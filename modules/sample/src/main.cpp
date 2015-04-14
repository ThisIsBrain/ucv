#include <iostream>

#include "ucv.h"
#include "opencv_methods.h"
#include <time.h>

void search_figure(IplImage* src);

int main(int argc, char* argv[])
{
//	CvCapture* capture = cvCreateCameraCapture(0);
//	IplImage* src;

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

	while(1){
//		src = cvQueryFrame(capture);
		search_figure(src);

		//вывод
		cvShowImage("src", src);
		char s = cvWaitKey(0);
		if(s==27){
			return 0;
		}
	}

	return 0;
}



void search_figure(IplImage* src)
{
	//time
	long t1, t2;
	float t3;

	//изображения
	IplImage* srcPyr = cvCreateImage(cvSize(src->width/2, src->height/2), 8, 3);
	IplImage* bin = cvCreateImage(cvGetSize(src), 8, 1);	//контуры

	//массивы
	ucv::ContourStorage storage;	//контуры
	ucv::Lines lines;				//прямые
	ucv::Circles circles;			//окружности

	//опции
	ucv::SearchCircle::Option option;
	float accApprox= 1.5f;			//точность аппроксимации


	//пирамида изображений
	cvPyrDown(src, srcPyr, IPL_GAUSSIAN_5x5);
	cvPyrUp(srcPyr, src);

	//получем контуры
	cvCanny(src, bin, 10, 100, 3);

	//находим контуры
t1=clock();
	ucv::findContours(bin, &storage);
t2=clock();
t3=((float)(t2)-(float)(t1))/1000;
std::cout << "Контуры найдены: " << t3 << std::endl;

	//находим прямые
t1=clock();
	ucv::SearchLine::find(&storage, &lines, accApprox);
t2=clock();
t3=((float)(t2)-(float)(t1))/1000;
std::cout << "прямые найдены: " << t3 << std::endl;

	//находим окружности
	option.isFastCalcRadius = false;
	option.minRadius = 10;
	option.maxRadius = src->height;
	option.accApproxLine = accApprox;
	option.threadCenter = 2;
	option.threadCirclePercent = 80;
	option.devRadius = 2;


t1=clock();
	ucv::SearchCircle searchCircle(cvGetSize(src));
	searchCircle.find(&storage,
					  &lines,
					  &circles,
					  option
					  );
t2=clock();
t3=((float)(t2)-(float)(t1))/1000;
std::cout << "окружности найдены: " << t3 << std::endl;
	std::cout << "[main]: найдено " << circles.size() << std::endl;


	//вывод
	ucv::SearchLine::draw(src, &lines, CV_RGB(0, 255, 0));
	ucv::SearchCircle::draw(src, &circles, CV_RGB(255, 0, 0));
}


/*End of file main.cpp*/
