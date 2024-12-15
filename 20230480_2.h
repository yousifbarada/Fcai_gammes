//
// Created by tvyos on 12/4/2024.
//

#ifndef ASSIGNMENT_DEMO_X_O_CONNECT4_H
#define ASSIGNMENT_DEMO_X_O_CONNECT4_H

using namespace std;

#include "BoardGame_Classes.h"
template<typename T>
class connect_4_X_O_board:public  Board<T> {
public:
    connect_4_X_O_board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win() ;
    bool check_diagonal();
    bool  check_vertical();
    bool check_horizontal();
    bool is_draw() ;
    bool game_is_over() ;
    ~connect_4_X_O_board() { // Proper cleanup
        for (int i = 0; i < this->rows; i++) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }

};
template<typename T>
class connect_4_X_O_player:public Player<T>{
public:
    connect_4_X_O_player(string name,T sympol);
    void getmove(int&x ,int &y);

};
template <typename T>
class connect_4_X_O_Random_player : public RandomPlayer<T> {
public:
    void getmove(int& x,int &y) override;
    connect_4_X_O_Random_player(T symbol);
};
// ____________________________________________________________________________________________
#include<bits/stdc++.h>
template<typename T>
connect_4_X_O_board<T>:: connect_4_X_O_board(){
    this->columns = 7;this->rows =6;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = '-';

        }
    }
    this->n_moves = 0;

}
template <typename T>
bool connect_4_X_O_board<T>::update_board(int col,int y, T symbol) {
    // Ensure the coordinates are within bounds
    if (col < 0 || col >= this->columns ) {
        cout << "Invalid column. Try again.\n";
        return false;
    }


    for (int i = this->rows - 1; i >= 0; i--) {
        if (this->board[i][col] == '-') { // Find the lowest empty row
            this->board[i][col] = symbol;
            this->n_moves++;
            return true;
        }
    }
    // If the move is invalid, return false
    return false;
}

template<typename T>
void connect_4_X_O_board<T>::display_board() {

    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {

            cout << "(" << j << ")  ";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-------------------------------------------------------------------------------";
    }
    cout << endl;
}
template<typename T>
bool connect_4_X_O_board<T>::is_win() {
  if(check_horizontal()||check_vertical()||check_diagonal())
   {
   return true;
        }
    return false; // No winning condition met
}

template <typename T>
bool connect_4_X_O_board<T>::is_draw() {
    return (this->n_moves == 42 && !is_win());
}

template <typename T>
bool connect_4_X_O_board<T>::game_is_over() {
    return is_win() || is_draw();
}

//_______________________________________________________________________________________
template<typename T>
connect_4_X_O_player<T>::connect_4_X_O_player(string Nname,T s):Player<T>(Nname,s){}

template <typename T>
void connect_4_X_O_player<T>::getmove(int& x,int &y) {
  cout<<this->getname()<<"it`s your turn\n";
    y=0;
    cout << "\nPlease enter A Row (0, 6) separated by spaces: ";
    cin >> x;
    while (cin.fail()){
        cout<<"enter a valid input\n";
        cin>>x;
    }
}

// Constructor for super_X_O_Random_Player
template <typename T>
connect_4_X_O_Random_player<T>::connect_4_X_O_Random_player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 7;
    this->symbol=symbol;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void connect_4_X_O_Random_player<T>::getmove(int& x,int &y) {
    y=0;
    x = rand() % this->dimension;  // Random number between 0 and 7

}
template<typename T>
bool connect_4_X_O_board<T>::check_horizontal() {
    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col <= this->columns - 4; col++) {
            if (this->board[row][col] != '-' &&
                this->board[row][col] == this->board[row][col + 1] &&
                this->board[row][col] == this->board[row][col + 2] &&
                this->board[row][col] == this->board[row][col + 3]) {
                return true;
            }
        }
    }
    return false;
}

// Vertical win check
template<typename T>
bool connect_4_X_O_board<T>::check_vertical() {
    for (int col = 0; col < this->columns; col++) {
        for (int row = 0; row <= this->rows - 4; row++) {
            if (this->board[row][col] != '-' &&
                this->board[row][col] == this->board[row + 1][col] &&
                this->board[row][col] == this->board[row + 2][col] &&
                this->board[row][col] == this->board[row + 3][col]) {
                return true;
            }
        }
    }
    return false;
}

// Diagonal win check
// Diagonal win check (both slopes)
template<typename T>
bool connect_4_X_O_board<T>::check_diagonal() {
    // Check positive slope diagonals
    for (int row = 0; row <= this->rows - 4; row++) {
        for (int col = 0; col <= this->columns - 4; col++) {
            if (this->board[row][col] != '-' &&
                this->board[row][col] == this->board[row + 1][col + 1] &&
                this->board[row][col] == this->board[row + 2][col + 2] &&
                this->board[row][col] == this->board[row + 3][col + 3]) {
                return true;
            }
        }
    }
    // Check negative slope diagonals
    for (int row = 3; row < this->rows; row++) {
        for (int col = 0; col <= this->columns - 4; col++) {
            if (this->board[row][col] != '-' &&
                this->board[row][col] == this->board[row - 1][col + 1] &&
                this->board[row][col] == this->board[row - 2][col + 2] &&
                this->board[row][col] == this->board[row - 3][col + 3]) {
                return true;
            }
        }
    }
    return false;
}
//__________________________________________________________________________________________________________________________________

#endif

