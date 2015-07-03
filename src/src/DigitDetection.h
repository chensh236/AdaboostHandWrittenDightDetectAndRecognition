//
//  DigitDetection.h
//  src
//
//  Created by wc on 15/6/20.
//  Copyright (c) 2015年 wc. All rights reserved.
//

#ifndef __src__DigitDetection__
#define __src__DigitDetection__

#include <vector>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include "Message.h"

using namespace cv;
using namespace std;

class DigitDetection {
public:
    static DigitDetection* getInstance();
    
    ~DigitDetection();
    
    vector<Rect> detection(Mat &imgGray, const string &xmlFilePath);
    
    void drawDigitsWithValue(Mat &img, vector<Rect> &digits, vector<int> &value,
                    const string &outputImgPath);
    
    vector<Mat> getDigitsAsImage(Mat &img, vector<Rect> &digits);
    
    void saveDigits(Mat &img, vector<Rect> &digits,
                    const string &filePath);
    
private:
    DigitDetection();
    
private:
    static DigitDetection* instance;
};

#endif /* defined(__src__DigitDetection__) */
