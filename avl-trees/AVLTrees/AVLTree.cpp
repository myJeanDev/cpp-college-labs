
//============================================================================
// Name        : AVLTree
// Author      : Bonnie Bell
// Version     :
// Copyright   : Your copyright notice
// Description : AVL Tree functions
//============================================================================

/*
-The functions you will need are stubbed out in the AVLTree header file.
 -Specifically you need to implement the insert function that will insert a new value and rebalance the tree if neccesary.
 -In order to test for balance you will need to implement the getBalance() function.
 -In order to rebalance it will be neccesary for you to implement both the rotateRight() and rotateLeft() functions.
 -I have gotten you started with a 10 element tree - you should try out larger numNodes to insure that your code is functioning as intended at higher values of n once you are done developing. Do not edit the function headers.
 -Do not use global variables.
 -Any algorithms that operate on more than one level of the tree should be recursive in nature.
 */

#include "AVLTree.h"
#include <iostream>
using namespace std;

//already implemented helper functions
//*****************************************************
AVLTree::AVLTree(int t_data, AVLTree* t_parent, AVLTree* t_left, AVLTree* t_right) {
    data = t_data;
    height = 0;
    parent = t_parent;
    left = t_left;
    right = t_right;
}

bool AVLTree::isLeaf() {
    return ((left == nullptr) and (right == nullptr));
}

uint32_t AVLTree::getHeight() {
    return height;
}
//******************************************************



//Run on any node to get its balance
int AVLTree::getBalance() {
    int leftHeight = 0;
    int rightHeight = 0;
    if(left != NULL){
        leftHeight = left->getHeight();
    }
    if(right != NULL){
        rightHeight = right->getHeight();
    }
    int balanceFactor = leftHeight - rightHeight;
    return balanceFactor;
}

AVLTree* AVLTree::rotateRight() {
    cout << "rotating right" << endl;
    AVLTree *x = this->left;
    AVLTree *t = x->right;
      
        // Perform rotation
        x->right = this;
        this->left = t;
      
        //Update node's new height
        this->updateHeight();
        x->updateHeight();
      
        //Return the new root
        return x;
}

AVLTree* AVLTree::rotateLeft() {
    cout << "rotating left" << endl;
    AVLTree *y = this->right;
    AVLTree *t = y->left;
  
    // Perform rotation
    y->left = this;
    this->right = t;
  
    // Update node's new heights
    this->updateHeight();
    y->updateHeight();
  
    //Return new root
    return y;
}

AVLTree* AVLTree::rebalance() {
    //left heavy
    if (this->getBalance() == -2) {//get's balance of the node
          // Left-Left case.
        int leftBalance = 0;
        if(this->left != NULL){
            leftBalance = this->left->getBalance();
        }
          if (leftBalance <= 0) {//gets balance of the node's left child, need a case for when child is NULL
                cout << "requires (LEFT LEFT)" << endl;
                return this->rotateRight();

            // Left-Right case.
          } else {
                cout << "requires (LEFT RIGHT)" << endl;
                this->left = this->left->rotateLeft();
                return this->rotateRight();
          }

          // Right heavy
        } else if (this->getBalance() == 2) {
          // Right-Right case.
            int rightBalance = 0;
            if(this->right != NULL){
                rightBalance = this->right->getBalance();
            }
          if (rightBalance >= 0) {
                cout << "requires (RIGHT RIGHT)" << endl;
                return this->rotateLeft();

            // Right-Left case.
          }else{
            cout << "requires (RIGHT LEFT)" << endl;
            this->right = this->right->rotateRight();
            return this->rotateLeft();
          }
        }
    cout <<"NEW ROOT: " << this->data << endl;
        return this;
}


//Must be able to handle duplicates
AVLTree* AVLTree::insert(int new_data) {

    //Inserting the new node
    if(new_data < data){
        cout << data << endl;
        
        //LEFT INSERT
        if(left == NULL){//if we go left and there is an open spot, insert new node
            cout << data << "INSRT->(" << new_data << ")"<<endl;
            left = new AVLTree(new_data, this, NULL, NULL);
        }else{//Otherwise call this function on the next child
            left = left->insert(new_data);
        }
    }else{
        //RIGHT INSERT
        if(right == NULL){//if we go right and there is an open spot, insert new node
            cout << "INSRT: " << data << "->(" << new_data << ")"<<endl;
            right = new AVLTree(new_data, this, NULL, NULL);
        }else{//Otherwise call this function on the next child
            right = right->insert(new_data);
        }
    }
    //Update the height and balance of the tree, because we altered it
    this->updateHeight();
    //return the new root of the tree after all changes have been made
    return this->rebalance();
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

//This is a function called on a node, it returns nothing, it updates the node's height variable
void AVLTree::updateHeight() {
    if (isLeaf()) {//if the node has no children it is at height 0, the lowest height
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
