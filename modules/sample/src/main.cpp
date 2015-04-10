#include <iostream>

#include "ucv.h"
#include "opencv_methods.h"

void search_figure(IplImage* src);

int main(int argc, char* argv[])
{
    IplImage* src = cvLoadImage(argv[1]);
    if(src==NULL)
    {
        std::cout << "[main]: файл не найден\n";
        return 1;
    }

    //окна
    cvNamedWindow("out", 0);
    cvNamedWindow("src", 0);
    cvNamedWindow("contour", 0);

	search_figure(src);

    //вывод
    cvShowImage("src", src);
    cvWaitKey(0);

	return 0;
}



void search_figure(IplImage* src)
{
	//изображения
	IplImage* srcPyr = cvCreateImage(cvSize(src->width/2, src->height/2), 8, 3);
	IplImage* bin = cvCreateImage(cvGetSize(src), 8, 1);	//контуры

	//массивы
	ucv::ContourStorage storage;	//контуры
	ucv::Lines lines;				//прямые
	ucv::Circles circles;			//окружности

	//опции
	ucv::SearchCircle::Option option;
	float accApprox= 2.0f;			//точность аппроксимации


	//пирамида изображений
	cvPyrDown(src, srcPyr, IPL_GAUSSIAN_5x5);
	cvPyrUp(srcPyr, src);

	//получем контуры
	cvCanny(src, bin, 10, 100, 3);

	//находим контуры
	ucv::findContours(bin, &storage);

	//находим прямые
	ucv::SearchLine::find(&storage, &lines, accApprox);

	//находим окружности
	option.isFastCalcRadius = false;
	option.maxRadius = src->height/2;
	option.accApproxLine = accApprox;
	option.threadCenter = 1;
	option.threadCirclePercent = 5;

	ucv::SearchCircle searchCircle(cvGetSize(src));
	searchCircle.find(&storage,
					  &lines,
					  &circles,
					  option
					  );

	std::cout << "[main]: найдено " << circles.size() << std::endl;


	//вывод
	ucv::SearchLine::draw(src, &lines, CV_RGB(0, 255, 0));
	ucv::SearchCircle::draw(src, &circles, CV_RGB(255, 0, 0));
}


/*End of file main.cpp*/
