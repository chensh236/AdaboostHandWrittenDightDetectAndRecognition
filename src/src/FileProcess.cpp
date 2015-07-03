//
//  FileProcess.cpp
//  src
//
//  Created by wc on 15/6/10.
//  Copyright (c) 2015年 wc. All rights reserved.
//

#include "FileProcess.h"

FileProcesser* FileProcesser::instance = nullptr;

FileProcesser::~FileProcesser() {
    if (instance != nullptr) {
        delete instance;
    }
}

FileProcesser* FileProcesser::getInstance() {
    if (instance == nullptr)
        instance = new FileProcesser();
    
    return instance;
}

FileProcesser::FileProcesser() { }

// Get the data from binary file and convert the data into
//      Mat format.
void FileProcesser::loadDigit(const string &filePath, vector<Mat> &digits) {
    FILE *file = fopen(filePath.c_str(), "rb");
    
    if (file == NULL)
        ErrorMsg(string("Can not open file ") + filePath, true);
    
    // Get the magic number of the file.
    int magic, numImages, rows, cols;
    fread(&magic, sizeof(magic), 1, file);
    magic = reverseInt4MNIST(magic);
    
    if (magic != 2051)
        ErrorMsg(string("The magic number of file ") + filePath + " is wrong!", true);
    
    // Get the description message of the file.
    fread(&numImages, sizeof(int), 1, file);
    fread(&rows, sizeof(int), 1, file);
    fread(&cols, sizeof(int), 1, file);
    
    numImages = reverseInt4MNIST(numImages);
    rows = reverseInt4MNIST(rows);
    cols = reverseInt4MNIST(cols);

    digits.resize(numImages);
    for (int i = 0; i < numImages; ++i)
        digits[i] = Mat::zeros(Size(rows, cols), CV_8UC1);
    
    // Convert the data type of image data from int into float
    for (int i = 0; i < numImages; ++i) {
        fread(digits[i].data, sizeof(uchar), rows * cols, file);
        digits[i].convertTo(digits[i], CV_32FC1);
    }
    
    fclose(file);
}

// Get the label of the image from binary file.
void FileProcesser::loadLable(const string &filePath, Mat &lables) {
    FILE* file = fopen(filePath.c_str(), "rb");
    
    if(file == NULL)
        ErrorMsg(string("Can not open file ") + filePath, true);
    
    int magic, numImages;
    fread(&magic, sizeof(magic), 1, file);
    magic = reverseInt4MNIST(magic);
    
    if (magic != 2049)
        ErrorMsg(string("The magic number of file ") + filePath + " is wrong!", true);
    
    fread(&numImages, sizeof(int), 1, file);
    numImages = reverseInt4MNIST(numImages);
    
    lables = Mat::zeros(1, numImages, CV_8UC1);
    fread(lables.data, sizeof(uchar), numImages, file);
    lables.convertTo(lables, CV_32FC1);
    
    fclose(file);
}

// Chose some digits from data set randomly and display them
//      display them in an image.
void FileProcesser::showImage(const vector<Mat> &digits, int showNumber) {
    vector<int> index(digits.size(), CV_8UC1);
    for (int i = 0; i < digits.size(); ++i) {
        index[i] = i;
    }
    srand((uchar)time(NULL));
    std::random_shuffle(index.begin(), index.end());
    
    int sr = 0;
    int sc = -1;
    int numPerRow = ceil(sqrt(showNumber));
    Mat showed(numPerRow * IMAGESIZE, numPerRow * IMAGESIZE, digits[0].type());
    
    // Group them into an image.
    for (int i = 0; i < showNumber; i++) {
        sr = i % numPerRow;
        if (sr == 0) sc += 1;
        digits[index[i]].copyTo(showed(Range(sr * IMAGESIZE, (sr + 1) * IMAGESIZE), Range(sc * IMAGESIZE, (sc + 1) * IMAGESIZE)));
    }
    imwrite("randomdigits.png", showed);
    
    index.clear();
    showed.release();

}

// Write the digits as image indipendently.
void FileProcesser::saveImage(const vector<Mat> &digits, const string &filePath) {
    int imageIndex = 0;
    for (auto image : digits) {
        string fileName = filePath + string("Image_")
                        + to_string(imageIndex++) + string(".bmp");
        Mat showed(IMAGESIZE, IMAGESIZE, image.type());
        image.copyTo(showed);
        imwrite(fileName, showed);
    }
}

// Reverse the number from binary format into decimal base
int FileProcesser::reverseInt4MNIST(const int i)
{
    uchar ch1, ch2, ch3, ch4;
    ch1 = i & 255;
    ch2 = (i >> 8) & 255;
    ch3 = (i >> 16) & 255;
    ch4 = (i >> 24) & 255;
    return ((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}