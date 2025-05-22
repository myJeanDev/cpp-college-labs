#include "game_of_life.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include "state.h"
// DO NOT add any more public methods, private ones are fine

// Copy Constructor, Copy Assignment Operator, and the Destructor: Maybe the copy needs to be changed to transfer history

using namespace std;
//⁤⁤⁢⁢ Starter File
//⁤⁤⁢⁢ NETID: willschm

//⁤⁤⁢⁢ String Constructor
GameOfLife::GameOfLife(string filename) : GameOfLife(filename, 0) {}

//⁤⁤⁢⁢ String Int Constructor
GameOfLife::GameOfLife(std::string filename, int pregens): GameOfLife(filename, '*', '-', pregens) {}

//⁤⁤⁢⁢ String Char Char Constructor
GameOfLife::GameOfLife(std::string filename, char live_cell, char dead_cell): GameOfLife(filename, live_cell, dead_cell, 0) {}

//⁤⁤⁢⁢ Complete Constructor
GameOfLife::GameOfLife(std::string filename, char live_cell, char dead_cell, int pregens){
  if (live_cell == dead_cell) {
    throw(runtime_error("Live cell cannot be same as dead cells"));
  } else {
    this->SetLiveCell(live_cell);
    this->SetDeadCell(dead_cell);
  }
    
  fstream file_in(filename);
  //⁤⁤⁢⁢File Reading Init
  if (!file_in) {
    throw(runtime_error("file does not exist"));
  }
  if (!(file_in >> this->width_ >> this->height_)) {
    throw(runtime_error("file's width or height are wrong"));
  }

  //⁤⁤⁢⁢String PreInit
  this->current_ = string(this->width_ * this->height_, '-');
  string line;
  getline(file_in, line);
  //⁤⁤⁢⁢Filling String
  for (int row = 0; row < this->height_; ++row) {
    getline(file_in, line);
    for (int col = 0; col < this->width_; ++col) {
      if (line[col] == '*') {
        this->current_[col + (row * this->width_)] = '*';
      }
    }
  }
  //⁤⁤⁢⁢Execute Pregens
  if (pregens > 0) this->NextNGen(pregens);
}


// Getters
int GameOfLife::GetGenerations() {
    return this->generations_;
}


// Setters
void GameOfLife::SetLiveCell(char new_live_cell) {
  if (new_live_cell == this->dead_cell_) {
    throw(runtime_error("cannot set the live cell to be the same as dead cell"));
  }
  this->live_cell_ = new_live_cell;
}
void GameOfLife::SetDeadCell(char new_dead_cell) {
  if (new_dead_cell == this->live_cell_) {
    throw(runtime_error("cannot set the dead cell to be the same as live cell"));
  }
  this->dead_cell_ = new_dead_cell;
}



// Manipulators
void GameOfLife::NextGen() {
  // Store the current state in a history object
  StoreStateInHistory();
  ++this->generations_;
  string next = this->current_;
  //⁤⁤⁢⁢Copy Current String
  for (int row = 0; row < this->height_; ++row) {
    for (int col = 0; col < this->width_; ++col) {
	  //⁤⁤⁢⁢Compute Current Cell Status
      short neighbor_count = 0;
      int tr, br, lc, rc;
      tr = ((row - 1) + this->height_) % this->height_;
      br = ((row + 1) + this->height_) % this->height_;
      lc = ((col - 1) + this->width_) % this->width_;
      rc = ((col + 1) + this->width_) % this->width_;
      int neighbors[8] = {tr * this->width_ + lc,  tr * this->width_ + col, tr * this->width_ + rc,  row * this->width_ + lc, row * this->width_ + rc, br * this->width_ + lc, br * this->width_ + col, br * this->width_ + rc};
      for (size_t j = 0; j < 8; j++) {
        if (this->current_[neighbors[j]] == '*') ++neighbor_count;
      }
	  //⁤⁤⁢⁢Apply Game Rules
      int curr = col + (row * this->width_);
      if (this->current_[curr] == '*') {
        if (neighbor_count == 2 || neighbor_count == 3)
          next[curr] = '*';
        else
          next[curr] = '-';
      } else {
        if (neighbor_count == 3)
          next[curr] = '*';
        else
          next[curr] = '-';
      }
    }
  }
  //⁤⁤⁢⁢Update game string
  this->current_ = next;
}

void GameOfLife::NextNGen(int n) {
  while (n-- > 0) {
    this->NextGen();
  }
}



// Operator Overloaders

GameOfLife& GameOfLife::operator++() {
  this->NextGen();
  return *this;
}

GameOfLife GameOfLife::operator++(int) {
  auto old = *this;
  ++*this;
  return old;
}


//⁤⁤⁢⁢Helper Method for comparisons
double GameOfLife::PercentLiving() const {
  double count = 0;
  for (size_t i = 0; i < current_.length(); ++i)
    if (current_[i] == '*') ++count;
  return (count / current_.length());
}
bool GameOfLife::operator<(const GameOfLife& rhs) const {
  return this->PercentLiving() < rhs.PercentLiving();
}
bool GameOfLife::operator<=(const GameOfLife& rhs) const {
  return (*this < rhs) || (*this == rhs);
}
bool GameOfLife::operator>(const GameOfLife& rhs) const {
  return (rhs < *this);
}
bool GameOfLife::operator>=(const GameOfLife& rhs) const {
  return (rhs < *this) || (rhs == *this);
}
bool GameOfLife::operator==(const GameOfLife& rhs) const {
  return abs(PercentLiving() - rhs.PercentLiving()) <= 0.005;
}

ostream& operator<<(ostream& os, const GameOfLife& game) {
  string out = "Generation: ";
  out += to_string(game.generations_);
  out += '\n';
  for (int row = 0; row < game.height_; ++row) {
    for (int col = 0; col < game.width_; ++col) {
      out += (game.current_[col + (row * game.width_)] == '*' ? game.live_cell_ : game.dead_cell_);
    }
    out += '\n';
  }
  return os << out;
}


// TESTING METHODS
int GameOfLife::GetHeight(){
    return height_;
}
int GameOfLife::GetWidth(){
    return width_;
}
char GameOfLife::GetLiveCell(){
    return live_cell_;
}
char GameOfLife::GetDeadCell(){
    return dead_cell_;
}
char GameOfLife::GetSpecificCell(int row, int col){
    return current_[(width_ * row) + col];
}
char GameOfLife::GetSpecificCellString(int index){
    return current_[index];
}
std::string GameOfLife::GetHistoryAtIndex(int index){
    return history_[index].game_board;
}
std::string GameOfLife::GetCurrent(){
    return current_;
}






// All My Code:





// Copy Constructor
GameOfLife& GameOfLife::operator=(const GameOfLife & other){
    if (this != &other) {
        std::cout << "Making a copy" << std::endl;
        current_ = other.current_;
        height_ = other.height_;
        width_ = other.width_;
        live_cell_ = other.live_cell_;
        dead_cell_ = other.dead_cell_;
        generations_ = other.generations_;
        available_gens_ = other.available_gens_;
        for(int i=0; i < 100; i++){
            State newState(other.history_[i].game_board, other.history_[i].live, other.history_[i].dead);
            history_[i] = newState;
        }
    }
    // Return a reference to the modified object
    return *this;
}

// constructor
GameOfLife::GameOfLife(GameOfLife && other){
    if (this != &other) {
        current_ = other.current_;
        height_ = other.height_;
        width_ = other.width_;
        live_cell_ = other.live_cell_;
        dead_cell_ = other.dead_cell_;
        generations_ = other.generations_;
        available_gens_ = other.available_gens_;
        for(int i=0; i < 100; i++){
            State newState(other.history_[i].game_board, other.history_[i].live, other.history_[i].dead);
            history_[i] = newState;
        }
    }
}


//Copy Assignment Operator
GameOfLife& GameOfLife::operator=(GameOfLife && other) {
    if (this != &other) {
        current_ = other.current_;
        height_ = other.height_;
        width_ = other.width_;
        live_cell_ = other.live_cell_;
        dead_cell_ = other.dead_cell_;
        generations_ = other.generations_;
        available_gens_ = other.available_gens_;
        for(int i=0; i < 100; i++){
            State newState(other.history_[i].game_board, other.history_[i].live, other.history_[i].dead);
            history_[i] = newState;
        }
    }
    // Return a reference to the modified object
    return *this;
}





GameOfLife::GameOfLife(std::string state, char live_cell, char dead_cell, int width, int height){
    width_ = width;
    height_ = height;
    current_ = state;
    live_cell_ = live_cell;
    dead_cell_ = dead_cell;
}

void GameOfLife::StoreStateInHistory(){
    // Create a new struct for state
    State newState(current_, live_cell_, dead_cell_);

    // If available_gens_ reaches the maximum capacity
    if (available_gens_ >= 100) {
        // Shift all elements to the left by one position
        for (int i = 0; i < 99; ++i) {
            history_[i] = history_[i + 1];
        }
        // Insert the new state at the end
        history_[99] = newState;
    } else {
        // If there's still space, insert the new state at the end
        history_[available_gens_] = newState;
        available_gens_++;
    }
}

int GameOfLife::GetAvailableGens(){
    return available_gens_;
}

void GameOfLife::ToggleCell(int index){
    // Throws a range error if index is out of bounds. This method sets a live_cell at the index to a dead_cell and vice versa.
    if(index < 0 || index > current_.length()){
        throw std::out_of_range ("index is out of range");
    }else{
        if(current_.at(index) == live_cell_){
            current_.at(index) = dead_cell_;
        } else if(current_.at(index) == dead_cell_){
            current_.at(index) = live_cell_;
        }
    }
}

void GameOfLife::ToggleCell(int row, int col){
    // arr[row][col] would be: (row * width_) + col
    if((row * width_) + col > current_.size()){
        throw std::out_of_range ("index is out of range");
    }else{
        if(current_.at((row * width_) + col) == live_cell_){
            current_.at((row * width_) + col) = dead_cell_;
        } else if (current_.at((row * width_) + col) == dead_cell_){
            current_.at((row * width_) + col) = live_cell_;
        }
    }
    // Same as ToggleCell(index). It throws a range error if either row or column are out of bounds.
}

bool GameOfLife::IsStillLife(){
    // loop through the currentState and the future state, and if all are the same return true, else return false
    // This method checks to see if the current generation of the game is a Still Life.
    // Meaning that no cells change between the current generation and the next generation.
    // Note that this should NOT advanced the current generations of the game
    // only check to see if the next step of the game is the same
    // note that this is a CELL wise comparison not a comparison of live or dead.
    GameOfLife future(*this);
    future.NextGen();
    for(size_t i=0; i < current_.size(); ++i){
        if (future.current_[i] != current_[i]){
            return false;
        }
    }
    return true;
}

// arr[2][5] would be: arr[(2*width)+5]
// arr[row][col] would be: (row * width_) + col

std::string GameOfLife::GenWindow(int row, int col, int height, int width){
    if(height > height_ || width > width_){
        throw std::domain_error("Height or width for generated window is too big");
    }
    if( (row * width_) + col > current_.size()){
        throw std::domain_error("Row or column for generated window is too big");
    }
    std::string window;

        // Iterate through rows and columns to construct the window
        for (int i = row; i < row + height; ++i) {
            for (int j = col; j < col + width; ++j) {
                // Ensure wrapping around for the table (circular array)
                int wrapped_row = i % height_;
                int wrapped_col = j % width_;

                // Append the cell value to the window string
                window += current_[wrapped_row * width_ + wrapped_col];
            }
        }
        return window;
}

GameOfLife GameOfLife::GenSubGame(int row, int col, int height, int width){
    // Create a new game from a GameOfLife window.
    // This method will return a new game of life with the same rules and logic as the GenWindow method.
    // HINT: you may want to make a PRIVATE constructor for creating your subgames.
    // They should be a BRAND NEW game and have no floating data from the original game it is a window of.
    // This method throws the same errors as GenWindow.
    std::string newBoard = GenWindow(row, col, height, width);
    GameOfLife newGame(newBoard, height, width);
    return newGame;
}



GameOfLife& GameOfLife::operator+=(int gens) {
  // Acts the same as ASN2 but, if the gens is negative then this acts equivalent to calling the "-=" operator instead.
  // Returns a reference to the object after incrementing
    
  if (gens > 0) {
    this->NextNGen(gens);
    return *this;
  } else{
      return *this -= gens;
  }
}

GameOfLife& GameOfLife::operator-=(int gens){
    // Decrement Equals. Decrements the game by that many generations.
    // This method throws a domain error if there are no generations available to roll back to
    if(available_gens_ == 0 || gens > available_gens_){
        throw std::out_of_range ("cannot roll back any further");
    }else{
        current_ = history_[available_gens_ - gens].game_board;
        available_gens_ = available_gens_ - gens;
        generations_ = generations_- gens;
    }
    // (Aka a freshly generated game or a game that has been rolled back to its limits).
    // This method will instead throw a range error if the number of generations passed is greater than the number of available generations
    // to rollback to, assuming there is a number of generations to rollback to that is greater than 0. Otherwise, roll back the current game to the game state "gens" generations back.
    // After rolling back return a reference to the current game.
    return *this;
}

GameOfLife GameOfLife::operator+(int gens) const {
  auto cp(*this);
  if (gens > 0)
    return cp += gens;
  else
    return cp;
}

GameOfLife GameOfLife::operator-(int gens){
    // Simple Decrement operator.
    // Decrements the game by that many generations.
    // This method throws errors identically to the "-=" method.
    // Otherwise, return a new game that is the equivalent of rolling back the current game "gens" generations.
    GameOfLife newGame(history_[available_gens_-gens].game_board, height_, width_);
    return newGame;
}

GameOfLife& GameOfLife::operator--(){
    // Acts like decrementing the current game by 1 and returns the current game state AFTER the decrement
    // get the history and move back by 1
    return *this -= 1;
}

GameOfLife GameOfLife::operator--(int){
    //⁤⁤⁢⁢ Like 'operator--' but instead returns the a copy of the game state BEFORE to the decrementation
    // get the history and move back by int amount
    GameOfLife past(*this);
    *this -= 1;
    return past;
}

GameOfLife GameOfLife::operator-(){
    // Returns a COPY of the game where all cells have swapped live/dead states
    GameOfLife newGame(*this);
    for(int i=0; i < newGame.current_.length(); ++i){
        newGame.ToggleCell(i);
    }
    return newGame;
}
