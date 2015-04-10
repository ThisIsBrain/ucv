#include "search_circle.h"



//constructor
//==============================================================================
ucv::SearchCircle::SearchCircle(
				CvSize sizeImg	//размер изображения
				)
{
	sizeImg_	=	sizeImg;

	//аккумуляторный массив потенциальных центров окружностей
	accum4centre_.init(sizeImg.width, sizeImg.height);

}
//==============================================================================



//destructor
//==============================================================================
ucv::SearchCircle::~SearchCircle()
{

}
//==============================================================================



//поиск окружностей
//==============================================================================
int ucv::SearchCircle::find(
				ucv::ContourStorage* contours,	//контуры
				ucv::Lines* lines,				//прямые
				ucv::Circles* circles,			//массив окружностей
				Option option					//араметры поиска
				)
{
	ucv::Circle circle;
	ucv::ContourSegment segment;

	ucv::Array1<int> accum4radius;
	accum4radius.init(option.maxRadius+option.accApproxLine+2);

	float radius;	//радиус
	float weight;	//

	//1. Находим потенциальные центры окружностей на изображении

	//для каждой прямой
	for(ucv::LinesIt i=lines->begin(); i!=lines->end(); ++i){
		//вычисляем нормали к прямым

		CvPoint mid_pt;	//точка середины прямой
		mid_pt.x = i->begin.x+(i->end.x - i->begin.x)/2;
		mid_pt.y = i->begin.y+(i->end.y - i->begin.y)/2;

		float vector = sqrt(pow((float)(i->option.a), 2) + pow((float)(i->option.b), 2));	//длинна вектора

		CvPoint begin;
		CvPoint end;

		//вычисляем минимальный радиус окружности
		float min_radius = 0.0f;
		float app_radius = calcAppRadius(i->lenght, option.accApproxLine);
		if(app_radius-2.0f>=0.0){
			min_radius = app_radius-2.0f;
		}


		//рисуем перпендикуляры в аккумуляторном массиве в обе стороны от прямой
		for(int k=0; k<2; k++){
			//находим начальную и конечную тчку перпендикуляра
			begin.x=mid_pt.x+i->option.a*(float)(min_radius)/vector;
			begin.y=mid_pt.y+i->option.b*(float)(min_radius)/vector;

			end.x=mid_pt.x+i->option.a*(float)(option.maxRadius)/vector; //x0+a*step
			end.y=mid_pt.y+i->option.b*(float)(option.maxRadius)/vector;

			drawLineB(begin, end, i);

			i->option.a *= -1;
			i->option.b *= -1;
		}
	}

//	IplImage* dst = cvCreateImage(sizeImg_, 8, 1);
//	for(int x=0; x<dst->width; x++){
//		for(int y=0; y<dst->height; y++){
//			PIXEL(uchar, dst, x, y)[0]=accum4centre_.data[x][y].size()*50;
//		}
//	}
//	cvShowImage("out", dst);
//	cvWaitKey(0);

	//2. Уточняем наличие окружностей в найденных точках

	//для каждого потенциального центра
	for(int x=0; x<accum4centre_.size.size_a; x++){
		for(int y=0; y<accum4centre_.size.size_b; y++){

			int val = accum4centre_.data[x][y].size();

			//если нашли потенциальный центер
			if(val>option.threadCenter){

				//брасываем аккумулятор
				for(int i=0; i<accum4radius.size.size_a; i++){
					accum4radius.data[i]=0;
				}

				//для каждой прямой которая проголосовала за данный центр
				for(std::vector<ucv::LinesIt>::iterator l = accum4centre_.data[x][y].begin();
					l!=accum4centre_.data[x][y].end(); ++l){

					//2.1 записываем сегмент контура который соответсвует этой прямой
//					segment.begin=(*l)->segment.begin;
//					segment.end	=(*l)->segment.end;
//					circle.segments.push_back(segment);

					//2.2 считаем вклад данной прямой в вес окружности

					//если быстрый поиск
					if(option.isFastCalcRadius){
						//считаем расстояние до прямой
						float dist = ucv::calcDistanceFromLineToPoint(
									(*l)->option,
									cvPoint(x, y)
									);

						//радиус окружности
						radius = dist + option.accApproxLine;

						//вклад данной прямой
						weight=(*l)->lenght;

						//засчитываем
						if((int)(radius)>=0 && (int)(radius)<accum4radius.size.size_a){
							accum4radius.data[(int)(radius)]+=weight;
						}

					}else{
						//для каждоой точки контура
						for(ucv::ContourIt cIt = (*l)->segment.begin;
							cIt!= (*l)->segment.end; ++cIt){
							//вычисляем растояние от точки до центра
							float delta_x = abs(x - cIt->x);
							float delta_y = abs(y - cIt->y);
							radius = sqrt( delta_x*delta_x + delta_y*delta_y );

							if(radius>=accum4radius.size.size_a){
								std::cout << "over" << radius-accum4radius.size.size_a << "\n";
								continue;
							}

							//голос за данный радиус
							accum4radius.data[(int)(radius)]++;
						}
					}

				}

				//находим максимальную точку
				float maxW=0;
				float maxR=0;
				for(int i=0; i<accum4radius.size.size_a; i++){
					float v=accum4radius.data[i]/(i+1)*31.84;
					if(v>maxW){
						maxW=v;
						maxR=i;
						//std::cout << "d5\n";
					}
				}

				if(maxW>option.threadCirclePercent){
					circle.radius=maxR;
					circle.weight=maxW;
					circle.center.x=x;
					circle.center.y=y;
					circles->push_back(circle);
				}
			}
		}
	}

	return 0;
}
//==============================================================================



//вычисление приблизительного радиуса
//==============================================================================
float ucv::SearchCircle::calcAppRadius(
				float lenght,		//длина хорды
				float accApprox		//точность аппроксимации
				)
{
	float radius = ( ( pow( lenght/2 , 2 ) ) / accApprox + accApprox) / 2.0f;
	return radius;
}

//==============================================================================



//рисование прямых в аккумуляторном массиве (Алгоритм Брезенхема)
//==============================================================================
void ucv::SearchCircle::drawLineB(
			CvPoint begin,			//начальная точка
			CvPoint end,			//конечная точка
			ucv::LinesIt lineIt		//
			)
{
	bool step = abs(begin.x - end.x) < abs(begin.y - end.y);	//угол больше 45град

	//если угол больше 45 град
	if(step)
		{
		std::swap(begin.x, begin.y);
		std::swap(end.x, end.y);
		}

	//правильно размещаем начало и конец отрезка
	if(begin.x > end.x){

		std::swap(begin.x, end.x);
		std::swap(begin.y, end.y);

	}

	int deltaX = abs(end.x-begin.x);
	int deltaY = abs(begin.y-end.y);
	float k = (float)(deltaY)/(float)(deltaX);
	int stepY;

	if(begin.y > end.y){

		stepY=-1;

	}else{

		stepY=1;
	}

	float error=0;
	int y=begin.y;

	for(int x=begin.x; x<end.x; x++){

		if(!step){

			if(	x>=0 && x<accum4centre_.size.size_a &&
				y>=0 && y<accum4centre_.size.size_b){

				accum4centre_.data[x][y].push_back(lineIt);
			}

		}else{

			if(	x>=0 && x<accum4centre_.size.size_b &&
				y>=0 && y<accum4centre_.size.size_a){

				accum4centre_.data[y][x].push_back(lineIt);
			}
		}

		error+=k;
		if(error>=0.5){
			y+=stepY;	//pixel(x+1, y+1)
			error-=1;
			}
		//pixel(x+1, y)
	}
}
//==============================================================================


//нарисовать окружности
//==============================================================================
int ucv::SearchCircle::draw(
		IplImage* img,
		ucv::Circles* circles,
		CvScalar scalar
		)
{
	for(ucv::CirclesIt circle=circles->begin(); circle!=circles->end(); ++circle){
		cvCircle(img, circle->center, circle->radius, scalar);
	}

	return 0;
}
//==============================================================================



/*End of file search_circle.h*/
