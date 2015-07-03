//
//  DigitDetection.cpp
//  src
//
//  Created by wc on 15/6/20.
//  Copyright (c) 2015年 wc. All rights reserved.
//

#include "DigitDetection.h"

DigitDetection* DigitDetection::instance = nullptr;

DigitDetection* DigitDetection::getInstance() {
    if (instance == nullptr)
        instance = new DigitDetection();
    
    return instance;
}

DigitDetection::DigitDetection() { }

DigitDetection::~DigitDetection() {
    if (instance != nullptr)
        delete instance;
}

// Detect the image to get the digit part of the image.
vector<Rect> DigitDetection::detection(Mat &imgGray, const string &xmlFilePath) {
    vector<Rect> digits;
    CascadeClassifier digitsCascade;
    digitsCascade.load(xmlFilePath);
    digitsCascade.detectMultiScale(imgGray, digits, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30) );
    
    return digits;
}

// Write the digits into image independently.
void DigitDetection::saveDigits(Mat &img, vector<Rect> &digits,
                                const string &outputImgPath) {
    int digitsNum = 0;
    for (auto digit : digits) {
        string saveName = outputImgPath + string("digit_") + to_string(digitsNum++) + string(".jpg");
        Rect roi = digit;
        imwrite(saveName, img(roi));
    }
}

// Get the digits part from source image as small images.
vector<Mat> DigitDetection::getDigitsAsImage(Mat &img, vector<Rect> &digits) {
    vector<Mat> digitsImg;
    for (auto digit : digits) {
        Rect roi = digit;
        digitsImg.push_back(img(roi));
    }
    
    return digitsImg;
}

// In the position of image where has digit, draw the digit's value and an ellipse into the image.
void DigitDetection::drawDigitsWithValue(Mat &img, vector<Rect> &digits, vector<int> &value,
                         const string &outputImgPath) {
    CvFont font;
    char showMsg[2];
    showMsg[1] = '\0';
    
    for (int i = 0; i < value.size(); ++i) {
        showMsg[0] = (char)(value[i] + '0');
        cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX | CV_FONT_ITALIC, 1, 1, 0, 1);
        
        // Draw the digit's value into image.
        putText(img, showMsg, Point(digits[i].x + digits[i].size().width / 2,
                                    digits[i].y + digits[i].size().height),
                FONT_HERSHEY_COMPLEX_SMALL, 1, cvScalar(0, 0, 255), 1, CV_AA);
        
        // Draw an ellipse into the image.
        Point center(digits[i].x + digits[i].width / 2, digits[i].y + digits[i].height / 2);
        ellipse(img, center, Size(digits[i].width / 2, digits[i].height / 1.5),
                0, 0, 360, Scalar(0, 255, 0), 2, 8, 0);
    }
    
    imwrite(outputImgPath, img);
}