
//============================================================================
// Name        :
// Author      : Bonnie Bell
// Version     :
// Copyright   : Your copyright notice
// Description : BAlanced AVL Tree
//============================================================================

#include <fstream>
#include <iostream>
#include <cmath>
#include <time.h>
#include <stack>
#include <queue>

#include "AVLTree.h"
#define COUNT 10
using namespace std;


void print2DUtil(AVLTree* root, int space){
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    cout << endl;
    for (int i = COUNT; i < space; i++)
        cout << " ";
    if(root->parent == NULL){
        cout << "h" << root->height << " (" << root->data << ")" << "-|" << "\n";
    }else{
        if(root->data < root->parent->data){
            cout << "h" << root->height << " L(" << root->data << ")" << "-|" << "\n";
        }else{
            cout << "h" << root->height << " R(" << root->data << ")" << "-|" << "\n";
        }
    }
 
    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void print2D(AVLTree* root){
    // Pass initial space count as 0
    cout << endl;
    cout << "****************************************************************************************************" <<endl;
    print2DUtil(root, 0);
    cout << "****************************************************************************************************" <<endl;
    cout << endl;
}




int main() {

    AVLTree* tree1Root = new AVLTree(50, nullptr);
    srand(time(NULL));
    uint32_t numNodes = 100;
    for (uint32_t i=1; i < numNodes; i++ ) {
        tree1Root = tree1Root->insert(( rand() % 10000));
        print2D(tree1Root);

        //Uncomment to help debug lost nodes
//        if (tree1Root->countNodes() != i+1) {
//            std::cout<<"Lost node "<<std::endl;
//            return 1;
//        }

        //uncomment to help debug unbalanced trees
//        tree1Root->updateHeight();
//        if ( ! tree1Root->isBalanced() ) {
//            std::cout<<"Tree1Root balanced: FAILED at node insertion "<<i<<std::endl;
//            return 1;
//        }

    }

    if (tree1Root->countNodes() == numNodes) {
        std::cout<<"tree1Root lost Nodes: PASSED"<<std::endl;
    }
    else {
        std::cout<<"tree1Root lost Nodes: FAILED expected: 100 actual: "<<tree1Root->countNodes()<<std::endl;
    }

    tree1Root->updateHeight();
    float expectedHeight = log2(numNodes) * 1.5;
    if (tree1Root->getHeight() < expectedHeight) {
        std::cout<<"tree1Root height: PASSED"<<std::endl;
    }
    else {
        std::cout<<"tree1Root height: FAILED expected: <" <<expectedHeight<<" actual: "<<tree1Root->getHeight()<<std::endl;
    }

    if ( tree1Root->isBalanced()) {
        std::cout<<"Tree1Root is balanced: PASSED"<<std::endl;
    }
    else {
        std::cout<<"Tree1Root is balanced: FAILED"<<std::endl;
    }
}

