#ifndef SEARCH_CIRCLE_H
#define SEARCH_CIRCLE_H

#include "graphic_pillars.h"

namespace ucv
{
	class SearchCircle
	{
		public:

		//труктура опций
		struct Option
		{
			int minRadius;			//минимальный радиус окружностей
			int maxRadius;			//максимальный радиус окружностей
			bool isFastCalcRadius;	//быстрое вычисление радиуса
			float accApproxLine;	//точность аппроксимации контуров
			int threadCenter;		//пороговое значение для возможного центра
			int threadCirclePercent;//пороговое часть окружноости
			int devRadius;			//точность квантования аккумулитивного массива радиуса
		};

		// SearchCircle();
		SearchCircle(
				CvSize sizeImg	//размер изображения
				);

		~SearchCircle();

		//поиск окружностей
		int find(
				ucv::ContourStorage* contours,	//контуры
				ucv::Lines* lines,				//прямые
				ucv::Circles* circles,			//массив окружностей
				Option option					//параметры поиска
				);


		//отрисовка окружностей
		static int draw(
				IplImage* img,
				ucv::Circles* circles,
				CvScalar scalar
				);


		private:
		//размер изображения
		CvSize sizeImg_;

		//массив потенциальных центров окружностей
		ucv::Array2< std::vector<LinesIt> > accum4centre_;

		//вычисление приблизительного радиуса
		float calcAppRadius(
						float lenght,	//длина хорды
						float accApprox //точность аппроксимации
						);

		//рисование прямых в аккумуляторном массиве (Алгоритм Брезенхема)
		void drawLineB(
					CvPoint begin,			//начальная точка
					CvPoint end,			//конечная точка
					ucv::LinesIt lineIt		//
					);
	};
}


#endif
/*End of file search_circle.h*/
