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
	Mat_return returnpdfcdf = img2pdfcdf(Gray);
	
	int slide_index = 50;
	Mat_return returnSliding = sliding(Gray, slide_index);
	Mat_return returnStretching = stretching(Gray);
	int min_shrink = 50, max_shrink = 150;
	Mat_return returnShrinking = shrinking(Gray, min_shrink, max_shrink);
	
	imshow("pdf", returnpdfcdf.a);
	imshow("cdf", returnpdfcdf.b);
	imshow("50sliding img", returnSliding.a);
	imshow("50sliding pdf", returnSliding.b);
	imshow("50sliding cdf", returnSliding.c);
	imshow("stretching image", returnStretching.a);
	imshow("stretching pdf", returnStretching.b);
	imshow("stretching cdf", returnStretching.c);
	imshow("shrink image", returnShrinking.a);
	imshow("shrink pdf ", returnShrinking.b);
	imshow("shrink cdf", returnShrinking.c);

	waitKey(0);

	return 0;
}