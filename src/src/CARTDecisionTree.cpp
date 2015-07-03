//
//  DesionTree.cpp
//  RandomForest
//
//  Created by wc on 15/6/10.
//  Copyright (c) 2015年 wc. All rights reserved.
//

#include "CARTDecisionTree.h"

CARTDecisionTree* CARTDecisionTree::instance = nullptr;

CARTDecisionTree* CARTDecisionTree::getInstance() {
    if (instance == nullptr)
        instance = new CARTDecisionTree();
    return instance;
}

CARTDecisionTree::CARTDecisionTree() {
    inequalList.clear();
    inequalList.push_back(true);
    inequalList.push_back(false);
}

CARTDecisionTree::~CARTDecisionTree() {}


Row CARTDecisionTree::getClassifyLabel(TreeMat &mat, int featureIndex,
                                   ElementType &threshold, bool inequal) {
    Row returnLabel(mat.size(), 1);
    
    for (int i = 0; i < mat.size(); ++i) {
        if (inequal) {
            if (mat[i][featureIndex] <= threshold) {
                returnLabel[i] = -1;
            }
        } else {
            if (mat[i][featureIndex] > threshold) {
                returnLabel[i] = -1;
            }
        }
    }
    
    return returnLabel;
}

TreeNode CARTDecisionTree::getBestTree(TreeMat &mat, ErrorWeight &D,
                                       Row &bestPredictLabel, double &minErrorRate) {
    assert(mat.size() > 0);
    
    TreeNode treeReturn = nullptr;
    
    minErrorRate = HUGE_VAL;
    int featureSize = (int)mat[0].size() - 1;
    for (int i = 0; i < featureSize; ++i) {
        double errorRateTemp = HUGE_VAL;
        Row predictLabel;
        TreeNode TreeTemp = getMinErrorTreeOfOneFeature(mat, D, i, errorRateTemp, predictLabel);
        if (minErrorRate > errorRateTemp) {
            minErrorRate = errorRateTemp;
            bestPredictLabel = predictLabel;
            if (treeReturn != nullptr) {
                delete treeReturn;
            }
            treeReturn = TreeTemp;
        } else {
            delete TreeTemp;
        }
    }
    
    return treeReturn;
}

TreeNode CARTDecisionTree::getMinErrorTreeOfOneFeature(TreeMat &mat,
                                     ErrorWeight &D, int featureIndex,
                                                   double &errorRate, Row &predictLabel) {
    assert(mat.size() > 0);
    predictLabel.clear();
    
    ElementType min;
    ElementType max;
    TreeNode newTree = new Node();
    
    getMinFeatureValue(mat, featureIndex, min, max);
    
    ElementType stepSize = (max - min) / NUMSTEP;
    
    for (int i = -1; i < NUMSTEP + 1; ++i) {
        for (auto inequal : inequalList) {
            ElementType threshod = min + (double)i * stepSize;
            Row predictResult = getClassifyLabel(mat, featureIndex, threshod, inequal);
            double errorRatetemp = getWeightErrorrate(mat, predictResult, D);
            if (errorRate > errorRatetemp) {
                errorRate = errorRatetemp;
                predictLabel = predictResult;
                newTree->_threshod = i;
                newTree->_inequal = inequal;
                newTree->_featureIndex = featureIndex;
            }
        }
    }
    return newTree;
}

double CARTDecisionTree::getWeightErrorrate(TreeMat &mat, Row &predictLabel, ErrorWeight &D) {
    assert(mat.size() > 0);
    
    double weightErrorRate = 0.0;
    int labelIndex = (int)mat[0].size() - 1;
    
    for(int i = 0; i < mat.size(); ++i) {
        if (mat[i][labelIndex] != predictLabel[i]) {
            weightErrorRate += D[i];
        }
    }
    
    return weightErrorRate;
}

void CARTDecisionTree::getMinFeatureValue(TreeMat &mat, int featureIndex,
                                          ElementType &min, ElementType &max) {
    min = HUGE_VAL;
    max = -HUGE_VAL;
    
    for (auto row : mat) {
        if (row[featureIndex] < min)
            min  = row[featureIndex];
        
        if (row[featureIndex] > max)
            max = row[featureIndex];
    }
}





