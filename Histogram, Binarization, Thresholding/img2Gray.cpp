#include "bep2.h"
Mat img2Gray(Mat src)
{
	Mat gray(src.rows, src.cols, CV_8UC1);
	int nBlue = 0, nGreen = 0, nRed = 0, nGray = 0;
	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			nBlue = src.at<Vec3b>(y, x)[0];
			nGreen = src.at<Vec3b>(y, x)[1];
			nRed = src.at<Vec3b>(y, x)[2];
			nGray = (nBlue + nGreen + nRed) / 3;
			gray.at<uchar>(y, x) = nGray;
		}
	}
	return gray;
}