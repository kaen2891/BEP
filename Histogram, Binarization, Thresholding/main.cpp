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


	return 0;
}