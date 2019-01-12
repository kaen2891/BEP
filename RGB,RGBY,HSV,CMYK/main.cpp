#include "bep1.h"

int main() {
	Mat src = imread("lena.jpg");
	if (!src.data)
	{
		std::cout << "Image not loaded";
		return -1;
	}
	Mat eye = imread("eye.jpg");
	if (!eye.data)
	{
		std::cout << "Image not loaded";
		return -1;
	}
	cout << "image size: " << src.size << endl;
	Mat GRAY = img2Gray(src);
	Mat RGBY = img2RGBY(src);
	Mat HSV = img2HSV(src);
	Mat CMYK = img2CMYK(src);
	Mat eyePoint = img2point(eye);
	
	imshow("original", src);
	imshow("gray img", GRAY);
	imshow("rgby img", RGBY);
	imshow("hsv img", HSV);
	imshow("cmyk img", CMYK);
	imshow("point on the eye", eyePoint);
	
	waitKey(0);
	return 0;
}

