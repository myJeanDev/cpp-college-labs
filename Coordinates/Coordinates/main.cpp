#include <fstream>
#include <iostream>
#include <time.h>
#include "CoordinateList.h"

/*
-Created a new object called 'list' built from the blueprint of the class in CoordinateList.h
-in the constructor we can take in an argument of the type int this case its 10
-Now there is an array called "list" filled with 10 coordinates all with random x and y'st

-Then the list if printed

-list which is of the class CoordinateList has the function orderListFromCenter invoked
-However the orderListFromCenter is not defined yet

-Console out a "sorted"
-Then invoke the function print() from list of class type coordinateList
*/


int main (){
  //Using a pointer to access the CoordinateList, assign it as 'list' with a size of 10
  CoordinateList *list = new CoordinateList(10);
  std::cout << "Unsorted" << std::endl;
  list->print();

  //This is the everything function
  list->orderListFromCenter();
  //*pointer access means we use '->' instead of '.'

  //Prints out a sorted List, this currently does not work
  std::cout << "Sorted" << std::endl;
  list->print();
}
