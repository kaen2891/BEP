#include "bep2.h"

Mat_return sliding(Mat gray, int sliding_index)
{
	Mat_return returnImg;
	int Gray_scale = 256, sum = 0;
	int *histogram = new int[Gray_scale], *sum_histogram = new int[Gray_scale];
	Mat slide(gray.rows, gray.cols, CV_8UC1);
	Mat pdf(256, 256, CV_8UC1, Scalar(0));
	Mat cdf(256, 256, CV_8UC1, Scalar(0));

	// initialize array
	for (int i = 0; i < 256; i++) {
		histogram[i] = 0;
		sum_histogram[i] = 0;
	}

	// insert gray intensity into array
	int nGray = 0;
	for (int y = 0; y < gray.rows; y++) {
		for (int x = 0; x < gray.cols; x++) {
			nGray = gray.at<uchar>(y, x);
			//sliding
			nGray = nGray + sliding_index;
			// nGray: intensity. The intensity of the grayscale is 0~255
			if (nGray < 0) nGray = 0;
			if (nGray > 255) nGray = 255;
			slide.at<char>(y, x) = nGray;
			histogram[nGray] += 1;
		}
	}

	// for endpoint
	int pdf_endpoint = 1;
	for (int i = 0; i < 256; i++) {
		if (pdf_endpoint < histogram[i]) {
			pdf_endpoint = histogram[i];
		}
	}

	// draw PDF
	for (int i = 0; i < 256; i++) {
		// Caculate input GrayScale image's each histogram = pdf
		int histo = 256 * histogram[i] / pdf_endpoint;
		line(pdf, Point(i, 256), Point(i, 256 - histo), Scalar(255, 255, 255));

	}

	// draw CDF
	for (int i = 0; i < 256; i++)
	{
		sum += histogram[i];
		sum_histogram[i] = sum;
	}
	for (int i = 0; i < 256; i++) {
		// Caculate input GrayScale image's sum_histogram = cdf
		int histo_cdf = 256 * sum_histogram[i] / sum_histogram[255];
		line(cdf, Point(i, 256), Point(i, 256 - histo_cdf), Scalar(255, 255, 255));
	}

	returnImg.a = slide;
	returnImg.b = pdf;
	returnImg.c = cdf;

	return returnImg;

}