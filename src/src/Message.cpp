//
//  Message.cpp
//  src
//
//  Created by wc on 15/6/10.
//  Copyright (c) 2015年 wc. All rights reserved.
//

#include "Message.h"

// Display the error message and then exit.
void ErrorMsg(const string &errorMsg, bool isExit) {
    cout << errorMsg << endl;
    if (isExit)
        exit(0);
}

void Info(const string &msg) {
    cout << msg << endl;
}