#include "contour.h"

//поиск контуров
void ucv::findContours(	IplImage* src,				//исходное контурное изобрвжение
					 	ContourStorage* contours	//указаетль на хранилеще контуров
					 	)
{
	CvPoint point;	//текущая точка
	ucv::Contour contour;	//текущий контур
	
	//для каждой точки принадлежащей контуру
	for(int x=0; x<src->width; x++){
		for(int y=0; y<src->height; y++){
			if(PIXEL(uchar, src, x, y)[0]==255){	//если нашли начало контура
				
				//начальный размер вектора
				contour.clear();
				//contour.reserve(std::max(src->width, src->height));	
				
				//первая точка контура
				point = cvPoint(x, y);	
				contour.push_back(point);	//set point in vector
				
				//пока не дойдем до конца контура
				while(NEIGHBOR_PIXEL(src, &point)){	//переход на соседний пиксель					
					//set point in vector
					contour.push_back(point);
				}
				
				//если не слишком короткий контур
				if(contour.size()>1){
					//contour.shrink_to_fit();		//сжимаем вектор до минимального значения
					contours->push_back(contour);	//закидываем данный контур в массив контуров
				}
			}
		}
	}
}






//соседний контурный пиксель
//ВОЗВРАЩАЕТ: false - если нет соседних точек					 
inline bool ucv::NEIGHBOR_PIXEL(	IplImage* src,		//исходное контурное изображение
									CvPoint* pt			//указатель на исходную точку, сюда же будет записана координата соседней точки
									)
{
	//здесь должна быть проверка на принадлежность пикселя контуру

	if(pt->x==0 || pt->y==0 || pt->x == src->width-1 || pt->y == src->height-1)
	{
		return false;
	}
	
	PIXEL(uchar, src, pt->x, pt->y)[0]=254;	//помечаем точку как найденную
	
	//перебираем соседние пиксели
	if(PIXEL(uchar, src, pt->x, pt->y+1)[0]==255){		//32
		pt->y+=1;
		return true;
	}
		
	if(PIXEL(uchar, src, pt->x+1, pt->y)[0]==255){		//23
		pt->x+=1;
		return true;
	}
		
	if(PIXEL(uchar, src, pt->x, pt->y-1)[0]==255){		//12
		pt->y-=1;
		return true;
	}
	
	if(PIXEL(uchar, src, pt->x-1, pt->y)[0]==255){		//21
		pt->x-=1;
		return true;
	}
	
	if(PIXEL(uchar, src, pt->x+1, pt->y+1)[0]==255){		//33
		pt->x+=1;
		pt->y+=1;
		return true;
	}
			
	if(PIXEL(uchar, src, pt->x+1, pt->y-1)[0]==255){		//13
		pt->x+=1;
		pt->y-=1;
		return true;
	}
		
	if(PIXEL(uchar, src, pt->x-1, pt->y+1)[0]==255){		//31
		pt->x-=1;
		pt->y+=1;
		return true;
	}
	
	if(PIXEL(uchar, src, pt->x-1, pt->y-1)[0]==255)	{	//11
		pt->x-=1;
		pt->y-=1;
		return true;
	}
	
	return false;	//нет соседних пикселей
}





//Линеная аппроксимация (Douglas-Peucker algorithm)
void ucv::approxContoursDp(	ucv::Contour* contour,					//указатель на исходный контур		
							ucv::DominantPoints* dominantPoints,	//указатель на массив куда будут записаны доминирующие точки
							ucv::DominantPointsIt beginNode,		//начало отрезка контура
							ucv::DominantPointsIt endNode,			//конец отрезка контура
							float eps								//точность аппроксимации в пикселях
							)
{
	ucv::LineAbc option;		//параметры данной прямой
	
	ucv::ContourIt contourBegin = *beginNode;	//начало контура
	ucv::ContourIt contourEnd   = *endNode;		//конец контура
	ucv::DominantPointsIt newNode;				//итератор на новый узел

	//1. Вычисление парметров данной прямой
	ucv::calcLineAbc(	cvPoint(contourBegin->x, contourBegin->y),
					 	cvPoint(contourEnd->x, contourEnd->y),
						&option
						);
				 
	//2. Вычисляем самую удаленную точку	
	
	ucv::ContourIt maxPt;		//указатель на самую удаленную точку
	float maxD=0.0;				//максимальное расcтояние от прямой до точки
	
	//проходим по контуру в диапозоне begin-end
	for(ucv::ContourIt it=contourBegin; it!=contourEnd; ++it)
		{
		float value=ucv::calcDistanceFromLineToPoint(option, cvPoint(it->x, it->y));
		if(value>maxD)
			{
			maxD=value;
			maxPt=it;
			}
		}


	//3. если точка сильно удалена от прямой - добавляем новый узел
	if(maxD>=eps)
		{		
		//добаволяем новый узел и получаем на него итератор
		newNode=dominantPoints->insert(endNode, maxPt);	
		
		//4.аппроксимируем полученые прямые
		ucv::approxContoursDp(	contour,
								dominantPoints,
								beginNode,
								newNode,
								eps);
								
		ucv::approxContoursDp(contour,
								dominantPoints,
								newNode,
								endNode,
								eps);
		}
		
	//иначе - аппроксимация закончена 
}




//отрисовка контура на изображении
void ucv::drawContour(	IplImage* src,				//исходное изображение 
				 		ucv::Contour* contour,		//контур
				 		CvScalar color				//цвет контура
				 		)
{
	CvPoint point;
	ucv::ContourIt it;
	
	for(it=contour->begin(); it!=contour->end(); ++it){
		point=*it;
		//if(point.x >=0 && point.x<src->width && point.y >= 0 && point.y < src->height)
		for(int i=0; (i<4 && i<src->nChannels); i++){
			PIXEL(uchar, src, point.x, point.y)[i]=color.val[i];
		}
	}

}

/*end of file contour.cpp*/
