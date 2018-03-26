#pragma once

#include <opencv2/opencv.hpp>

static const float a(0.073235f);
static const float b(0.176765f);
static const cv::Mat K = (cv::Mat_<float>(3, 3) << a, b, a, b, 0.0f, b, a, b, a);

void inpaint(const cv::Mat &src, const cv::Mat &mask, const cv::Mat kernel, cv::Mat &dst, int maxNumOfIter = 100)
{
	assert(src.type() == mask.type() && mask.type() == CV_8UC3);
	assert(src.size() == mask.size());
	assert(kernel.type() == CV_32F);

	// fill in the missing region with the input's average color
	auto avgColor = cv::sum(src) / (src.cols * src.rows);
	cv::Mat avgColorMat(1, 1, CV_8UC3);
	avgColorMat.at<cv::Vec3b>(0, 0) = cv::Vec3b(avgColor[0], avgColor[1], avgColor[2]);
	cv::resize(avgColorMat, avgColorMat, src.size(), 0.0, 0.0, cv::INTER_NEAREST);
	cv::Mat result = (mask / 255).mul(src) + (1 - mask / 255).mul(avgColorMat);

	// convolution
	int bSize = K.cols / 2;
	cv::Mat kernel3ch, inWithBorder;
	result.convertTo(result, CV_32FC3);
	cv::cvtColor(kernel, kernel3ch, cv::COLOR_GRAY2BGR);

	cv::copyMakeBorder(result, inWithBorder, bSize, bSize, bSize, bSize, cv::BORDER_REPLICATE);
	cv::Mat resInWithBorder = cv::Mat(inWithBorder, cv::Rect(bSize, bSize, result.cols, result.rows));

	const int ch = result.channels();
	for (int itr = 0; itr < maxNumOfIter; ++itr)
	{
		cv::copyMakeBorder(result, inWithBorder, bSize, bSize, bSize, bSize, cv::BORDER_REPLICATE);

		for (int r = 0; r < result.rows; ++r)
		{
			const uchar *pMask = mask.ptr(r);
			float *pRes = result.ptr<float>(r);
			for (int c = 0; c < result.cols; ++c)
			{
				if (pMask[ch * c] == 0)
				{
					cv::Rect rectRoi(c, r, K.cols, K.rows);
					cv::Mat roi(inWithBorder, rectRoi);

					auto sum = cv::sum(kernel3ch.mul(roi));
					pRes[ch * c + 0] = sum[0];
					pRes[ch * c + 1] = sum[1];
					pRes[ch * c + 2] = sum[2];
				}
			}
		}

		// for debugging
		cv::imshow("Inpainting...", result / 255.0f);
		cv::waitKey(1);
	}

	result.convertTo(dst, CV_8UC3);
}