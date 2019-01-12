#include "bep1.h"

Mat img2HSV(Mat src)
{
	Mat HSV(src.rows, src.cols, CV_8UC3);
	
	int nBlue = 0, nGreen = 0, nRed = 0;
	int nHue = 0, nSaturation = 0, nValue = 0;
	int max1 = 0, max2 = 0, min1 = 0, min2 = 0, final_max = 0, final_min = 0;

	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			nBlue = src.at<Vec3b>(y, x)[0];
			nGreen = src.at<Vec3b>(y, x)[1];
			nRed = src.at<Vec3b>(y, x)[2];
			
			max1 = max(nRed, nGreen);
			max2 = max(nRed, nBlue);
			final_max = max(max1, max2);

			min1 = min(nRed, nGreen);
			min2 = min(nRed, nBlue);
			final_min = min(min1, min2);
			nValue = final_max;

			if (nValue != 0) nSaturation = (nValue - final_min) / nValue;
				else nSaturation = 0;

			if (nValue == nRed) nHue = (60 * (nGreen - nBlue)) / (nValue - final_min);
				else if (nValue == nGreen) nHue = 120 + (60 * (nBlue - nRed)) / (nValue - final_min);
					else nHue = 240 + (60 * (nRed - nGreen)) / (nValue - final_min);
			
			HSV.at<Vec3b>(y, x)[0] = nHue;
			HSV.at<Vec3b>(y, x)[1] = nSaturation;
			HSV.at<Vec3b>(y, x)[2] = nValue;
		}
	}
	return HSV;
}