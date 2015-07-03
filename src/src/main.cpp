//
//  main.cpp
//  src
//
//  Created by wc on 15/6/10.
//  Copyright (c) 2015年 wc. All rights reserved.
//

#include <iostream>
#include "FileProcess.h"
#include "SVMProcessor.h"
#include "Message.h"
#include "DigitDetection.h"
#include "Tools.h"

#define TEST false

void trainSvm() {
    Info("Training svm...");
    vector<cv::Mat> trainData, testData;
    cv::Mat trainLables, testLables, predictLables;
    
    Info("Loading data...");
    FileProcesser::getInstance()->loadDigit("../data/train-images.idx3-ubyte", trainData);
    FileProcesser::getInstance()->loadDigit("../data/t10k-images.idx3-ubyte", testData);
    FileProcesser::getInstance()->loadLable("../data/train-labels.idx1-ubyte", trainLables);
    FileProcesser::getInstance()->loadLable("../data/t10k-labels.idx1-ubyte", testLables);
    
    Info("Finish Loaded data\nTraining...");
    SVMProcessor::getInstance()->train(trainData, trainLables);
    Info("Finish training svm...");
    
    if (TEST) {
        Info("Finish Training\nTesting...");
        SVMProcessor::getInstance()->predict(testData, predictLables);
        Info("Finish Test!\nGetting the correct rate...");
        
        double correctRate = SVMProcessor::getInstance()->correctRate(testLables, predictLables);
        
        Info(string("The accuracy rate of SVM is: ") + to_string(correctRate));
    }
}

void testDigitDetection(vector<string> &filePaths) {
    // Train svm classifier
    trainSvm();
    
    // process each image
    for (auto file : filePaths) {
        Mat image = readImage(string("../image/") + file);
        Mat grayImg = getGrayImage(image);
        vector<Rect> digits = DigitDetection::getInstance()->detection(grayImg, "../descriptionFile/trainout.xml");
        vector<Mat> digitsImages = DigitDetection::getInstance()->getDigitsAsImage(grayImg, digits);
        Mat digitsValue;
        
        // Normalize image to standard size [28 * 28]
        vector<Mat> dstImages = normalizeImage(digitsImages, 28, 28);
        
        // Get the recognize result.
        SVMProcessor::getInstance()->predict(dstImages, digitsValue);
        vector<int> digitsValueList = getDataAsVector(digitsValue);
        
        DigitDetection::getInstance()->drawDigitsWithValue(image, digits, digitsValueList, string("../result/") + file);
    }
}


int main(int argc, const char * argv[]) {
    
    if (argc < 2) {
        ErrorMsg("Input format: [main] [image path list]", true);
    }
    
    vector<string> failePaths;
    for (int i = 1; i < argc; ++i) {
        failePaths.push_back(argv[i]);
    }
    testDigitDetection(failePaths);
    
    return 0;
}
