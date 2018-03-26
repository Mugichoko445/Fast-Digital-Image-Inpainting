#include <iostream>
#include <map>
#include <opencv2/opencv.hpp>
#include "FastDigitalImageInpainting.hpp"

std::map<std::string, std::string> path =
{
	{"Image", "data/image.png"},
	{"Mask", "data/mask.png"},
	{"Output", "data/inpaint.png"}
};

void main()
{
	cv::Mat src = cv::imread(path["Image"]);
	cv::Mat mask = cv::imread(path["Mask"]);
	cv::Mat res;

	cv::imshow("src", src);
	cv::imshow("mask", mask);
	cv::waitKey(1);

	std::cout << "inpainting...";
	inpaint(src, mask, K, res, 500);
	std::cout << " done!" << std::endl;

	cv::imwrite(path["Output"], res);
	cv::imshow("Convolutional Inpainting (Result)", res);
	cv::waitKey();
}