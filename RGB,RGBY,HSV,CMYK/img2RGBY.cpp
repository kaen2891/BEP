#include "bep1.h"

Mat img2RGBY(Mat src)
{
	Mat RGBY(src.rows, src.cols, CV_8UC4);
	
	int nBlue = 0, nGreen = 0, nRed = 0;
	int newB = 0, newG = 0, newR = 0, newY = 0;
	
	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			nBlue = src.at<Vec3b>(y, x)[0];
			nGreen = src.at<Vec3b>(y, x)[1];
			nRed = src.at<Vec3b>(y, x)[2];

			newB =  nBlue - (nRed + nGreen) / 2;
			newG = nGreen - (nRed + nBlue) / 2;
			newR = nRed - (nGreen + nBlue) / 2;
			newY = (nRed + nGreen) / 2 - abs(nRed - nGreen) / 2 - nBlue;
			
			RGBY.at<Vec4b>(y, x)[0] = newR;
			RGBY.at<Vec4b>(y, x)[1] = newG;
			RGBY.at<Vec4b>(y, x)[2] = newB;
			RGBY.at<Vec4b>(y, x)[3] = newY;
		}
	}
	return RGBY;
}