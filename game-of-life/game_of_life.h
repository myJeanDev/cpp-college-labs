#ifndef GAME_OF_LIFE_H_DEFINED
#define GAME_OF_LIFE_H_DEFINED
#include <iostream>
#include <string>
class GameOfLife {
  //⁤⁤⁢⁢ Necessary Data Member Variables
  int height_, width_;
  int generations_ = 0;
  char live_cell_ = '*', dead_cell_ = '-';
  std::string current_;
  //⁤⁤⁢⁢ Private Helper Method for Comparison Operators
  double PercentLiving() const;

 public:
  //⁤⁤⁢⁢ No Default Contructor
  GameOfLife() = delete;
  //⁤⁤⁢⁢ Defaulting Big 5
  GameOfLife(const GameOfLife &) = default;
  GameOfLife &operator=(const GameOfLife &) = default;
  GameOfLife(GameOfLife &&) = default;
  GameOfLife &operator=(GameOfLife &&) = default;
  ~GameOfLife() = default;
  //⁤⁤⁢⁢ Constructor Declarations
  GameOfLife(std::string);
  GameOfLife(std::string, int);
  GameOfLife(std::string, char, char);
  GameOfLife(std::string, char, char, int);
  //⁤⁤⁢⁢ Basic Getter
  int GetGenerations();
  //⁤⁤⁢⁢ Integral Next Gen
  void NextGen();
  void NextNGen(int);
  //⁤⁤⁢⁢ Setters for Live and Dead Cells.
  void SetLiveCell(char);
  void SetDeadCell(char);
  GameOfLife operator+(int) const;    //⁤⁤⁢⁢ Simple addition
  GameOfLife &operator+=(int);  //⁤⁤⁢⁢ Add and Assign Operator
  GameOfLife &operator++();     //⁤⁤⁢⁢ Pre-increment
  GameOfLife operator++(int);   //⁤⁤⁢⁢ Post-increment
  bool operator<(const GameOfLife &) const; //⁤⁤⁢⁢ Less Than Operator
  bool operator<=(const GameOfLife &) const; //⁤⁤⁢⁢ Less Than EQ Operator
  bool operator>(const GameOfLife &) const; //⁤⁤⁢⁢ Greater Than Operator
  bool operator>=(const GameOfLife &) const; //⁤⁤⁢⁢ Greater Than EQ Operator
  bool operator==(const GameOfLife &) const; //⁤⁤⁢⁢ Equality Operator
  //⁤⁤⁢⁢ Friend command for Ostream operator
  friend std::ostream &operator<<(std::ostream &, const GameOfLife &);
};
//⁤⁤⁢⁢ Output Stream operator
std::ostream &operator<<(std::ostream &, const GameOfLife &);
#endif