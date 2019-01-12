#pragma once

#include "opencv2\highgui\highgui.hpp"
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <iostream>
using namespace std;
using namespace cv;

typedef struct Mat_value
{
	Mat a;
	Mat b;
}Mat_return;


Mat img2Gray(Mat src);
Mat_return img2pdfcdf(Mat gray);

