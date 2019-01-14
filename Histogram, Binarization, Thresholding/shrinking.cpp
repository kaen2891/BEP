#include "bep2.h"

Mat_return shrinking(Mat gray, int min_shrink, int max_shrink)
{
	Mat_return returnImg;
	int Gray_scale = 256;
	Mat shrink(gray.rows, gray.cols, CV_8UC1);
	Mat shrink_pdf(Gray_scale, Gray_scale, CV_8UC1, Scalar(0));
	Mat shrink_cdf(Gray_scale, Gray_scale, CV_8UC1, Scalar(0));

	int nGray = 0, value = 0, sum = 0, nmin = 256, nmax = 0, my_Min = 0, my_Max = 256;
	int *histogram = new int[Gray_scale], *sum_histogram = new int[Gray_scale];
	int for_measure = 0, final_result = 0, extract_grayscale = 0;
	double *shrink_histogram = new double[Gray_scale];

	for (int i = 0; i < Gray_scale; i++) {
		//Caculate input GrayScale image's histogram
		histogram[i] = 0;
		//Caculate input GrayScale image's sum_histogram
		sum_histogram[i] = 0;
		shrink_histogram[i] = 0;
	}
	for (int y = 0; y < gray.rows; y++) {
		for (int x = 0; x < gray.cols; x++) {
			nGray = gray.at<uchar>(y, x);
			if (nGray < nmin) nmin = nGray; //23
			if (nGray > nmax) nmax = nGray; //245
			histogram[nGray] += 1;
		}
	}

	int under = nmax - nmin;
	double for_shrink_index = 0, final_for_shrink_index = 0;
	for_shrink_index = abs(max_shrink - min_shrink);
	final_for_shrink_index = for_shrink_index / under;
	
	for (int y = 0; y < gray.rows; y++) {
		for (int x = 0; x < gray.cols; x++) {
			extract_grayscale = gray.at<uchar>(y, x);
			for_measure = (abs(extract_grayscale - nmin));
			for_measure = for_measure + min_shrink;
			for_shrink_index = final_for_shrink_index * for_measure;
			shrink.at<uchar>(y, x) = for_shrink_index;
			final_result = floor(for_shrink_index);
			shrink_histogram[final_result] += 1;
		}
	}
	int pdf_endpoint = 1;
	for (int i = 0; i < 128; i++) {
		if (pdf_endpoint < histogram[i]) {
			pdf_endpoint = histogram[i];
		}
	}

	for (int i = 0; i < Gray_scale; i++) {
		int histo2 = Gray_scale * shrink_histogram[i] / pdf_endpoint;
		line(shrink_pdf, Point(i, Gray_scale), Point(i, Gray_scale - histo2), Scalar(255, 255, 255));
	}
	// draw CDF
	for (int i = 0; i < 256; i++)
	{
		sum += shrink_histogram[i];
		shrink_histogram[i] = sum;
	}

	for (int i = 0; i < 256; i++) {
		int histo_cdf = 256 * shrink_histogram[i] / shrink_histogram[255];
		line(shrink_cdf, Point(i, 256), Point(i, 256 - histo_cdf), Scalar(255, 255, 255));
	}

	returnImg.a = shrink;
	returnImg.b = shrink_pdf;
	returnImg.c = shrink_cdf;

	return returnImg;

}
