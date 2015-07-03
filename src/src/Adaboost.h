//
//  Adaboost.h
//  src
//
//  Created by wc on 15/6/13.
//  Copyright (c) 2015年 wc. All rights reserved.
//

#ifndef __src__Adaboost__
#define __src__Adaboost__

#include <iostream>
#include <vector>
#include <cmath>
#include "CARTDecisionTree.h"
#include "Message.h"

#define STOPTRAINERRORRATE 1e-6

struct WeakClassifier {
    TreeNode _classTree;
    double _alpha;
    
    WeakClassifier(TreeNode classTree = nullptr, double alpha = 0.0) :
    _classTree(classTree), _alpha(alpha) { }
};

class AdaBoost {
public:
    AdaBoost();
    ~AdaBoost();
    
    void train(TreeMat &mat, int numIt = 100);
    Row classify(TreeMat &mat);
private:
    void initD(int size);
    ElementType sign(double value);
private:
    ErrorWeight _D;
    vector<WeakClassifier> weakClassiers;
};

#endif /* defined(__src__Adaboost__) */
