#include "meanshift_segmentation.h"

string winName = "meanshift";
int spatialRad, colorRad, maxPyrLevel;
Mat img, res;

void meanShiftSegmentation(int, void*)
{
    qDebug() << "spatialRad=" << spatialRad << "; "
        << "colorRad=" << colorRad << "; "
        << "maxPyrLevel=" << maxPyrLevel << endl;
    pyrMeanShiftFiltering(img, res, spatialRad, colorRad, maxPyrLevel);
    floodFillPostprocess(res, Scalar::all(2));
    imshow(winName, res);
}

void meanshift_segmentation(Mat input)
{
    img = input;
    qDebug() <<img.empty();
        if (img.empty())
        {
            qDebug() << "pic is empty";

        }

        spatialRad = 10;
        colorRad = 10;
        maxPyrLevel = 1;

        namedWindow(winName, WINDOW_AUTOSIZE);

        createTrackbar("spatialRad", winName, &spatialRad, 80,meanShiftSegmentation);
        createTrackbar("colorRad", winName, &colorRad, 60,meanShiftSegmentation);
        createTrackbar("maxPyrLevel", winName, &maxPyrLevel, 5, meanShiftSegmentation);

        meanShiftSegmentation(0, 0);

        waitKey();

}

void floodFillPostprocess(Mat & img, const Scalar& colorDiff ) //用来给不同的连通域涂上颜色
{
    qDebug() <<img.empty();
    CV_Assert(!img.empty());
    RNG rng = theRNG();
    Mat mask(img.rows + 2, img.cols + 2, CV_8UC1, Scalar::all(0));
    for (int y = 0; y < img.rows; y++)
    {
        for (int x = 0; x < img.cols; x++)
        {
            if (mask.at<uchar>(y + 1, x + 1) == 0)
            {
                Scalar newVal(rng(256), rng(256), rng(256));
                floodFill(img, mask, Point(x, y), newVal, 0, colorDiff, colorDiff);
            }
        }
    }
}
