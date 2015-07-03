//
//  Adaboost.cpp
//  src
//
//  Created by wc on 15/6/13.
//  Copyright (c) 2015年 wc. All rights reserved.
//

#include "Adaboost.h"

AdaBoost::AdaBoost() {
    weakClassiers.clear();
}

AdaBoost::~AdaBoost() {
    for (auto weakClassifier : weakClassiers) {
        delete weakClassifier._classTree;
    }
    weakClassiers.clear();
}

void AdaBoost::train(TreeMat &mat, int numIt) {
    assert(mat.size() > 0);
    
    int matSize = (int)mat.size();
    
    // Initialize of data set weight list D
    initD(matSize);
    
    int labelIndex = (int)mat[0].size() - 1;
    
    vector<double> addClassEst(matSize, 0);
    while (numIt--) {
        Row bestPredictLabel;
        double minErrorRate;
        TreeNode tree = CARTDecisionTree::getInstance()->getBestTree(mat, _D, bestPredictLabel, minErrorRate);
        double alpha = 0.5 * log((1.0 - minErrorRate) / max(minErrorRate, 1e-16));
        WeakClassifier weakClassifier(tree, alpha);
        weakClassiers.push_back(weakClassifier);

        // updata D
        for (int i = 0; i < _D.size(); ++i) {
            _D[i] = _D[i] * exp((-alpha) * mat[i][labelIndex] * bestPredictLabel[i]);
        }
        double Z = 0.0;
        for (auto d : _D)
            Z += d;
        for (int i = 0; i < _D.size(); ++i) {
            _D[i] /= Z;
        }
        
        // update adaboost classifier classify value of data set
        
        for (int i = 0; i < matSize; ++i) {
            addClassEst[i] += alpha * bestPredictLabel[i];
            //cout << "alpha * bestPredictLabel[i]: " << addClassEst[i] << endl;
        }
        
        
        int errorNum = 0;
        for (int i = 0; i < matSize; ++i) {
            if (sign(addClassEst[i]) != mat[i][labelIndex])
                errorNum += 1;
        }
        //cout << "errorNum: " << errorNum << endl;
        double errorRate = (double)errorNum / (double)matSize;
        Info(string("Error rate: " + to_string(errorRate)));
        if (errorRate < STOPTRAINERRORRATE)
            break;
    }
}

Row AdaBoost::classify(TreeMat &mat) {
    Row result(mat.size(), 0);
    int matSize = (int)mat.size();
    
    for (auto weakClassifier : weakClassiers) {
        Row restemp = CARTDecisionTree::getInstance()->getClassifyLabel(mat,
                                                                        weakClassifier._classTree->_featureIndex,
                                                                        weakClassifier._classTree->_threshod,
                                                                        weakClassifier._classTree->_inequal);
        for (int i = 0; i < matSize; ++i) {
            result[i] += weakClassifier._alpha * restemp[i];
        }
    }
    
    for (int i = 0; i < result.size(); ++i)
        result[i] = sign(result[i]);
    
    return result;
}

void AdaBoost::initD(int size) {
    double val = 1.0 / (double)size;
    _D.clear();
    
    for (int i = 0; i < size; ++i)
        _D.push_back(val);
}

ElementType AdaBoost::sign(double value) {
    if (value < 0)
        return -1;
    return 1;
}