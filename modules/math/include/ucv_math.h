#ifndef MATH_H
#define MATH_H

#include <math.h>

#include <cv.h>

#include "ucv.h"



namespace ucv
{
	//считает параметры прямой заданной двумя точками
	void calcLineAbc(	CvPoint begin,			//точка начала прямой
						CvPoint end,			//точка конца прямой
						ucv::LineAbc* option	//параметры A B C прямой
						);
				
	//возвращает расстояние от прямой заданной параметрически до точки 
    float calcDistanceFromLineToPoint(
                ucv::LineAbc option,	//параметры A B C прямой
				CvPoint point			//точка в плоскости
				);
}
#endif
/*End of file*/
