//
// Created by tvyos on 12/4/2024.
//

#ifndef ASSIGNMENT_DEMO_WORDS_X_O_H
#define ASSIGNMENT_DEMO_WORDS_X_O_H
#include "BoardGame_Classes.h"
#include <bits/stdc++.h>

template<typename T>
class words_X_O_Board: public Board<T> {
public:
     // Renamed from 'move' to avoid conflicts
    set<string> words;

    words_X_O_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    ~words_X_O_Board() { // Proper cleanup
        for (int i = 0; i < this->rows; i++) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }

};

template<typename T>
class words_X_O_player: public Player<T>, public words_X_O_Board<T> {
public:

    words_X_O_player() {}
    words_X_O_player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class words_X_O_Random_player : public RandomPlayer<T> {
public:
    void getmove(int& x, int& y) override;
    words_X_O_Random_player(T symbol);
};

// ____________________________________________________________________________________________
#include <bits/stdc++.h>

template<typename T>
words_X_O_Board<T>::words_X_O_Board() {
    this->columns = 3;
    this->rows = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = '-';
        }
    }

    ifstream file("dic.txt");
    if (file.is_open()) {
        string word;
        while (file >> word) {
            words.insert(word);
        }
        file.close();
    }

    this->n_moves = 0;
}

template<typename T>
bool words_X_O_Board<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != '-') {
        return false;
    }
    this->n_moves++;
    this->board[x][y] = toupper(symbol);  // Use symbol instead of 'move'
    return true;
}

template<typename T>
void words_X_O_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ") " << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n----------------------------------------";
    }
    cout << endl;
}

template<typename T>
bool words_X_O_Board<T>::is_win() {
    string check,check2;

    // Horizontal check
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            check = {this->board[i][j], this->board[i][j + 1], this->board[i][j + 2]};
            check2={this->board[i][j + 2],this->board[i][j + 1],this->board[i][j]};
            if (words.find(check) != words.end()||words.find(check2)!=words.end()) {
                return true;
            }
        }
    }

    // Vertical check
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 0; j < this->columns; j++) {
            check = {this->board[i][j], this->board[i + 1][j], this->board[i + 2][j]};
            check2 = {this->board[i+2][j], this->board[i + 1][j], this->board[i][j]};
            if (words.find(check) != words.end()||words.find(check2) != words.end()) {
                return true;
            }
        }
    }

    // Diagonal checks
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            check = {this->board[i][j], this->board[i + 1][j + 1], this->board[i + 2][j + 2]};
            check2={this->board[i+2][j+2], this->board[i + 1][j + 1], this->board[i ][j]};
            if (words.find(check) != words.end()||words.find(check2) != words.end()) {
                return true;
            }
        }
    }
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 2; j < this->columns; j++) {
            check = {this->board[i][j], this->board[i + 1][j - 1], this->board[i + 2][j - 2]};
            check2 = {this->board[i+2][j-2], this->board[i + 1][j - 1], this->board[i ][j]};
            if (words.find(check) != words.end()||words.find(check2) != words.end()) {
                return true;
            }
        }
    }

    return false;
}

template<typename T>
bool words_X_O_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template<typename T>
bool words_X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}
//_______________________________________________________________________________________
template<typename T>
words_X_O_player<T>::words_X_O_player(string Nnam,T s): Player<T>(Nnam,s) {}

template <typename T>
void words_X_O_player<T>::getmove(int& x, int& y) {
  cout<<this->getname()<<"it`s your turn!!\n";
    cout << "\nPlease enter your move x(0 to 2) and y (0 to 2) separated by spaces: ";
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
    cout << "Enter a char to play (A to Z): ";
    char s;
    cin >> s;
    while (!isalpha(s)||cin.fail()){
        cout<<"Enter a valid input\n";
        cin>>s;
    }
    this->symbol=s;// Use symbol instead of 'move'
}

// Constructor for super_X_O_Random_Player
template <typename T>
words_X_O_Random_player<T>::words_X_O_Random_player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";

    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void words_X_O_Random_player<T>::getmove(int& x, int& y) {
  cout<<"it`s computer turn\n";
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    srand(static_cast<unsigned int>(time(0)));

    // Generate a random number between 0 and 25
    int randomIndex = rand() % 26;

    // Map the number to a character in the alphabet (uppercase or lowercase)
    char randomSymbol = 'A' + randomIndex;  // Random letter
    this->symbol = randomSymbol;  // Set the symbol for the random player
}

#endif // ASSIGNMENT_DEMO_WORDS_X_O_H
