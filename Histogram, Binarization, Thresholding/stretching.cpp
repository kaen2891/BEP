#include "bep2.h"
Mat_return stretching(Mat gray)
{
	int Gray_scale = 256;
	Mat_return returnImg;
	Mat stretch(gray.rows, gray.cols, CV_8UC1);
	Mat stretch_pdf(Gray_scale, Gray_scale, CV_8UC1, Scalar(0));
	Mat stretch_cdf(Gray_scale, Gray_scale, CV_8UC1, Scalar(0));
	int i, x, y;
	int value = 0, sum = 0, nmin = 256, nmax = 0, my_Min = 0, my_Max = Gray_scale;
	double *stretch_histogram = new double[Gray_scale], *sum_stretch_histogram = new double[Gray_scale];
	int *histogram = new int[Gray_scale];
	int extract_grayscale = 0;

	for (int i = 0; i < 256; i++) {
		stretch_histogram[i] = 0;
		sum_stretch_histogram[i] = 0;
		histogram[i] = 0;
	}

	// insert gray intensity into array and get most min, most max
	int nGray = 0;
	for (int y = 0; y < gray.rows; y++) {
		for (int x = 0; x < gray.cols; x++) {
			nGray = gray.at<uchar>(y, x);
			if (nGray < nmin) nmin = nGray;
			if (nGray > nmin) nmax = nGray;
			histogram[nGray] += 1;
		}
	}
	// using nmax, nmin to calculate stretching
	for (int y = 0; y < gray.rows; y++) {
		for (int x = 0; x < gray.cols; x++) {
			extract_grayscale = gray.at<uchar>(y, x);
			extract_grayscale = abs(extract_grayscale - nmin) * my_Max / (nmax - nmin);
			if (extract_grayscale > 255) extract_grayscale = 255;
			if (extract_grayscale < 0) extract_grayscale = 0;
			stretch.at<uchar>(y, x) = extract_grayscale;
			stretch_histogram[extract_grayscale] += 1;
		}
	}

	int pdf_endpoint = 1;

	// Calculate stretching
	for (int i = 0; i < Gray_scale; i++) {
		if (pdf_endpoint < histogram[i]) {
			pdf_endpoint = histogram[i];
		}
	}

	//for draw Frequency
	for (i = 0; i < Gray_scale; i++) {
		int histo = Gray_scale * stretch_histogram[i] / pdf_endpoint;
		line(stretch_pdf, Point(i, Gray_scale), Point(i, Gray_scale - histo), Scalar(255, 255, 255));
	}

	// draw CDF
	for (int i = 0; i < 256; i++)
	{
		sum += stretch_histogram[i];
		sum_stretch_histogram[i] = sum;
	}
	for (int i = 0; i < 256; i++) {
		int histo_cdf = 256 * sum_stretch_histogram[i] / sum_stretch_histogram[255];
		line(stretch_cdf, Point(i, 256), Point(i, 256 - histo_cdf), Scalar(255, 255, 255));
	}

	returnImg.a = stretch;
	returnImg.b = stretch_pdf;
	returnImg.c = stretch_cdf;

	return returnImg;
}