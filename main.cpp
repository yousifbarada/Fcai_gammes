#include <iostream>
#include "9x9.h"
#include "BoardGame_Classes.h"
#include "nurmirical_tic_tac_toc.h"
#include "sus_tic-tac-toc.h"
#include "Tic_Tac_Toe.h"
#include "pyramid_X-O.h"
#include "words_X_O.h"
#include "X-O_connect4.h"
#include"misere.h"
//#include "connect_4_min_max.h"

using namespace std;
vector<string>v={};
int main() {
    int f_choice, s_choice;
    string player1Name, player2Name;
    while (true) {
        cout << "Welcome to FCAI Games. :)\n";
        cout << "Choose a game to play:\n";
        cout << "1) Pyramid X-O (char)\n";
        cout << "2) X-O Connect 4 (char)\n";
        cout << "3) Words X-O (char)\n";
        cout << "4) Numerical Tic-Tac-Toe (int)\n";
        cout << "5) SUS Tic-Tac-Toe (char)\n";
        cout << "6) Reverse Tic-Tac-Toe (char)\n";
        cout << "7) 5x5 Tic-Tac-Toe (char)\n8)super tic tac toe \n9)exit";
        cin >> f_choice;
        if (f_choice==9){
            cout<<"Thank You To Play Our game !!!!!!!!!\n this done by Eng/yousif_Edris \n Eng/Habiba_ibrahim \n Eng/Habiba . "
                    ;return 0;
        }
        if (f_choice == 4) { // Numerical Tic-Tac-Toe (int-based game)
            Board<int> *B = new numerical_tic_tac_toe_board<int>();
            Player<int> *players[2];

            cout << "Enter Player 1 name: ";
            cin >> player1Name;
            cout << "Choose Player 1 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "3. Smart Computer (AI)\n";
            cin >> s_choice;

            switch (s_choice) {
                case 1:
                    players[0] = new numerical_tic_tac_toe_Player<int>(player1Name, 1);
                    break;
                case 2:
                    players[0] = new numerical_tic_tac_toe_Random_Player<int>(1);
                    break;
                case 3:
                    cout << "Smart Computer (AI) not implemented yet.\n";
                    return 1;
                default:
                    cout << "Invalid choice for Player 1. Exiting the game.\n";
                    return 1;
            }

            cout << "Enter Player 2 name: ";
            cin >> player2Name;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "3. Smart Computer (AI)\n";
            cin >> s_choice;

            switch (s_choice) {
                case 1:
                    players[1] = new numerical_tic_tac_toe_Player<int>(player2Name, 2);
                    break;
                case 2:
                    players[1] = new numerical_tic_tac_toe_Random_Player<int>(2);
                    break;
                case 3:
                    cout << "Smart Computer (AI) not implemented yet.\n";
                    return 1;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                    return 1;
            }

            GameManager<int> game(B, players);
            game.run();

            delete B;
            delete players[0];
            delete players[1];

        } else { // Handle char-based games
            Board<char> *B = nullptr;
            Player<char> *players[2];

            switch (f_choice) {
                case 1:
                    B = new pyramid_X_O_board<char>();
                    break;
                case 2:
                    B = new connect_4_X_O_board<char>();
                    break;
                case 3:
                    B = new words_X_O_Board<char>();
                    break;
                case 5:
                    B = new SUS<char>();
                    break;
                case 6:
                    B = new r_X_O_Board<char>();
                    break;
                case 7:
                    B = new tic_tac_toe<char>();
                    break;
                case 8:
                    B = new X_O_9x9_Board<char>();
                    break;
                default:
                    cout << "Invalid choice. Exiting the game.\n";
                    return 1;
            }

            cout << "Enter Player 1 name: ";
            cin >> player1Name;
            cout << "Choose Player 1 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "3. Smart Computer (AI)\n";
            cin >> s_choice;
            switch (s_choice) {
                case 1:
                    if (f_choice == 1) players[0] = new pyramid_X_O_player<char>(player1Name, 'X');
                    else if (f_choice == 2) players[0] = new connect_4_X_O_player<char>(player1Name, 'X');
                    else if (f_choice == 3) players[0] = new words_X_O_player<char>(player1Name, 'X');
                    else if (f_choice == 5) players[0] = new SUS_Player<char>(player1Name, 'S');
                    else if (f_choice == 6) players[0] = new r_X_O_Player<char>(player1Name, 'X');
                    else if (f_choice == 7) players[0] = new tic_tac_toe_player<char>(player1Name, 'X');
                    else if (f_choice == 8) players[0] = new super_X_O_Player<char>(player1Name, 'X');
                    break;
                case 2:
                    if (f_choice == 1) players[0] = new pyramid_X_O_Random_player<char>('X');
                    else if (f_choice == 2) players[0] = new connect_4_X_O_Random_player<char>('X');
                    else if (f_choice == 3) players[0] = new words_X_O_Random_player<char>('X');
                    else if (f_choice == 5) players[0] = new SUS_Random_Player<char>('S');
                    else if (f_choice == 6) players[0] = new r_o_random<char>('X');
                    else if (f_choice == 7) players[0] = new tic_tac_toe_Random_player<char>('X');
                    else if (f_choice == 8) players[0] = new super_X_O_Random_Player<char>('X');
                    break;
                case 3:
                        //players[0]=new connect4_Ai<char>('X');
                    cout << "Smart Computer (AI) not implemented yet.\n";
                    return 1;
                default:
                    cout << "Invalid choice for Player 1. Exiting the game.\n";
                    return 1;
            }

            cout << "Enter Player 2 name: ";
            cin >> player2Name;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "3. Smart Computer (AI)\n";
            cin >> s_choice;

            switch (s_choice) {
                case 1:
                    if (f_choice == 1) players[1] = new pyramid_X_O_player<char>(player2Name, 'O');
                    else if (f_choice == 2) players[1] = new connect_4_X_O_player<char>(player2Name, 'O');
                    else if (f_choice == 3) players[1] = new words_X_O_player<char>(player2Name, 'O');
                    else if (f_choice == 5) players[1] = new SUS_Player<char>(player2Name, 'U');
                    else if (f_choice == 6) players[1] = new r_X_O_Player<char>(player2Name, 'O');
                    else if (f_choice == 7) players[1] = new tic_tac_toe_player<char>(player2Name, 'O');
                    else if (f_choice == 8) players[1] = new super_X_O_Player<char>(player1Name, 'O');
                    break;
                case 2:
                    if (f_choice == 1) players[1] = new pyramid_X_O_Random_player<char>('O');
                    else if (f_choice == 2) players[1] = new connect_4_X_O_Random_player<char>('O');
                    else if (f_choice == 3) players[1] = new words_X_O_Random_player<char>('O');
                    else if (f_choice == 5) players[1] = new SUS_Random_Player<char>('U');
                    else if (f_choice == 6) players[1] = new r_o_random<char>('O');
                    else if (f_choice == 7) players[1] = new tic_tac_toe_Random_player<char>('O');
                    else if (f_choice == 8) players[1] = new super_X_O_Random_Player<char>('O');
                    break;
                case 3:
                    cout << "Smart Computer (AI) not implemented yet.\n";
                    return 1;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";

            }

            GameManager<char> game(B, players);
            game.run();
             int choooise;cout<<"if your want to try another game\n 1)yes \n 2)no";
            cin>>choooise;
            if (choooise==2){
              cout<<"Thank You To Play Our game !!!!!!!!!\n this done by\n Eng/yousif_Edris \n Eng/Habiba_ibrahim \n Eng/Habiba_Ahamed. ";
            return 0;
            }
            delete B;
            delete players[0];
            delete players[1];
        }


    }

}