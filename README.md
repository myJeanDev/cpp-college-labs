# C++ Lab work
This repository contains important labs for 3 different classes that taught C++. It does not include all assignments or smaller code projects from the classes, but most of the concepts are encapsulated within these projects.

## ✨🧬[game-of-life-final](./game-of-life-final/)  
Conway's Game of Life with screen wrap written for my Advanced C++ class at Colorado State University.  
- Generation history tracking (maximum of 100 states of rollback)
- Grid wrapping _(all cells on the edges are neighbors to cells on the other side)_
- Load 'life patterns' from files
- Advance or revert generations
- Operator overloads for intuitive generation progression
- Stable state checking _(knowing if a cell pattern will repeat forever)_
- Extract sub-grids into new 'games of life' _(take a section of the current game and copy that to a new game)_

## ✨🌳[avl-tree-redo](./avl-tree-redo/)  
My later attempt at creating a self-balancing AVL Tree on insertion:  
- Rotations (left/right)  
- Height updates  
- Balance checks  
- Node counting  
- Leaf detection  
- Tree validation  

Maintains `O(log n)` height for efficient operations.  

## 🧬[game-of-life](./game-of-life/)  
My first attempt at creating the 'game of life', had a few bugs and did not give exactly expected results.
- Grid wrapping _(all cells on the edges are neighbors to cells on the other side)_
- Load 'life patterns' from files
- Operator overloads for intuitive generation progression

## 🌳[binary-search-tree](./binary-search-tree/)  
An implementation of a binary search tree with:
- node insertion
- height calculation
- node counting
- full-tree verification
- leaf-checking
The Node class handles recursive insertion and checks if the tree is full.

## 🌳[avl-trees](./avl-trees/)  
First attempt at creating an AVL tree.

## 📍[coordinates](./coordinates/)  
My first project using C++, I remember this project being so hard at the time. Looking back on it now this code looks so small.
The code generates a list of random 2D coordinates, computes their average center point, and sorts the coordinates by their distance from this center using a selection sort algorithm.
