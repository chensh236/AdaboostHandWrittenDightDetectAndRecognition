//
//  DesionTree.h
//  RandomForest
//
//  Created by wc on 15/6/10.
//  Copyright (c) 2015年 wc. All rights reserved.
//

#ifndef __RandomForest__DesionTree__
#define __RandomForest__DesionTree__

#include <vector>
#include <string>
#include <stack>
#include <map>
#include <vector>
#include <cmath>
#include <assert.h>
#include "Message.h"

#define NUMSTEP 10.0

using namespace std;

typedef double ElementType;
typedef vector<ElementType> Row;
typedef vector<Row> TreeMat;
typedef vector<double> ErrorWeight;

struct Node {
    ElementType _threshod;
    int _featureIndex;
    bool _inequal;  // _inequal == true means label = -1 when feature <= threshold
                    // _inequal == false means label = -1 when feature > threshold
    
    Node(ElementType threshod = 0, int featureIndex = 0, bool inequal = false) :
    _threshod(threshod), _featureIndex(featureIndex), _inequal(inequal) { }
};

typedef Node* TreeNode;

class CARTDecisionTree {
public:
    ~CARTDecisionTree();
    static CARTDecisionTree* getInstance();
    TreeNode getBestTree(TreeMat &mat, ErrorWeight &D, Row &bestPredictLabel, double &minErrorRate);
    Row getClassifyLabel(TreeMat &mat, int featureIndex, ElementType &threshold, bool inequal);
private:
    CARTDecisionTree();
    
    TreeNode getMinErrorTreeOfOneFeature(TreeMat &mat,
                                         ErrorWeight &D, int featureIndex,
                                         double &errorRate, Row &predictLabel);
    
    double getWeightErrorrate(TreeMat &mat, Row &predictLabel, ErrorWeight &D);
    
    void getMinFeatureValue(TreeMat &mat, int featureIndex,
                            ElementType &min, ElementType &max);
private:
    static CARTDecisionTree* instance;
    vector<bool> inequalList;
};



#endif /* defined(__RandomForest__DesionTree__) */
