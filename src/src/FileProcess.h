//
//  FileProcess.h
//  src
//
//  Created by wc on 15/6/10.
//  Copyright (c) 2015年 wc. All rights reserved.
//

#ifndef __src__FileProcess__
#define __src__FileProcess__

#include <fstream>
#include <iostream>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <cstdio>
#include "Message.h"

using namespace std;
using namespace cv;

#define IMAGESIZE 28

class FileProcesser {
public:
    ~FileProcesser();
    static FileProcesser* getInstance();
    void loadDigit(const string &filePath, vector<Mat> &digits);
    void loadLable(const string &filePath, Mat &lables);
    void showImage(const vector<Mat> &digits, int showNumber = 10);
    void saveImage(const vector<Mat> &digits, const string &filePath);
private:
    int reverseInt4MNIST(const int i);
private:
    FileProcesser();
    static FileProcesser* instance;
};

#endif /* defined(__src__FileProcess__) */
