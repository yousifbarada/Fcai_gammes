#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
using namespace std;
bool s=false;

// Class for the numerical tic-tac-toe board
template<typename T>
class numerical_tic_tac_toe_board : public Board<T> {
public:
    int goal = 15;
    numerical_tic_tac_toe_board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    bool isValidMove(int x, int y) const;
    ~numerical_tic_tac_toe_board() { // Proper cleanup
        for (int i = 0; i < this->rows; i++) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }

};

// Class for a human numerical tic-tac-toe player
template<typename T>
class numerical_tic_tac_toe_Player : public Player<T>,numerical_tic_tac_toe_board<T> {
public:
    set<int> set1 = {1, 3, 5, 7, 9};  // Player 1's numbers
    set<int> set2 = {2, 4, 6, 8};     // Player 2's numbers
    set<int> game_set;                // Available numbers for the player
T last_choise;
    numerical_tic_tac_toe_Player() {}
    numerical_tic_tac_toe_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

// Class for a random AI numerical tic-tac-toe player
template<typename T>
class numerical_tic_tac_toe_Random_Player : public RandomPlayer<T>,numerical_tic_tac_toe_board<T> {
public:
    set<int> set1 = {1, 3, 5, 7, 9};
    set<int> set2 = {2, 4, 6, 8};
    set<int> game_set;
    T lasett_choise;

    numerical_tic_tac_toe_Random_Player(T symbol);
    void getmove(int& x, int& y) override;
};

// ---------------- Implementation of numerical_tic_tac_toe_board ----------------

template<typename T>
numerical_tic_tac_toe_board<T>::numerical_tic_tac_toe_board() {
    this->rows = 3;
    this->columns = 3;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = -10;  // Initialize empty cells
        }
    }
    this->n_moves = 0;
}

template<typename T>
bool numerical_tic_tac_toe_board<T>::update_board(int x, int y, T symbol) {
    if (!isValidMove(x, y)){s=false; return s;}  // Validate the move
    this->board[x][y] = symbol;
    s= true;
    // Place the symbol
    this->n_moves++;

    return true;
}

template<typename T>
void numerical_tic_tac_toe_board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j]==-10) {
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << 0 << " |";
            }
            else{
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << this->board[i][j] << " |";
            }
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

template<typename T>
bool numerical_tic_tac_toe_board<T>::is_win() {
    int check;

    // Horizontal check
    for (int i = 0; i < this->rows; i++) {
        check = accumulate(this->board[i], this->board[i] + this->columns, 0);
        if (check == goal) return true;
    }

    // Vertical check
    for (int j = 0; j < this->columns; j++) {
        check = 0;
        for (int i = 0; i < this->rows; i++) {
            check += this->board[i][j];
        }
        if (check == goal) return true;
    }

    // Diagonal checks
    check = 0;
    for (int i = 0; i < this->rows; i++) check += this->board[i][i];
    if (check == goal) return true;

    check = 0;
    for (int i = 0; i < this->rows; i++) check += this->board[i][this->columns - i - 1];
    if (check == goal) return true;

    return false;
}

template<typename T>
bool numerical_tic_tac_toe_board<T>::is_draw() {
    return (this->n_moves == this->rows * this->columns && !is_win());
}

template<typename T>
bool numerical_tic_tac_toe_board<T>::game_is_over() {
    return is_win() || is_draw();
}

template<typename T>
bool numerical_tic_tac_toe_board<T>::isValidMove(int x, int y) const {
    return x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == -10;

}

// ---------------- Implementation of numerical_tic_tac_toe_Player ----------------

template<typename T>
numerical_tic_tac_toe_Player<T>::numerical_tic_tac_toe_Player(string name, T symbol) : Player<T>(name, symbol) {
    this->game_set = (symbol == 1) ? set1 : set2;
}

template<typename T>
void numerical_tic_tac_toe_Player<T>::getmove(int& x, int& y) {
  cout<<this->getname()<<"it`s your turn!!\n";
    if (s){
        game_set.erase(this->last_choise);
    }

    cout << "\nEnter your move (x, y),(x:0,2 ,y:0,2) ";
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
    cout << "Enter a number to play:( ";
    for (auto i:game_set)cout<<i<<" , ";
    cout<<')';
    int z;
    cin >> z;
    while (this->game_set.find(z) == this->game_set.end()) {
        cout << "Invalid number. Try again: ";
        cin >> z;
    }
    this->symbol = z;
    this->last_choise=z;
    // Remove the chosen number
}

// ---------------- Implementation of numerical_tic_tac_toe_Random_Player ----------------

template<typename T>
numerical_tic_tac_toe_Random_Player<T>::numerical_tic_tac_toe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->game_set = (symbol == 1) ? set1 : set2;
}

template<typename T>

void numerical_tic_tac_toe_Random_Player<T>::getmove(int& x, int& y) {
  cout<<"it`s the computer turn\n";
    if (s){
        game_set.erase(this->lasett_choise);
    }
    do {
        x = rand() % 3;  // Random row
        y = rand() % 3;  // Random column
    } while (!this->isValidMove(x, y));  // Ensure the move is valid

    int z = *next(this->game_set.begin(), rand() % this->game_set.size());
    this->symbol = z;
    this->lasett_choise=z;
    // Remove the chosen number
}
//__________________________________________________________________________________________
//sus
