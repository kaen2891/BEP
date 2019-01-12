/* Copyright (C) kaen2891 <https://github.com/kaen2891/BEP> */
/* 
*	use img to get RGB and convert to RGBY, CMYK, HSV, GRAY
*	img2RGBY: get image and calculate equation to convert RGB to RGBY
*	img2Gray: get image and calculate equation to convert RGB to GRAY
*	img2HSV: get image and calculate equation to convert RGB to HSV
*	img2CMYK: get image and calculate equation to convert RGB to CMYK
*	pointEye: draw circle and line for make point
*
*					by June-Woo Kim
					Author kaen2891 (kaen2891@gmail.com)
*						2019.01.12
*/

#pragma once
#include "opencv2\highgui\highgui.hpp"
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <iostream>
using namespace std;
using namespace cv;


Mat img2RGBY(Mat src);
Mat img2Gray(Mat src);
Mat img2HSV(Mat src);
Mat img2CMYK(Mat src);
Mat img2point(Mat eye);