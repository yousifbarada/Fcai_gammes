#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <cstdlib>
using namespace std;
int total_w_o=0;
int total_w_x=0;
template<typename T>
class tic_tac_toe : public Board<T> {
public:
    int player1 = 0;
    int player2 = 0;

    tic_tac_toe();
    ~tic_tac_toe(); // Destructor for cleanup
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    int Round_win();
    void check_Round();
    bool is_draw();
    bool game_is_over();

};

template<typename T>
class tic_tac_toe_player : public Player<T> {
public:
    tic_tac_toe_player();
    tic_tac_toe_player(string name, T symbol);
    void getmove(int& x, int& y);
};

template<typename T>
class tic_tac_toe_Random_player : public RandomPlayer<T> {
public:
    void getmove(int& x, int& y) override;
    tic_tac_toe_Random_player(T symbol);
};

// Implementation of tic_tac_toe
template<typename T>
tic_tac_toe<T>::tic_tac_toe() {
    this->rows = this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = '-';
        }
    }
    this->n_moves = 0;
}

template<typename T>
tic_tac_toe<T>::~tic_tac_toe() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
}

template<typename T>
bool tic_tac_toe<T>::update_board(int x, int y, T mark) {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && (this->board[x][y] == '-' || mark == '-')) {
        if (mark == '-') {
            this->n_moves--;
            this->board[x][y] = '-';
        } else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}

template<typename T>
void tic_tac_toe<T>::display_board() {
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

template<typename T>
int tic_tac_toe<T>::Round_win() {
    int n=0;
    char  currunt= (this->n_moves%2!=0?'X':'O');
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (j + 2 < this->columns &&
                this->board[i][j] == this->board[i][j + 1] &&
                this->board[i][j + 1] == this->board[i][j + 2] &&
                this->board[i][j + 2] != '-'&& this->board[i][j]== currunt) {
                n++;
            }
            if (i + 2 < this->rows &&
                this->board[i][j] == this->board[i + 1][j] &&
                this->board[i + 1][j] == this->board[i + 2][j] &&
                this->board[i + 2][j] != '-'&&this->board[i][j]== currunt) {
                n++;
            }
            if (i + 2 < this->rows && j + 2 < this->columns &&
                this->board[i][j] == this->board[i + 1][j + 1] &&
                this->board[i + 1][j + 1] == this->board[i + 2][j + 2] &&
                this->board[i + 2][j + 2] != '-'&&this->board[i][j]== currunt) {
                n++;
            }
            if (i + 2 < this->rows && j - 2 >= 0 &&
                this->board[i][j] == this->board[i + 1][j - 1] &&
                this->board[i + 1][j - 1] == this->board[i + 2][j - 2] &&
                this->board[i + 2][j - 2] != '-'&&this->board[i][j]== currunt) {
                n++;
            }
        }
    }
    return n;
}

template<typename T>
bool tic_tac_toe<T>::is_draw() {
    return (player1 == player2 && this->n_moves == 24);
}

template<typename T>
bool tic_tac_toe<T>::game_is_over() {
    return (this->n_moves == 24 && !is_win());
}

template<typename T>
void tic_tac_toe<T>::check_Round() {
    int curnt_T=(this->n_moves%2!=0)? total_w_x:total_w_o;
    int m=Round_win();
    int z=abs(m-curnt_T);
    if ( this->n_moves % 2 == 0) {
        total_w_o = m;
        player1 += z;
    }
    else if ( this->n_moves % 2 != 0) {
        player2 += z;
        total_w_x=m;
    }
}

template<typename T>
bool tic_tac_toe<T>::is_win() {
    check_Round();
    if (this->n_moves == 24) {
        return player1 != player2;
    }
    cout<<"player 1 score is: "<<this->player2<<endl;
    cout<<"player 2 score is: "<<this->player1<<endl;
    return false;
}

// Implementation of tic_tac_toe_player
template<typename T>
tic_tac_toe_player<T>::tic_tac_toe_player(string name, T symbol) : Player<T>(name, symbol) {}

template<typename T>
void tic_tac_toe_player<T>::getmove(int& x, int& y) {
  cout<<this->getname()<<"it`s your turn!!\n";
    do {
        cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
        cin >> x >> y;
    } while (x < 0 || x >= 5 || y < 0 || y >= 5||cin.fail());
}

// Implementation of tic_tac_toe_Random_player
template<typename T>
tic_tac_toe_Random_player<T>::tic_tac_toe_Random_player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template<typename T>
void tic_tac_toe_Random_player<T>::getmove(int& x, int& y) {
  cout<<"it`s computer turn\n";
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}
#endif
//___________________________________________________________________________________________________________________________________

