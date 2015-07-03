//
//  Tools.h
//  src
//
//  Created by wc on 15/6/20.
//  Copyright (c) 2015年 wc. All rights reserved.
//

#ifndef __src__Tools__
#define __src__Tools__

#include <vector>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include "Message.h"


cv::Mat getGrayImage(cv::Mat &img);
cv::Mat readImage(const std::string &filePath);
std::vector<int> getDataAsVector(cv::Mat &label);
std::vector<cv::Mat> normalizeImage(std::vector<cv::Mat> &images, int aimWidth, int aimHeight);

#endif /* defined(__src__Tools__) */
