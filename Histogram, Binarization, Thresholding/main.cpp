#include "bep2.h"
//img name: LENA256.jpg

int main()
{
	Mat src = imread("LENA256.jpg");

	if (!src.data) {
		std::cout << "Image not loaded";
		return -1;
	}

	Mat Gray = img2Gray(src);
	Mat_return returnImg = img2pdfcdf(Gray);
	
	imshow("pdf", returnImg.a);
	imshow("cdf", returnImg.b);
	waitKey(0);

	return 0;
}