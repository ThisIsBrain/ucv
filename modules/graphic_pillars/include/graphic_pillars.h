#ifndef GRAPHIC_PILLARS_H
#define GRAPHIC_PILLARS_H

#include "ucv.h"
#include "opencv_methods.h"

namespace ucv
{
	class SearchLine
	{
		public:
		SearchLine();		//constructor
		~SearchLine();		

		//найти прямые
		static int find(
				ucv::ContourStorage* contours,	//контуры
				std::vector<ucv::Line>* lines,	//массив прямых
				float accApprox					//точность аппроксимации
				);

		//отобразить прямые
		static int draw(
					IplImage* img,		//исходное изображение
					ucv::Lines* lines,	//прямые
					CvScalar color		//ывет прямой
					);
	};
}

#endif
/*End of file features.cpp*/
