
//============================================================================
// Name        : AVLTree
// Author      : Bonnie Bell
// Version     :
// Copyright   : Your copyright notice
// Description : AVL Tree functions
//============================================================================
#include "AVLTree.h"
#include <iostream>
using namespace std;
//************** already implemented helper functions

//This is our node structure
AVLTree::AVLTree(int t_data, AVLTree* t_parent, AVLTree* t_left, AVLTree* t_right) {
    data = t_data;
    height = 0;
    parent = t_parent;
    left = t_left;
    right = t_right;
}

//checks to see if node has no children
bool AVLTree::isLeaf() {
    return ((left == nullptr) and (right == nullptr));
}

//simple getter function
uint32_t AVLTree::getHeight() {
    return height;
}
//******************************************************

//CORRECT, working as intended
//NULL nodes are a height of -1
int AVLTree::getBalance() {
    int leftHeight = -1;
    int rightHeight = -1;
    //check if getHeight can be called on left
    if(left != NULL){
        leftHeight = left->getHeight();
    }
    //check if getHeight can be called on left
    if(right != NULL){
        rightHeight = right->getHeight();
    }
    //negative is right heavy
    //positive is left heavy
    return leftHeight - rightHeight;
}

//CORRECT, this is working as intended.
AVLTree* AVLTree::rotateRight() {
    AVLTree* newParent = left;
    left = newParent->right;
    newParent->right = this;
    
    //updating heights
    this->updateHeight();
    newParent->updateHeight();
    
    return newParent;
}

//CORRECT, this is working as intended.
AVLTree* AVLTree::rotateLeft() {
    AVLTree* newParent = right;
    right = newParent->left;
    newParent->left = this;
    
    //updating heights
    this->updateHeight();
    newParent->updateHeight();

    return newParent;
}

//CHECK BALANCE
//CHECK CASES
//ROTATE
//Possible issues, left right, and right left cases sometimes do not fire
AVLTree* AVLTree::rebalance() {
    int balance = this->getBalance();
    
    //LEFT HEAVY
    if (balance > 1) {
        //CASE: left-right, rotate left then right
        if (left->getBalance() < 0) {
            left = this->left->rotateLeft();
            return this->rotateRight();
        }
        //Otherwise left left, so rotate right
        return this->rotateRight();
    }
    
    //RIGHT HEAVY
    if (balance < -1) {
        //CASE: right-left, rotate right, then left
        if (right->getBalance() > 0) {
            right = this->right->rotateRight();
            return this->rotateLeft();
        }
        //Otherwise right right, so rotate left
        return this->rotateLeft();
    }
    
    //return the node unchanged
    return this;
}

//INSERT
//UPDATE HEIGHT
//REBALANCE
//RETURN
AVLTree* AVLTree::insert(int new_data) {
    AVLTree* newNode = new AVLTree(new_data);

    //CORRECT, this functions like a normal BST insert
    if (new_data < data){
        if (left == NULL){
            left = newNode;
            newNode->parent = this;
        }else{
            left = left->insert(new_data);//continue to search for an empty spot
        }
    }else{
        if(right == NULL){
            right = newNode;
            newNode->parent = this;
        }else{
            right = right->insert(new_data);//continue to search for an empty spot
        }
    }
    //update the heights after insert
    this->updateHeight();
    
    //Rebalance the new tree
    return rebalance();
}

//***************************
//Do not edit code below here
uint32_t AVLTree::countNodes() {
    if (isLeaf()) {
        return 1;
    }
    if (left != nullptr) {
        if (right != nullptr) {
            return 1 + left->countNodes() + right->countNodes();
        }
        return 1+ left->countNodes();
    }
    return 1 + right->countNodes();
}

void AVLTree::updateHeight() {
    if (isLeaf()) {
        height = 0;
        return;
    }
    if (left != nullptr) {
        left->updateHeight();
        if (right != nullptr) {
            right->updateHeight();
            height = (1 + max(left->getHeight(), right->getHeight()));
            return;
        }
        height = 1 + left->getHeight();
        return;
    }
    right->updateHeight();
    height = 1 + right->getHeight();
    return;
}

bool AVLTree::isBalanced() {
    if ( isLeaf() ) {
        return true;
    }
    updateHeight();
    if (left == nullptr) {
        return ( right->getHeight() < 1 );
    }
    if (right == nullptr) {
        return ( left->getHeight() < 1 );
    }
    return ( left->isBalanced() and right->isBalanced() and (getBalance() < 2) and (getBalance() > -2) );
}
