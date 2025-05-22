/*
 * Node.h
 *
 *  Created on: Jan 30, 2021
 *      Author: cj6bo
 */
#include <iostream>

class Node {
    public:
        int data;
        Node* left;
        Node* right;
        Node(int data, Node* left=nullptr, Node* right=nullptr);
        bool isLeaf();
        void insert(int data);
        bool isFull();
        int height();
        int countNodes();
};
