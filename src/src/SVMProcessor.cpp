//
//  SVMProcessor.cpp
//  src
//
//  Created by wc on 15/6/10.
//  Copyright (c) 2015年 wc. All rights reserved.
//

#include "SVMProcessor.h"

SVMProcessor* SVMProcessor::instance = nullptr;

SVMProcessor* SVMProcessor::getInstance() {
    if (instance == nullptr)
        instance = new SVMProcessor();
    return instance;
}

SVMProcessor::SVMProcessor() { index  = 0; }

SVMProcessor::~SVMProcessor() {
    if (instance != nullptr)
        delete instance;
}

// Train the svm model with data set.
void SVMProcessor::train(vector<Mat> &digits, Mat& lables) {
    assert(digits.size() != 0);
    
    // If the value of TRAIN is true, it means need to train the
    //      model.
    // Or when the value of TRAIN is false means the model has finished
    //      trained yet. We only need to load the description file.
    if (TRAIN) {
        params.svm_type    = CvSVM::NU_SVC;
        params.kernel_type = CvSVM::POLY; // The kernal type of the svm is polynomial.
        params.term_crit   = cvTermCriteria(CV_TERMCRIT_ITER, 1000, FLT_EPSILON);
        
        params.degree        = CvSVM::POLY;
        params.gamma         = CvSVM::POLY;
        params.coef0         = CvSVM::POLY;
        params.nu            = 0.1;
        params.p             = CvSVM::EPS_SVR;
        Mat trainData = getData(digits);
        svm.train(trainData, lables, Mat(), Mat(), params);
        svm.save("../descriptionFile/SVMtrain.XML");
    } else {
        svm.load("../descriptionFile/SVMtrain.XML");
    }
}

// Make the data set into a Mat paramenter which is the parameter of
//      svm model.
Mat SVMProcessor::getData(vector<Mat> &digits) {
    
    // Each image is 8 * 8 size, which has 64 pixels.
    Mat data = Mat::zeros((int)digits.size(), 64, CV_32FC1);

    for (int i = 0; i < digits.size(); ++i) {
        Mat temp;
        
        // Normalize the image.
        getROI(digits[i], temp);
        
        // Resize the image into 8 * 8.
        Mat dst = Mat::zeros(8, 8, CV_32FC1);
        resize(temp, dst, dst.size());
        int index = 0;
        for (int j = 0; j < 8; ++j) {
            for (int k = 0; k < 8; ++k) {
                data.at<float>(i, index++) = dst.at<float>(j, k);
            }
        }
    }
    return data;
}

// Get the classify value of the test data set.
void SVMProcessor::predict(vector<Mat> &digits, Mat& lables) {
    Mat testData = getData(digits);
    lables.resize(digits.size());
    svm.predict(testData, lables);
}

// Caculate the accuracy rate of the model while test by test data set.
double SVMProcessor::correctRate(Mat &rightLabels, Mat& predictLables) {
    Size lableSize = rightLabels.size();
    
    assert(lableSize.width != 0 && lableSize.height != 0);
    
    int correctNum = 0;
    
    for (int i = 0; i < lableSize.height; ++i) {
        for (int j = 0; j < lableSize.width; ++j) {
            if (rightLabels.at<float>(i, j) == predictLables.at<float>(j, i))
                ++correctNum;
        }
    }
    
    return (float)(correctNum) / (float)(lableSize.width * lableSize.height);
}

// Normalize the image.
// First get the number part of the image, and then make the image into
//      square.
void SVMProcessor::getROI(Mat& src, Mat& dst){
    src.convertTo(src, CV_32FC1);
    
    int left, right, top, bottom;
    
    // The four peak of the image.
    left = src.cols; right = 0;
    top = src.rows; bottom = 0;
    
    for(int i = 0; i < src.rows; i++)
    {
        for(int j = 0; j < src.cols; j++)
        {
            if(src.at<float>(i, j) != 0)
            {
                // Get the image part.
                if(j < left) left = j;
                if(j > right) right = j;
                if(i < top) top = i;
                if(i > bottom) bottom = i;
            }
        }
    }
    
    int width = right - left + 1;
    int height = bottom - top + 1;
    
    // The number part of the image.
    Rect dstRect(left, top, width, height);
    dst = src(dstRect);
    
    // Make the image into a square with the number in center.
    int edeg = width > height ? width : height;
    Mat dstTemp = Mat::zeros(edeg, edeg, CV_32FC1);
    int wIndex = (edeg - width) / 2;
    int hIndex = (edeg - height) / 2;
    for (int i = hIndex; i < edeg - hIndex; ++i) {
        for (int j = wIndex; j < edeg - wIndex; ++j) {
            dstTemp.at<float>(i, j) = dst.at<float>(i - hIndex, j - wIndex);
        }
    }
    dst = dstTemp;
}












