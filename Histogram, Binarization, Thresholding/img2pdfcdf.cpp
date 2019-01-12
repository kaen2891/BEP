#include "bep2.h"

Mat_return img2pdfcdf(Mat gray)
{
	Mat_return returnImg;
	int Gray_scale = 256, sum = 0;
	int *histogram = new int[Gray_scale], *sum_histogram = new int[Gray_scale];

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

	returnImg.a = pdf;
	returnImg.b = cdf;

	return returnImg;

}