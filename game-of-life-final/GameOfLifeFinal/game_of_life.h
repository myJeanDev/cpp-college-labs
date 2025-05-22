#ifndef GAME_OF_LIFE_H_DEFINED
#define GAME_OF_LIFE_H_DEFINED
#include <iostream>
#include <string>
#include "state.h"
#include <vector>

class GameOfLife {
  //⁤⁤⁢⁢ Necessary Data Member Variables
  int height_, width_;
  int generations_ = 0;
  char live_cell_ = '*';
  char dead_cell_ = '-';
  std::string current_;
  //⁤⁤⁢⁢ Private Helper Method for Comparison Operators
  double PercentLiving() const;
    
  // history implimentation
  int available_gens_ = 0;
  State history_[100];
  void StoreStateInHistory();
  GameOfLife(std::string, char, char, int, int);

 public:
    
  // TEST METHODS (REMOVE THESE BEFORE SUBMISSION)
  int GetHeight();
  int GetWidth();
  char GetLiveCell();
  char GetDeadCell();
  char GetSpecificCell(int, int);
  char GetSpecificCellString(int);
  std::string GetCurrent();
  std::string GetHistoryAtIndex(int);
    
  //⁤⁤⁢⁢ No Default Contructor
  GameOfLife() = delete;
    
  //⁤⁤⁢⁢ Defaulting Big 5
  GameOfLife(const GameOfLife &) = default;                 // Construct a Game
  GameOfLife &operator=(const GameOfLife &);                // Copy another Game
  GameOfLife(GameOfLife &&);                                // 
  GameOfLife &operator=(GameOfLife &&);                     // Moves data from one Game to another
  ~GameOfLife() = default;                                  // Deconstructs the Game
    
  //⁤⁤⁢⁢ Constructor Declarations
  GameOfLife(std::string);
  GameOfLife(std::string, int);
  GameOfLife(std::string, char, char);
  GameOfLife(std::string, char, char, int);
    
  //⁤⁤⁢⁢ Setters
  void SetLiveCell(char);
  void SetDeadCell(char);
    
  //⁤⁤⁢⁢ Getters
  int GetGenerations();
  int GetAvailableGens();
    
  //⁤⁤⁢⁢ Integral Next Gen
  void NextGen();
  void NextNGen(int);

  // Methods
  std::string GenWindow(int row, int col, int height, int width);
  GameOfLife GenSubGame(int row, int col, int height, int width);
  void ToggleCell(int index);
  void ToggleCell(int row, int col);
  bool IsStillLife();
    
  // Operator overrides
  GameOfLife operator+(int) const;              //⁤⁤⁢⁢ If passed a negative number then it acts like the '-' operator
  GameOfLife operator-();                       // Returns a COPY of the game where all cells have swapped live/dead states
  GameOfLife operator-(int gens);
  GameOfLife &operator++();                     //⁤⁤⁢⁢ Pre-increment
  GameOfLife operator++(int);                   //⁤⁤⁢⁢ Post-increment
  GameOfLife& operator--();                     // Acts like decrementing the current game by 1 and returns the current game state AFTER the decrement
  GameOfLife operator--(int);                   //⁤⁤⁢⁢ Like 'operator--' but instead returns the a copy of the game state BEFORE to the decrementation
  GameOfLife &operator+=(int);                  //⁤⁤⁢⁢ If the gens is negative this acts equivalent to calling the "-=" operator instead. Returns a reference to the object after incrementing
  GameOfLife& operator-=(int gens);
  
  // Uses PercentLiving() for comparisons
  bool operator<(const GameOfLife &) const;     //⁤⁤⁢⁢ Less Than Operator
  bool operator<=(const GameOfLife &) const;    //⁤⁤⁢⁢ Less Than EQ Operator
  bool operator>(const GameOfLife &) const;     //⁤⁤⁢⁢ Greater Than Operator
  bool operator>=(const GameOfLife &) const;    //⁤⁤⁢⁢ Greater Than EQ Operator
  bool operator==(const GameOfLife &) const;    //⁤⁤⁢⁢ Equality Operator
    
  //⁤⁤⁢⁢ Friend command for Ostream operator
  friend std::ostream &operator<<(std::ostream &, const GameOfLife &);
};
//⁤⁤⁢⁢ Output Stream operator
std::ostream &operator<<(std::ostream &, const GameOfLife &);
#endif
