#ifndef TYPES_H
#define TYPES_H

#include <cv.h>

#include <list>
#include <vector>


namespace ucv
{
	
	//параметрически заданная прямая	
	//=====================================================
	typedef struct LineAbc
	{
		float a;
		float b;
		float c;
	}LineAbc;
	
	//конструктор
	LineAbc lineAbc(float a, float b, float c);
	//=====================================================
	
	
	
	//контуры
	//=====================================================
	typedef std::vector<CvPoint> Contour;
	typedef std::vector<CvPoint>::iterator ContourIt;
	typedef std::vector<ucv::Contour> ContourStorage;
	typedef std::vector<ucv::Contour>::iterator ContourStorageIt;
	
	typedef std::list<ucv::ContourIt> DominantPoints;				//доминирующие точки контура
	typedef std::list<ucv::ContourIt>::iterator DominantPointsIt;	//
	
	//сегмент контура
	typedef struct ContourSegment
	{
		ContourIt begin;
		ContourIt end;
	}ContourSegment;
	//=====================================================
	
	
	
	//линии
	//=====================================================
	
	//прямая
	typedef struct Line
	{
		LineAbc option;			//параметры прямой
		
		ContourSegment segment;	//сегмент контура соответсвующий данной прямой
		
		CvPoint begin;		//координаты начала отрезка
		CvPoint end;		//координаты конца отрезка
		
		float weight;		//вес прямой
	}Line;

	typedef std::vector<Line> Lines;				//массив прямых
	typedef std::vector<Line>::iterator LinesIt;	//
	
	
	//окружность
	typedef struct Circle
	{
		CvPoint center;			//центр окружности
		float radius;			//радиус окружности
		std::vector<ContourSegment> segments;	//cегменты контура соответсвующие данной окружности
		
		float weight;		//вес окружности
	}Circle;
	//=====================================================

}


#endif
/*End of file types.h*/
