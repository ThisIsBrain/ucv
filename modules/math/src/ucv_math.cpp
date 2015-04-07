#include "ucv_math.h"





//считает параметры прямой заданной двумя точками
//==============================================================================
void ucv::calcLineAbc(	CvPoint begin,			//точка начала прямой
						CvPoint end,			//точка конца прямой
						ucv::LineAbc* option	//параметры A B C прямой
						)
{
	float x1	=	begin.x;	
	float y1	=	begin.y;
	float x2	=	end.x;
	float y2	=	end.y;
	
	option->a=y2-y1;
	option->b=-1.0*(x2-x1);
	option->c=-1.0*option->a*x1-option->b*y1;
}
//==============================================================================




			
//возвращает расстояние от прямой заданной параметрически до точки 
//==============================================================================
float ucv::calcDistanceFromLineToPoint(	ucv::LineAbc option,	//параметры A B C прямой
										CvPoint point			//точка в плоскости
										)
{
	float distance;					//расстояние до точки
	float m_x	=	point.x;
	float m_y	=	point.y;
	
	
	if(option.a==0 && option.b==0)
		{
		std::cout << "a=0 b=0\n";
		distance=0;
		}
		
    distance = fabs(option.a * m_x + option.b * m_y + option.c)/sqrt(option.a * option.a + option.b * option.b);	//вычисляем расстояние до точки
	
	return distance;
}
//==============================================================================





/*End of file*/
