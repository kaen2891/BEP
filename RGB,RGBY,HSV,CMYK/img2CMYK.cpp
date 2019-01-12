#include "bep1.h"

Mat img2CMYK(Mat src)
{
	Mat CMYK(src.rows, src.cols, CV_8UC4);

	int nBlue = 0, nGreen = 0, nRed = 0;
	int nCyan = 0, nMagenta = 0, nYellow = 0, nBlackKey = 0;
	int min1 = 0, min2 = 0, final_min = 0;

	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			nBlue = src.at<Vec3b>(y, x)[0];
			nGreen = src.at<Vec3b>(y, x)[1];
			nRed = src.at<Vec3b>(y, x)[2];

			nCyan = 1 - nRed;
			nMagenta = 1 - nGreen;
			nYellow = 1 - nBlue;
			min1 = min(nCyan, nMagenta);
			min2 = min(nCyan, nYellow);
			final_min = min(min1, min2);
			nBlackKey = final_min;

			nCyan = nCyan - nBlackKey;
			nMagenta = nMagenta - nBlackKey;
			nYellow = nYellow - nBlackKey;

			CMYK.at<Vec4b>(y, x)[0] = nCyan;
			CMYK.at<Vec4b>(y, x)[1] = nMagenta;
			CMYK.at<Vec4b>(y, x)[2] = nYellow;
			CMYK.at<Vec4b>(y, x)[3] = nBlackKey;
		}
	}
	return CMYK;

}