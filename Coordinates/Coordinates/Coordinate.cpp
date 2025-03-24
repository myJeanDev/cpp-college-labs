#include <cmath>
#include <iostream>
#include "Coordinate.h"

/*
Populating the unctions and variables declared by the Coordinate.h class
*/

//constructs an object of class 'coordinate'
Coordinate::Coordinate(unsigned int t_x, unsigned int t_y) {
    //t_ means its a parameter variable
   x = t_x;
   y = t_y;
}

//Prints out its X & Y variables
void Coordinate::print() {
   std::cout<<"("<<x<<","<<y<<")";
}

//& in declaration makes the ofstream variable a reference rather than a pointer
void Coordinate::print(std::ofstream& out_stream) {
   out_stream<<"("<<x<<","<<y<<")";
}

//returns x variable
unsigned int Coordinate::getX() {
   return x;
}
//returns y variable
unsigned int Coordinate::getY() {
   return y;
}

//returns a non negative whole number
//takes in a type Coordinate declared as secondPoint
unsigned int Coordinate::getDistance(Coordinate* secondPoint) {
    unsigned int x2 = secondPoint->getX();
    unsigned int y2 = secondPoint->getY();
    float xDifference = 0;
    float yDifference = 0;
    if(x2 > x){
        xDifference = x2-x;
    }else{
        xDifference = x-x2;
    }
    if(y2 > y){
        yDifference = y2-y;
    }else{
        yDifference = y-y2;
    }
    float approxDistance = pow(pow(xDifference, 2) + pow(yDifference, 2), 0.5);
    unsigned int distance = static_cast<int>(approxDistance);
    return distance;
}

