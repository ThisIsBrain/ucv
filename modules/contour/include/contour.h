#ifndef CONTOUR_H
#define CONTOUR_H

#include "ucv.h"
#include "opencv_methods.h"

namespace ucv
{
	//поиск контуров
	void findContours(	IplImage* src,				//исходное контурное изобрвжение
					 	ContourStorage* contours	//указаетль на хранилеще контуров
					 	);
					 	
	//соседний контурный пиксель
	//ВОЗВРАЩАЕТ: false - если нет соседних точек					 
	inline bool NEIGHBOR_PIXEL(	IplImage* src,		//исходное контурное изображение
								CvPoint* pt			//указатель на исходную точку, сюда же будет записана координата соседней точки
								);
	
	//Линеная аппроксимация (Douglas-Peucker algorithm)
	void approxContoursDp(	ucv::Contour* contour,					//указатель на исходный контур		
							ucv::DominantPoints* dominantPoints,	//указатель на массив куда будут записаны доминирующие точки
							ucv::DominantPointsIt beginNode,		//начало отрезка контура
							ucv::DominantPointsIt endNode,			//конец отрезка контура
							float eps								//точность аппроксимации в пикселях
							);
	
	//отрисовка контура на изображении
	void drawContour(	IplImage* src,				//исходное изображение 
					 	ucv::Contour* contour,		//контур
					 	CvScalar color				//цвет контура
					 	);
}

#endif
/*End of file contour.h*/
