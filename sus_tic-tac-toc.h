//
// Created by tvyos on 12/5/2024.
//

#ifndef _3X3X_O_H
#define _3X3X_O_H
#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

using namespace std;
int total_wins=0;
template <typename T>
class SUS : public Board<T> {
private:
  vector<vector<T>> board;
  string words = "SUS";

public:
  SUS();
  bool update_board(int x, int y, T symbol);
  void display_board();
  bool is_win();
  int player1=0,player2=0;
  bool check_round();
  int round_win();
  bool is_draw();
  bool game_is_over();
};

template <typename T>
class SUS_Player : public Player<T> {
public:
  SUS_Player(string name, T symbol);
  void getmove(int& x, int& y);
};

template <typename T>
class SUS_Random_Player : public RandomPlayer<T> {
public:
  SUS_Random_Player(T symbol);
  void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION

template <typename T>
SUS<T>::SUS() {
  this->rows = this->columns = 3;
  this->board = vector<vector<T>>(this->rows, vector<T>(this->columns, '-'));
  this->n_moves = 0;
}

template <typename T>
bool SUS<T>::update_board(int x, int y, T symbol) {
  if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && this->board[x][y] == '-') {
    this->n_moves++;
    this->board[x][y] = toupper(symbol);  // Ensure characters are upper case
    return true;
  }
  return false;
}

template <typename T>
void SUS<T>::display_board() {
  for (int i = 0; i < this->rows; i++) {
    cout << "| ";
    for (int j = 0; j < this->columns; j++) {
      cout << this->board[i][j] << " | ";
    }
    cout << "\n-------------------------\n";
  }
  cout<<"______________________________________________________________________________________________\n";
}

template <typename T>
int SUS<T>::round_win() {
  string check;
  int n=0;
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j <= this->columns - 3; j++) {
      check = string(1, board[i][j]) + board[i][j + 1] + board[i][j + 2];
      if (check == words) n++;
    }
  }
  for (int i = 0; i <= this->rows - 3; i++) {
    for (int j = 0; j < this->columns; j++) {
      check = string(1, board[i][j]) + board[i + 1][j] + board[i + 2][j];
      if (check == words) n++;
    }
  }
  for (int i = 0; i <= this->rows - 3; i++) {
    for (int j = 0; j <= this->columns - 3; j++) {
      check = string(1, board[i][j]) + board[i + 1][j + 1] + board[i + 2][j + 2];
      if (check == words) n++;
    }
  }
  for (int i = 0; i <= this->rows - 3; i++) {
    for (int j = 2; j < this->columns; j++) {
      check = string(1, board[i][j]) + board[i + 1][j - 1] + board[i + 2][j - 2];
      if (check == words) n++;
    }
  }

  return n;
}

template <typename T>
bool SUS<T>::check_round() {
  int m=round_win();
  int z=abs(m-total_wins);
  total_wins=m;
  if (z) {
    if (this->n_moves % 2 == 0) {
      player1+=z;
    } else {
      player2+=z;
    }
    return true;
  }


  return false;
}

// Checks if there is a winner
template <typename T>
bool SUS<T>::is_win() {
  check_round();

  if (this->n_moves == 9) {
    return player1 != player2;
  }
  cout<<"player 1 score is: "<<this->player1<<endl;
  cout<<"player 2 score is: "<<this->player2<<endl;

  return false;
}

// Checks if the game is a draw
template <typename T>
bool SUS<T>::is_draw() {
  return (this->n_moves == 9 && !is_win());
}

// Checks if the game is over
template <typename T>
bool SUS<T>::game_is_over() {
  return is_win()||is_draw();
}


template <typename T>
SUS_Player<T>::SUS_Player(string name, T symbol) : Player<T>(name, symbol) {
}

template <typename T>
void SUS_Player<T>::getmove(int& x, int& y){
  cout<<this->getname()<<"it`s your turn!!\n";
  cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
  cin >> x;
  while (cin.fail()){
    cout<<"enter a valid input\n";
    cin>>x;
  }
  cin>>y;
  while (cin.fail()){
    cout<<"enter a valid input\n";
    cin>>y;
  }

}

template <typename T>
SUS_Random_Player<T>::SUS_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
  this->name = "Random Computer Player";
  srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void SUS_Random_Player<T>::getmove(int& x, int& y) {
  cout<<"it`s computer turn\n";
  x = rand() % 3;  // Random number between 0 and 2
  y = rand() % 3;

}


#endif

