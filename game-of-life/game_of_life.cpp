#include "game_of_life.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;
//⁤⁤⁢⁢ Starter File
//⁤⁤⁢⁢ NETID: 

//⁤⁤⁢⁢ String Constructor
GameOfLife::GameOfLife(string filename) : GameOfLife(filename, 0) {}
//⁤⁤⁢⁢ String Int Constructor
GameOfLife::GameOfLife(std::string filename, int pregens)
    : GameOfLife(filename, '*', '-', pregens) {}
//⁤⁤⁢⁢ String Char Char Constructor
GameOfLife::GameOfLife(std::string filename, char live_cell, char dead_cell)
    : GameOfLife(filename, live_cell, dead_cell, 0) {}
//⁤⁤⁢⁢ Complete Constructor
GameOfLife::GameOfLife(std::string filename, char live_cell, char dead_cell,
                       int pregens) {
  if (live_cell == dead_cell) {
    throw(runtime_error("ERROR FINISH ERROR MESSAGE"));
  } else {
    this->SetLiveCell(live_cell);
    this->SetDeadCell(dead_cell);
  }
  fstream file_in(filename);
  //⁤⁤⁢⁢File Reading Init
  if (!file_in) {
    throw(runtime_error("ERROR FINISH ERROR MESSAGE"));
  }
  if (!(file_in >> this->width_ >> this->height_)) {
    throw(runtime_error("ERROR FINISH ERROR MESSAGE"));
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
void GameOfLife::SetLiveCell(char new_live_cell) {
  if (new_live_cell == this->dead_cell_) {
    throw(runtime_error("ERROR FINISH ERROR MESSAGE"));
  }
  this->live_cell_ = new_live_cell;
}
void GameOfLife::SetDeadCell(char new_dead_cell) {
  if (new_dead_cell == this->live_cell_) {
    throw(runtime_error("ERROR FINISH ERROR MESSAGE"));
  }
  this->dead_cell_ = new_dead_cell;
}
int GameOfLife::GetGenerations() { return this->generations_; }
void GameOfLife::NextGen() {
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
      int neighbors[8] = {tr * this->width_ + lc,  tr * this->width_ + col,
                          tr * this->width_ + rc,  row * this->width_ + lc,
                          row * this->width_ + rc, br * this->width_ + lc,
                          br * this->width_ + col, br * this->width_ + rc};
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
GameOfLife& GameOfLife::operator++() {
  this->NextGen();
  return *this;
}
GameOfLife GameOfLife::operator++(int) {
  auto old = *this;
  ++*this;
  return old;
}
GameOfLife GameOfLife::operator+(int gens) const {
  auto cp(*this);
  if (gens > 0)
    return cp += gens;
  else
    return cp;
}
GameOfLife& GameOfLife::operator+=(int gens) {
  if (gens > 0) {
    this->NextNGen(gens);
    return *this;
  } else
    return *this;
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
