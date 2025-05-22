/*
 * AVLTree.h
 *
 *  Created on: Jan 30, 2021
 *      Author: cj6bo
 */
#include <iostream>

class AVLTree {
    public:
        int data;
        uint32_t height;
        AVLTree* parent;
        AVLTree* left;
        AVLTree* right;

        //base functions defined for you
        AVLTree(int data, AVLTree* parent=nullptr, AVLTree* left=nullptr, AVLTree* right=nullptr);
        bool isLeaf();
        uint32_t getHeight();

        //*******************
        //functions you need to define

        //insert a node and rebalance tree to maintain AVL balanced tree
        //return new root of tree
        AVLTree* insert(int data);

        //computes a node's balance factor by subtracting the right subtree height from the left subtree height.
        int getBalance();

        //checks for imbalance and rebalances if neccessary
        //return new root of tree
        AVLTree* rebalance();


        //implement a right rotate
        //return new root of tree
        AVLTree* rotateRight();

        //implement a left rotate
        //return new root of tree
        AVLTree* rotateLeft();

        //Do not edit these three functions
        bool isBalanced();
        uint32_t countNodes();
        void updateHeight();
};
