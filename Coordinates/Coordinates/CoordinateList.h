//READ ONLY
//.h indicates that this is a header file
#include <fstream>
#include <vector>

#include "Coordinate.h"

class CoordinateList {
    private:
        //resizable array that stores the 'coordinate' type
        std::vector<Coordinate*> allPoints;
        
        //A pointer to a coordinate
        Coordinate* center;
        
        //takes in a non negative whole number as 'start'
        unsigned int findNextClosest(unsigned int start);
    public:
    //This is our constructor function, takes in a size, its called the same name as the class however it is a funciton
       CoordinateList(unsigned int size);
       void print();
       void print(std::ofstream& out_stream);
        void createCenterPoint();
       void orderListFromCenter();
       Coordinate* getCenter();
       unsigned int getDistanceFromCenter(unsigned int index);
};
