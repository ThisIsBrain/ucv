#include "graphic_pillars.h"


//найти прямые
int ucv::SearchLine::find(
					ucv::ContourStorage* contours,	//контуры
					std::vector<ucv::Line>* lines,	//массив прямых
					float accApprox					//точность аппроксимации контуров
					)
{
	ucv::ContourStorageIt contourIt;		//указатель на текущий контур
	ucv::DominantPoints dominantPoints;		//доминирующие точки
	ucv::Line line;							//прямая

	//для каждого контура
	for(contourIt=contours->begin(); contourIt!=contours->end(); ++contourIt){

		//1. Аппроксимация контура (поиск доминирующих точек)
		dominantPoints.clear();
		dominantPoints.push_back(contourIt->begin());		//конечная точка контура
		dominantPoints.push_back(contourIt->end());			//начальная точка контура
		
		ucv::DominantPointsIt dIt=dominantPoints.end();		//конечная точка аппроксимирования
		--dIt;												//

		ucv::approxContoursDp(	&(*contourIt),				//контур
								&dominantPoints,			//доминирующие точки 
								dominantPoints.begin(),		//начальная точка аппроксимирования
								dIt,						//конечная точка аппроксимирования
								accApprox					//точность аппроксимирования
								);

		//2. записывае параметры полученых после аппроксимирования прямых
		ucv::DominantPointsIt endIt = dominantPoints.end();	//последняя доминирующая точка
		--endIt;											//
		--endIt;											//
		
		//для каждой прямой
		for(ucv::DominantPointsIt it = dominantPoints.begin();
			it != endIt; ++it){
			
			
			ucv::DominantPointsIt it2 = it;
			++it2;
			
			//записываем координаты концов прямой
			line.begin.x=(*it)->x;
			line.begin.y=(*it)->y;
			line.end.x=(*it2)->x;
			line.end.y=(*it2)->y;
			
			//записываем указатели на точки контура
			line.segment.begin=*it;
			line.segment.end=*it2;
			
			//вычисляем параметры прямой
			ucv::calcLineAbc(line.begin, line.end, &line.option);
			
			//вес прямой
			//(пока квадрат длины прямой)
			line.weight = pow(line.begin.x-line.end.x, 2) + pow(line.begin.y-line.end.y, 2);
			
			//записываем прямую в вектор
			lines->push_back(line); 
		}
	}
	return 0;
}


//отобразть прямые
int ucv::SearchLine::draw(
					IplImage* img,		//исходное изображение
					ucv::Lines* lines,	//прямые
					CvScalar color		//ывет прямой
					)
{
	//для каждой прямой
	for(ucv::LinesIt line = lines->begin(); line!=lines->end(); ++line){
		cvLine(img, line->begin, line->end, color);
	}
	return 0;
}
/*End of file features.h*/
