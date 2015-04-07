#ifndef OPENCV_METHODS_H
#define OPENCV_METHODS_H

#include <cv.h>
#include <highgui.h>

//макрос для доступа к данным изображени
#define PIXEL(type, img, x, y)	(((type*) ((img)->imageData+(y)*(img)->widthStep))+(x)*(img)->nChannels)

#endif
/*End of file opencv_method.h*/
