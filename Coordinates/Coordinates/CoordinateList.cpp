#include <iostream>
#include "CoordinateList.h"

/*
Defined functions for class 'CoordinateList' from 'CoordinateList.h' file
*/

//Constructor function
CoordinateList::CoordinateList(unsigned int size) {
    //iterates based on inputed size, in this case it will be 10
   for (unsigned int i=0; i<size; i++) {
       //Generates random coordinates & adds them to 'allPoints' array
       allPoints.push_back(new Coordinate((rand() % 100), (rand() % 100)));
    }
    //we don't know the center yet
    center = nullptr;
}

//Print Function
void CoordinateList::print() {
   for (auto i:allPoints) {
       //Invokes the print function found within Coordinate object's class
      i->print();
      //for formatting
      std::cout<<std::endl;
   }
}
//Print Function
void CoordinateList::print(std::ofstream& out_stream) {
   for (auto i:allPoints) {
       //Invokes the print function found within Coordinate object's class
      i->print();
      out_stream<<std::endl;
   }
}


//center = new Coordinate(average of all x's, average of all y's)
void CoordinateList::createCenterPoint(){
   int averageX = 0;
   int averageY = 0;
   int arraySize = 0;
    for (auto i:allPoints) {
        arraySize++;
        averageX += i->getX();
        averageY += i->getY();
   }
   averageX = averageX/arraySize;
   averageY = averageY/arraySize;
   center = new Coordinate(averageX,averageY);
}

//Returns the distance from center given an index
unsigned int CoordinateList::getDistanceFromCenter(unsigned int index) {
   if (center == nullptr) {
      std::cout<<"ERROR getDistanceFromCenter called when center is still nullptr"<<std::endl;
      return -1;
   }
   return allPoints[index]->getDistance(center);
}

//given start, find the index of the next closest coordinate point to center remaining in the list
//searching from start to the end of the vector
unsigned int CoordinateList::findNextClosest(unsigned int start) {
    int min = start;
    for (long unsigned int i=start;i < allPoints.size();i++) {
        //comparing min with rest of indexed items
        if(getDistanceFromCenter(i) < getDistanceFromCenter(min)){
            min = i;
        }
   }
   std::cout << "DISTANCE: "<< allPoints[min]->getX() << "," << allPoints[min]->getY() << " " << getDistanceFromCenter(min) << std::endl;
   return min;
}

//Simple getter, returns the 'center' coordinate
Coordinate* CoordinateList::getCenter() {
   return center;
}

/*
-GOAL: Use selection sort to sort the list
-STEP1: Initialize the center variable
-STEP2: Put the closest Coordinate to the center in location 0 in the vector
-STEP3: continue to put the points in order one by one by finding the next closest and swapping with whatever is next
*/

//This is our everything function
void CoordinateList::orderListFromCenter() {
    //Initilize Center Point
    createCenterPoint();
    
    for(long unsigned int i=0; i < allPoints.size(); i++){
        //swapping, closest point with current index
        iter_swap(allPoints.begin() + i, allPoints.begin() + findNextClosest(i));
    }
    std::cout << "CENTER: " << center->getX() << "," << center->getY() << std::endl;
    
    for(int j = 0; j < 10; j++){
        std::cout << "(" << allPoints[j]->getX() << "," << allPoints[j]->getY() << ")" << " Distance:" << getDistanceFromCenter(j) << std::endl;
    }
}
