#include "search_circle.h"



//constructor
//==============================================================================
ucv::SearchCircle::SearchCircle(
				CvSize sizeImg,	//размер изображения
				int maxRadius 	//максимальный радиус окружности	
				)
{
	sizeImg_	=	sizeImg;
	maxRadius_	=	maxRadius;

	//аккумуляторный массив потенциальных центров окружностей
	accum4centre_.init(sizeImg.width, sizeImg.height);

}
//==============================================================================



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
				ucv::Circles* circles			//массив окружностей
				)
{

	return 0;
}
//==============================================================================
