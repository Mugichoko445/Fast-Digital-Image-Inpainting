#include <iostream>
#include <map>
#include <opencv2/opencv.hpp>
#include "FastDigitalImageInpainting.h"

std::map<std::string, std::string> path =
{
	{"Image", "data/image.png"},
	{"Mask", "data/mask.png"}
};

void main()
{
	cv::Mat src = cv::imread(path["Image"]);
	cv::Mat mask = cv::imread(path["Mask"]);

	cv::imshow("src", src);
	cv::imshow("mask", mask);
	cv::waitKey();

	cv::Mat res;
	inpaint(src, mask, K, res, 500);

	cv::destroyAllWindows();
	cv::imshow("Convolutional Inpainting", res);
	cv::waitKey();
}