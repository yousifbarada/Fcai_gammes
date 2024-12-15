#ifndef _3X3X_O_H
#define _3X3X_O_H

#include "BoardGame_Classes.h"
#include <deque>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
class X_O_9x9_Board : public Board<T> {
public:
    X_O_9x9_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;

    ~X_O_9x9_Board() { // Proper cleanup
        for (int i = 0; i < this->rows; i++) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }

private:
    deque<deque<pair<bool, char>>> B;
    bool is_valid_board(int x, int y);
    bool small_check(int startX, int startY);
    bool big_check();
};

template <typename T>
class super_X_O_Player : public Player<T> {
public:
    super_X_O_Player(string name, T symbol);
    void getmove(int& x, int& y) override;
};

template <typename T>
class super_X_O_Random_Player : public RandomPlayer<T> {
public:
    super_X_O_Random_Player(T symbol);
    void getmove(int& x, int& y) override;
};

//--------------------------------------- IMPLEMENTATION

template <typename T>
X_O_9x9_Board<T>::X_O_9x9_Board() {
    this->rows = this->columns = 9;

    // Initialize 3x3 big board
    for (int i = 0; i < 3; ++i) {
        deque<pair<bool, char>> row;
        for (int j = 0; j < 3; ++j) {
            row.emplace_back(false, '-');
        }
        B.push_back(row);
    }

    // Initialize 9x9 board
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = '-';
        }
    }

    this->n_moves = 0;
}

template <typename T>
bool X_O_9x9_Board<T>::is_valid_board(int x, int y) {
    int bx = x / 3, by = y / 3;
    return !B[bx][by].first;
}

template <typename T>
bool X_O_9x9_Board<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != '-') {
        return false;
    }

    int bx = x / 3, by = y / 3;
    if (!is_valid_board(x, y)) return false;

    this->board[x][y] = toupper(symbol);
    this->n_moves++;

    // Update the small board if there is a winner
    if (small_check(bx * 3, by * 3)) {
        B[bx][by] = {true, symbol};
    }

    return true;
}

template <typename T>
void X_O_9x9_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n ||";
        for (int j = 0; j < this->columns; j++) {
            if (B[i/3][j/3].first){
                if (B[i/3][j/3].second=='X'){ cout << "(" << i << "," << j << ")";
                    cout << setw(2) << 'X' << " ||";
                }
                else{ cout << "(" << i << "," << j << ")";
                    cout << setw(2) << 'O' << " ||";
                }
            }
            else if ((j+1)%3==0&&j!=0){
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << this->board[i][j] << " ||";
            }
            else
            {cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
            }
        }
        if ((i+1)%3==0&&i!=0){
          cout << "\n   -------------------------  ---------------------------  -------------------------";
         //cout<<"\n   ------------   ------------  -------------";
        }
       else cout<<endl;

    }
    cout << endl;
}


template <typename T>
bool X_O_9x9_Board<T>::small_check(int startX, int startY) {
    // Check rows, columns, and diagonals within the 3x3 small board
    for (int i = startX; i < startX + 3; ++i) {
        if (this->board[i][startY] == this->board[i][startY + 1] &&
            this->board[i][startY + 1] == this->board[i][startY + 2] &&
            this->board[i][startY] != '-') {
            return true;
        }
    }

    for (int j = startY; j < startY + 3; ++j) {
        if (this->board[startX][j] == this->board[startX + 1][j] &&
            this->board[startX + 1][j] == this->board[startX + 2][j] &&
            this->board[startX][j] != '-') {
            return true;
        }
    }

    if (this->board[startX][startY] == this->board[startX + 1][startY + 1] &&
        this->board[startX + 1][startY + 1] == this->board[startX + 2][startY + 2] &&
        this->board[startX][startY] != '-') {
        return true;
    }

    if (this->board[startX][startY + 2] == this->board[startX + 1][startY + 1] &&
        this->board[startX + 1][startY + 1] == this->board[startX + 2][startY] &&
        this->board[startX][startY + 2] != '-') {
        return true;
    }

    return false;
}

template <typename T>
bool X_O_9x9_Board<T>::big_check() {
    for (int i = 0; i < 3; i++) {
        if ((B[i][0].first && B[i][1].first && B[i][2].first && B[i][0].second == B[i][1].second &&
             B[i][1].second == B[i][2].second) ||
            (B[0][i].first && B[1][i].first && B[2][i].first && B[0][i].second == B[1][i].second &&
             B[1][i].second == B[2][i].second)) {
            return true;
        }
    }

    if ((B[0][0].first && B[1][1].first && B[2][2].first && B[0][0].second == B[1][1].second &&
         B[1][1].second == B[2][2].second) ||
        (B[0][2].first && B[1][1].first && B[2][0].first && B[0][2].second == B[1][1].second &&
         B[1][1].second == B[2][0].second)) {
        return true;
    }

    return false;
}

template <typename T>
bool X_O_9x9_Board<T>::is_win() {
    return big_check();
}

template <typename T>
bool X_O_9x9_Board<T>::is_draw() {
    return this->n_moves == 81 && !is_win();
}

template <typename T>
bool X_O_9x9_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

// Constructor for super_X_O_Player
template <typename T>
super_X_O_Player<T>::super_X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void super_X_O_Player<T>::getmove(int& x, int& y) {
  cout<<this->getname()<<"it`s your turn!!\n";
    cout << "Enter your move (row and column)( 0 - 9 ): ";
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

// Constructor for super_X_O_Random_Player
template <typename T>
super_X_O_Random_Player<T>::super_X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 9;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void super_X_O_Random_Player<T>::getmove(int& x, int& y) {
  cout<<"it`s computer turn!\n";
    x = rand() % 9;
    y = rand() % 9;
}

#endif //_3X3X_O_H
