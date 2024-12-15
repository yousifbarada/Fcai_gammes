//
// Created by tvyos on 12/15/2024.
//

#ifndef ASSIGNMENT_DEMO_MISERE_H
#define ASSIGNMENT_DEMO_MISERE_H
#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <cstdlib> // for rand()
#include <ctime>   // for time()
bool l_s=false;
using namespace std;
template <typename T>
class r_X_O_Board : public Board<T> {
public:
  r_X_O_Board();
  ~r_X_O_Board(); // Destructor to deallocate memory
  bool update_board(int x, int y, T symbol);
  void display_board();
  bool is_win();
  bool is_draw();
  bool game_is_over();
  bool check_round();

private:
  void print_winner(); // Helper function to print the winner
};

template <typename T>
class r_X_O_Player : public Player<T> {
public:
  r_X_O_Player(string name, T symbol);
  void getmove(int& x, int& y);
};

template <typename T>
class r_o_random : public RandomPlayer<T> {
public:
  r_o_random(T symbol);
  void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION

// Constructor for X_O_Board
template <typename T>
r_X_O_Board<T>::r_X_O_Board() {
  this->rows = this->columns = 3;
  this->board = new char*[this->rows];
  for (int i = 0; i < this->rows; i++) {
    this->board[i] = new char[this->columns];
    for (int j = 0; j < this->columns; j++) {
      this->board[i][j] = ' '; // Initialize with a space for better display
    }
  }
  this->n_moves = 0;
}

// Destructor for X_O_Board
template <typename T>
r_X_O_Board<T>::~r_X_O_Board() {
  for (int i = 0; i < this->rows; i++) {
    delete[] this->board[i];
  }
  delete[] this->board;
}

template <typename T>
bool r_X_O_Board<T>::update_board(int x, int y, T mark) {
  if (l_s){return true;}
  if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && (this->board[x][y] == ' ' || mark == 0)) {
    if (mark == 0) {
      this->n_moves--;
      this->board[x][y] = ' ';
    } else {
      this->n_moves++;
      this->board[x][y] = toupper(mark);
    }
    return true;
  }
  return false;
}

template <typename T>
void r_X_O_Board<T>::display_board() {
  if (!l_s) {
    for (int i = 0; i < this->rows; i++) {
      cout << "\n| ";
      for (int j = 0; j < this->columns; j++) {
        cout << "(" << i << "," << j << ")";
        cout << setw(2) << this->board[i][j] << " |";
      }
      cout << "\n-----------------------------";
    }
    cout << endl;
  }
}

template <typename T>
bool r_X_O_Board<T>::check_round() {
  for (int i = 0; i < this->rows; i++) {
    if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != ' ') ||
        (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != ' ')) {
      return true;
    }
  }
  if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != ' ') ||
      (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != ' ')) {
    return true;
  }
  return false;
}

template <typename T>
bool r_X_O_Board<T>::is_win() {
  if(l_s){
    return true;
  }
  if (check_round()) {
    l_s= true;
    return false;
  }
  return false;
}

template <typename T>
bool r_X_O_Board<T>::is_draw() {
  return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool r_X_O_Board<T>::game_is_over() {

  return is_win() || is_draw();
}


// Constructor for r_X_O_Player
template <typename T>
r_X_O_Player<T>::r_X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void r_X_O_Player<T>::getmove(int& x, int& y) {
  if (!l_s) {
    cout << this->getname() << "it`s your turn!!\n";
    cout << "\nPlease enter a Row to play (0 4): ";
    cin >> x;
    while (cin.fail()) {
      cout << "enter a valid input\n";
      cin >> x;
    }
    cin >> y;
    while (cin.fail()) {
      cout << "enter a valid input\n";
      cin >> y;
    }
  }
}

// Constructor for super_X_O_Random_Player
template <typename T>
r_o_random<T>::r_o_random(T symbol) : RandomPlayer<T>(symbol) {
  this->dimension = 3;
  this->name = "Random Computer Player";
  static bool seeded = false;
  if (!seeded) {
    srand(static_cast<unsigned int>(time(0)));
    seeded = true;
  }
}

template <typename T>
void r_o_random<T>::getmove(int& x, int& y) {

  x = rand() % this->dimension;
  y = rand() % this->dimension;
}

#endif // ASSIGNMENT_DEMO_MISERE_H
