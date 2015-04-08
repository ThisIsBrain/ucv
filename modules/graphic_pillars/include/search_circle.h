#ifndef SEARCH_CIRCLE_H
#define SEARCH_CIRCLE_H

#include "graphic_pillars.h"

namespace ucv
{
	class SearchCircle
	{
		public:
		// SearchCircle();
		SearchCircle(
				CvSize sizeImg,	//размер изображения
				int maxRadius 	//максимальный радиус окружности	
				);

		~SearchCircle();

		//поиск окружностей
		int find(
				ucv::ContourStorage* contours,	//контуры
				ucv::Lines* lines,				//прямые
				ucv::Circles* circles			//массив окружностей
				);

		private:
		CvSize sizeImg_;	//размер изображения
		int maxRadius_;		//максимальный радиус окружности

		//массив потенциальных центров окружностей
		ucv::Array2< std::list<LinesIt> > accum4centre_;
	};
}


#endif
/*End of file search_circle.h*/
