#ifndef MEANSHIFT_SEGMENTATION_H
#define MEANSHIFT_SEGMENTATION_H

#include <QDebug>

#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;


void meanshift_segmentation(Mat input);

extern string winName ;
extern int spatialRad, colorRad, maxPyrLevel;
extern Mat img, res;


void floodFillPostprocess(Mat& img, const Scalar& colorDiff = Scalar::all(1));//用来给不同的连通域涂上颜色



void meanShiftSegmentation(int, void*);

#endif // MEANSHIFT_SEGMENTATION_H
