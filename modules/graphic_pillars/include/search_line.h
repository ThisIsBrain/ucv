#ifndef SEARCH_LINE_H
#define SEARCH_LINE_H

#include "graphic_pillars.h"

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
/*End of file search_line.h*/