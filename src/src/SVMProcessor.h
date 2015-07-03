//
//  SVMProcessor.h
//  src
//
//  Created by wc on 15/6/10.
//  Copyright (c) 2015年 wc. All rights reserved.
//

#ifndef __src__SVMProcessor__
#define __src__SVMProcessor__

#include <opencv2/ml/ml.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/gpu/gpu.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace cv;

#define TRAIN false

class SVMProcessor {
public:
    ~SVMProcessor();
    
    static SVMProcessor* getInstance();
    void train(vector<Mat> &digits, Mat& lables);
    void predict(vector<Mat> &digits, Mat& lables);
    
    double correctRate(Mat &rightLabels, Mat& predictLables);
private:
    SVMProcessor();
    
    Mat getData(vector<Mat> &digits);
    void getROI(Mat& src, Mat& dst);
private:
    CvSVMParams params;
    CvSVM svm;
    
    int index;
    
    static SVMProcessor* instance;
};

#endif /* defined(__src__SVMProcessor__) */
