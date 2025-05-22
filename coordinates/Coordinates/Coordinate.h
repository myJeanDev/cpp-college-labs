//READ ONLY
//.h indicates that this is a header file
#include <fstream>

class Coordinate {
    private:
        unsigned int x;
        unsigned int y;
    public:
        //constructor function, takes in 2 non negative numbers
       Coordinate(unsigned int x, unsigned int y);
       unsigned int getX();
       unsigned int getY();
       void print();
       void print(std::ofstream& out_stream);
      unsigned int getDistance(Coordinate* second);
};
