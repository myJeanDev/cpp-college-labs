#include "Node.h"
#include <iostream>
using namespace std;

//Constructor Function with Arguments
Node::Node(int t_data, Node* t_left, Node* t_right) {
    data = t_data;
    left = t_left;
    right = t_right;
}

//Called on the root
void Node::insert(int new_data) {
    //This function will check the node's data to see if the new data should go left or right
    //If there is no child a new node will be placed there
    //If there is a child in the position insert() will be called on that child
    //Repeat the steps until there is no child and insert a new node there
    if(new_data < data){ //Left
        if(left == nullptr){   //If it has no left child
            Node* newLeftNode = new Node(new_data, nullptr, nullptr);  //Create a new Node
            left = newLeftNode;  //Set left to this new node
            cout << data << " +child(L) " << new_data << endl;
        }else{  //if there is a child
            left->insert(new_data); //ask to insert the child into this node
        }
    }else{ //Right
        if(right == nullptr){   //If it has no right child
            Node* newRightNode = new Node(new_data, nullptr, nullptr);  //Create a new Node
            right = newRightNode;  //Set right to this new node
            cout << data << " +child(R) " << new_data << endl;
        }else{  //if there is a child
            right->insert(new_data); //ask to insert the child into this node
        }
    }
}

//Helper function, will be called on singular Nodes
bool Node::isLeaf() {
    //If the node has NO children, it is a leaf
    if(left == nullptr && right == nullptr){
        return true;
    }else{
        return false;
    }
}

//Only called on the root
int Node::height() {
    //Must be recursive
    if(isLeaf()){ //BaseCase will end this line of searching
        return 0;
    }
    int a = 0;
    int b = 0;
    int result = 0;
    if(left != NULL){
        a = left->height();
    }
    if(right != NULL){
        b = right->height();
    }
    if(a >= b){ // whichever path is greatest the function will follow
        result = a;
    }else{
        result = b;
    }
    return (result + 1); //increasing the count by 1 based on the path chosen
}

//This will be called on a root node
bool Node::isFull(){
    //Must be recursive
    //We step through the whole tree and check if each child has two children
    //If any Node has a single child: return false
    bool isBalanced = true;
    cout << data << " (" << (left != nullptr) << "," << (right != nullptr) << ")" << endl;
    if((left == nullptr) != (right == nullptr)){
        cout << "isNotFull" << endl;
        isBalanced = false;
    }
    if((left != nullptr) && (right != nullptr)){
        cout << "Both left and right exist" << endl;
        isBalanced = left->isFull();
        isBalanced = right->isFull();
    }else if((left == nullptr) && (right == nullptr)){
        cout << "found leaf" << endl;
    }
    return isBalanced;
}
    

//This will be called on the root
int Node::countNodes() {
    int count = 1; //Starts at 1 because if the function is executed on the node then it exists
    if(left != nullptr){
        count += left->countNodes();
    }
    if(right != nullptr){
        count += right->countNodes();
    }
    return count;
}
