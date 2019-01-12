#include "bep2.h"

Mat img2pdfcdf(Mat gray)
{
	int Gray_scale = 256;
	int *histogram = new int[Gray_scale], *sum_histogram = new int[Gray_scale];

	Mat pdf(256, 256, CV_8UC1, Scalar(0));

	// initialize array
	for (int i = 0; i < 256; i++) {
		// Caculate input GrayScale image's histogram
		histogram[i] = 0;
		// Caculate input GrayScale image's sum_histogram
		sum_histogram[i] = 0;
	}

	// insert gray intensity into array
	int nGray = 0;
	for (int y = 0; y < gray.rows; y++) {
		for (int x = 0; x < gray.cols; x++) {
			nGray = gray.at<uchar>[y, x];
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
	////
	//for PDF
	for (int i = 0; i < 256; i++) {
		int histo = 256 * histogram[i] / pdf_endpoint;
		line(pdf, Point(i + 10, 256), Point(i + 10, 256 - histo), Scalar(255, 255, 255));
		x = i + 210;
		if (x < 0) {
			x = 0;
			cout << "if¹® µé¾î¿È. x´Â : " << x << endl;
		}
		else if (x > 255) {
			x = 255;
			cout << "else if ¹® µé¾î¿È. x´Â : " << x << endl;
		}
		//line(pdf2slide, Point(x, 256), Point(x, 256 - histo), Scalar(255, 255, 255));
	}
	////
	// for CDF
	for (i = 0; i < 256; i++)
	{
		sum += histogram[i];
		sum_histogram[i] = sum;
		//cout << "i :" << i << ", sum_histogram[i] : " << sum_histogram[i] << endl;
	}
	for (i = 0; i < 256; i++) {
		int histo_cdf = 256 * sum_histogram[i] / sum_histogram[255];
		line(cdf, Point(i + 10, 256), Point(i + 10, 256 - histo_cdf), Scalar(255, 255, 255));
	}



}