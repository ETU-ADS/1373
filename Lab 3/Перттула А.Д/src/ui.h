//
// Created by theta-sigma on 11/30/2022.
//

#ifndef SRC_UI_H
#define SRC_UI_H

#include <fstream>
#include <string>
#include "BinaryTree.h"
#include "AvlTree.h"

void testsFunction();

void consoleInputString(BinaryTree *&bt);

void parserMessage(AvlTree *&pAvlTree);

void dfsMessage(AvlTree *pAvlTree);

void avlMessage();

void menuMessage();

bool innerDialog();


#endif //SRC_UI_H
