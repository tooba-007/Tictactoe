#include <iostream>
#include <fstream>
using namespace std;

void display(char** board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) {
                cout << " | ";
            }
        }
        cout << endl;
        if (i < 2) {
            cout << "----------" << endl;
        }
    }
}

void filee(char** board, ofstream& f) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            f << board[i][j];
            if (j < 2) {
                f << " | ";
            }
        }
        f << endl;
        if (i < 2) {
            f << "----------" << endl;
        }
    }
}

bool winchk1(char** board, char player) {
    for (int i = 0; i < 3; i++) {
        // Check rows and columns
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    return false;
}

// Function to check if the board is full (draw)
bool full(char** board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

int main() {
    ofstream file;
    file.open("game_statistics.txt");
    cout << "      ----------------------     " << endl;;
    cout << "     WELCOME TO TIC TAC TOE <3 " << endl;;
    cout << "      ----------------------    " << endl;;
    cout << endl;
    file << "       ---------------------     " << endl;;
    file << "     WELCOME TO TIC TAC TOE <3 " << endl;;
    file << "      ----------------------    " << endl;;
    file << endl;

    char** board = new char* [3];
    for (int i = 0; i < 3; i++) {
        board[i] = new char[3];
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
    const int maxlength = 50;
    char player1[maxlength], player2[maxlength];
    cout << "Player 1, enter your initial: ";
    cin.getline(player1, maxlength);
    cout << "Player 2, enter your initial: ";
    cin.getline(player2, maxlength);

    // Assign X and O to players
    cout << player1 << " is assigned by X" << endl;
    cout << player2 << " is assigned by O." << endl; 
    file << player1 << " is assigned by X" << endl;
    file << player2 << " is assigned by O." << endl;
    cout << endl;

    char* symbol = player1;//symbol=X

    while (true)
    {
        display(board);
        int row, col;

    againrow:
        cout << symbol << " enter row(0 - 2) : ";
        cin >> row;
        if (row < 0 || row > 2)
        {
            cout << "Invalid row, please enter a number between 0 and 2." << endl;
            goto againrow;
        }

    againcol:
        cout << symbol << " enter column (0-2): ";
        cin >> col;
        if (col < 0 || col > 2)
        {
            cout << "Invalid column, please enter a number between 0 and 2." << endl;
            goto againcol;
        }

        // Check if the selected spot is empty
        if (board[row][col] == ' ')
        {
            if (symbol == player1)
            {
                board[row][col] = 'X';
                if (winchk1(board, 'X')) {
                    display(board);
                    cout << endl;
                    cout << "WOHOO!!! " << symbol << "  WINS ;))" << endl;
                    file << "WOHOO!!! " << symbol << "  WINS ;))" << endl;

                    // Determine the losing player
                    char* losingPlayerInitial;
                    if (symbol == player1) {
                        losingPlayerInitial = player2;
                    }
                    else {
                        losingPlayerInitial = player1;
                    }
                    cout << losingPlayerInitial << " loses ;((" << endl;
                    file << losingPlayerInitial << " loses ;((" << endl;

                    filee(board, file);
                    break;
                }
                else if (full(board)) {
                    display(board);
                    cout << "IT'S A DRAW!!!" << endl;
                    file << "IT'S A DRAW!!!" << endl;
                    filee(board, file);
                    break;
                }
                // Switch turns
                else {
                    if (symbol == player1) {
                        symbol = player2;
                        // currentPlayerInitial = player2[0];
                    }
                    else {
                        symbol = player1;
                        // currentPlayerInitial = player1[0];
                    }
                }
            }

            else {
                board[row][col] = 'O';
                if (winchk1(board, 'O')) {
                    display(board);
                    cout << endl;
                    cout << "WOHOO!!! " << symbol << "  WINS ;))" << endl;
                    file << "WOHOO!!! " << symbol << "  WINS ;))" << endl;

                    // Determine the losing player
                    char* losingPlayerInitial;
                    if (symbol == player2) {
                        losingPlayerInitial = player1;
                    }
                    else {
                        losingPlayerInitial = player2;
                    }
                    cout << losingPlayerInitial << " loses ;((" << endl;
                    file << losingPlayerInitial << " loses ;((" << endl;

                    filee(board, file);
                    break;
                }
                else if (full(board)) {
                    display(board);
                    cout << "IT'S A DRAW!!!" << endl;
                    file << "IT'S A DRAW!!!" << endl;
                    filee(board, file);
                    break;
                }
                // Switch turns
                else {
                    if (symbol == player1) {
                        symbol = player2;
                        // currentPlayerInitial = player2[0];
                    }
                    else {
                        symbol = player1;
                        // currentPlayerInitial = player1[0];
                    }
                }

            }
        }
        // If the spot is already taken
        else {
            cout << "That spot is already taken. Try again." << endl;
        }
    }

    // Cleanup dynamic memory
    for (int i = 0; i < 3; i++) {
        delete[] board[i];
    }
    delete[] board;
    // Close the file
    file.close();
    system("pause");
    return 0;
}