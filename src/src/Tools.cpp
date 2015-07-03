//
//  Tools.cpp
//  src
//
//  Created by wc on 15/6/20.
//  Copyright (c) 2015年 wc. All rights reserved.
//

#include "Tools.h"

// Get the binary image of the source image.
cv::Mat getGrayImage(cv::Mat &img) {
    cv::Mat imgGray;
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
    cv::threshold(imgGray, imgGray, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    cv::bitwise_not(imgGray, imgGray);
    
    return imgGray;
}

// Get image from file.
cv::Mat readImage(const std::string &filePath) {
    cv::Mat img = cv::imread(filePath);
    if (img.empty()){
        Info("[ERROR] : please check your image file name.");
        exit(0);
    }
    
    return img;
}

// Get the data in Mat into a vector.
std::vector<int> getDataAsVector(cv::Mat &label) {
    vector<int> digitsValueList;
    for (int i = 0; i < label.size().height; ++i) {
        for (int j = 0; j < label.size().width; ++j) {
            digitsValueList.push_back(label.at<float>(j, i));
        }
    }
    
    return digitsValueList;
}

// Normalize the image.
// Make the image into aim size.
std::vector<cv::Mat> normalizeImage(std::vector<cv::Mat> &images, int aimWidth, int aimHeight) {
    std::vector<cv::Mat> dstImages;
    for (int i = 0; i < images.size(); ++i) {
        cv::Mat aimImg;
        cv::resize(images[i], aimImg, cv::Size(aimWidth, aimHeight));
        dstImages.push_back(aimImg);
    }
    
    return dstImages;
}