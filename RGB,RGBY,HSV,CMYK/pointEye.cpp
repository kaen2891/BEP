#include "bep1.h"

Mat img2point(Mat eye)
{
	int thickness = 0;
	int lineType = 0;
	int shift = 0;
	
	//draw circle near eye. y axis 70 ~ 140, x axis 70 ~ 140
	circle(eye, Point(70, 70), 32.0, Scalar(255, 255, 255), 10, 8);
	//line into circle, y axis 100 ~ 40
	line(eye, Point(70, 100), Point(70, 40), Scalar(255, 255, 255), thickness = 2, lineType = LINE_8, shift = 0);
	//line into circle, x axis 40 ~ 100
	line(eye, Point(40, 70), Point(100, 70), Scalar(255, 255, 255), thickness = 2, lineType = LINE_8, shift = 0);

	return eye;
}