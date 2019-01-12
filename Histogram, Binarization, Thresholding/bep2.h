#pragma once

#include "opencv2\highgui\highgui.hpp"
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <iostream>
using namespace std;
using namespace cv;


Mat img2Gray(Mat src);
Mat img2pdfcdf(Mat gray);
