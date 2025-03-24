
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

int AVLTree::getBalance() {
	//insert code here
}

AVLTree* AVLTree::rotateRight() {
	//insert code here
}

AVLTree* AVLTree::rotateLeft() {
	//insert code here
}

AVLTree* AVLTree::rebalance() {
	//insert code here
}

AVLTree* AVLTree::insert(int new_data) {
	//insert code here to insert and rebalance tree
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
