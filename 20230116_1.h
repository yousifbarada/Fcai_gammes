
#ifndef ASSIGNMENT_DEMO_PYRAMID_X_O_H
#define ASSIGNMENT_DEMO_PYRAMID_X_O_H

#include "BoardGame_Classes.h"
template<typename T>
class pyramid_X_O_board:public  Board<T> {
public:
    pyramid_X_O_board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win() ;
    bool is_draw() ;
     bool game_is_over() ;
    ~pyramid_X_O_board() { // Proper cleanup
        for (int i = 0; i < this->rows; i++) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }
};
template<typename T>
class pyramid_X_O_player:public Player<T>{
public:
    pyramid_X_O_player(){}
    pyramid_X_O_player(string name,T sympol);
    void getmove(int& x, int& y);

};
template <typename T>
class pyramid_X_O_Random_player : public RandomPlayer<T> {
public:
    int dimention2;
    void getmove(int& x, int& y) override;
    pyramid_X_O_Random_player(T symbol);
};
// ____________________________________________________________________________________________
#include<bits/stdc++.h>
template<typename T>
pyramid_X_O_board<T>:: pyramid_X_O_board(){
     this->columns = 5;this->rows =3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            if (i==0&&j!=2|| i==1&&j==0||i==1&&j==4){
                this->board[i][j] = 'N';
            }
            else{
                this->board[i][j] = '-';
            }
           //
        }
    }
    this->n_moves = 0;

}
template <typename T>
bool pyramid_X_O_board<T>::update_board(int x, int y, T mark) {
    // Ensure the coordinates are within bounds
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) {
        return false;
    }

    // Ensure the move is valid (cell is empty or undo operation)
    if (this->board[x][y] == '-' || mark == '-') {
        if (mark == '-') { // Undo operation
            if (this->board[x][y] != 'N') { // Only undo valid moves
                this->n_moves--;
                this->board[x][y] = '-'; // Reset the cell to empty
            }
        }
        else { // Place a new mark
            this->n_moves++;
            this->board[x][y] = toupper(mark); // Store the uppercase version of the mark
        }
        return true;
    }

    // If the move is invalid, return false
    return false;
}

template<typename T>
void pyramid_X_O_board<T>::display_board() {

    for (int i = 0; i < this->rows; i++) {
       cout << "\n ";
        for (int j = 0; j < this->columns; j++) {

             if(i==0&&j+1== this->columns) cout << "\n              ------------------------------------------";
            else if(i==1&&j+1== this->columns)cout << "\n        -----------------------------------------------------------";

            if (this->board[i][j]!='N') {
                if (i==0){
                    cout << "                              |(" << i << "," << j << ")  ";
                    cout << setw(2) << this->board[i][j] << "|";

                }

                else if (i==1){
                    cout << "         |(" << i << "," << j << ")  ";
                    cout << setw(2) << this->board[i][j] << " |";

                }

                else if (i==2) {
                    cout << "|(" << i << "," << j << ")    ";
                    cout << setw(2) << this->board[i][j] << " |";
                        if (j==4){cout << "|(" << i << "," << j << ")    ";
                            cout << setw(2) << this->board[i][j] << " |"; cout << "\n----------------------------------------------------------------------------------";}
                }
            }

        }


    }
    cout << endl;
}
template<typename T>
bool pyramid_X_O_board<T>::is_win() {
    // Check vertical columns
    for (int col = 0; col < this->columns; col++) {
        if (this->board[0][col] != '-' && this->board[0][col] != 'N' &&
            this->board[0][col] == this->board[1][col] &&
            this->board[1][col] == this->board[2][col]) {
            return true;
        }
    }

    // Check horizontal rows
    for (int row = 0; row < this->rows; row++) {
        T first_symbol = '-';
        bool is_winning_row = true;

        for (int col = 0; col < this->columns; col++) {
            if (this->board[row][col] != 'N'|| this->board[row][col]!='-') { // Skip invalid cells
                if (first_symbol == '-') {
                    first_symbol = this->board[row][col];
                }
                else if (this->board[row][col] != first_symbol || this->board[row][col] == '-') {
                    is_winning_row = false;
                    break;
                }
            }
        }
        if (is_winning_row && first_symbol != '-') {
            return true;
        }
    }

    // Check diagonals
    if (this->board[0][2] != '-' && this->board[0][2] != 'N') {
        // Top-left to bottom-right diagonal
        if (this->board[0][2] == this->board[1][3] && this->board[1][3] == this->board[2][4]) {
            return true;
        }
        // Top-right to bottom-left diagonal
        if (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0]) {
            return true;
        }
    }

    return false; // No winning condition met
}

template <typename T>
bool pyramid_X_O_board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool pyramid_X_O_board<T>::game_is_over() {
    return is_win() || is_draw();
}

//_______________________________________________________________________________________
template<typename T>
pyramid_X_O_player<T>::pyramid_X_O_player(string Nname,T s):Player<T>(Nname,s){}

template <typename T>
void pyramid_X_O_player<T>::getmove(int& x, int& y) {
  cout<<this->getname()<<"it`s your turn!!\n";

    cout << "\nPlease enter your move x(0 to 2) and y (0 to 4) separated by spaces: ";
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
pyramid_X_O_Random_player<T>::pyramid_X_O_Random_player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->dimention2=5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void pyramid_X_O_Random_player<T>::getmove(int& x, int& y) {
  cout<<"computer plays\n";
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimention2;
}
//_______________________________________________________________________________________________________
//sus

#endif
