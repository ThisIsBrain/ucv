#include <iostream>

#include "ucv.h"
#include "opencv_methods.h"

int main(int argc, char* argv[])
{
    IplImage* src = cvLoadImage(argv[1]);
    if(src==NULL)
    {
        std::cout << "[main]: файл не найден\n";
        return 1;
    }

    //пирамида изображений
    IplImage* srcPyr=cvCreateImage(cvSize(src->width/2, src->height/2), 8, 3);
    cvPyrDown(src, srcPyr, IPL_GAUSSIAN_5x5);
    cvPyrUp(srcPyr, src);

    //олучем контуры
    IplImage* bin = cvCreateImage(cvGetSize(src), 8, 1);
    cvCanny(src, bin, 10, 100, 3);

    //окна
    cvNamedWindow("out", 0);
    cvNamedWindow("src", 0);
    cvNamedWindow("contour", 0);

    //реобразовния
    IplImage* cntr = cvCreateImage(cvGetSize(src), 8, 1);
    cvZero(cntr);

	//находим контуры
    ucv::ContourStorage storage;
    ucv::findContours(bin, &storage);

	//находим прямые
	std::vector<ucv::Line> lines;
	ucv::SearchLine::find(&storage, &lines, 2.0f);
	std::cout << lines.size() << std::endl;
	ucv::SearchLine::draw(src, &lines, CV_RGB(255, 255, 255));


    //вывод
    cvShowImage("src", src);
    cvShowImage("out", bin);
    cvShowImage("contour", cntr);
    cvWaitKey(0);

	return 0;
}
/*End of file main.cpp*/
