#include <iostream>
using namespace std;
 
class Player {
private:
    char symbol;
    string name;

    public:

    Player(char sym = ' ', string n = " ") : symbol(sym), name(n) {}

    const char getSymbol() {
        return symbol;
    }

    const string getName() {
        return name;
    }
};

class Board {
    private:
    char grid[3][3];
    int filledCells;

    public:
    Board() : filledCells(0) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                grid[i][j] = ' ';
            }
        }
    }

    const void drawBoard() {
        cout << "-------------" << endl;
        for (int i = 0; i<3; i++) {
            cout << "| ";
            for (int j = 0; j<3; j++) {
                cout << grid[i][j] << " | ";
            }
            cout << endl << "-------------" << endl;
        }
    }

    const bool isValidMove(int row, int col) {
        return (row >= 0 && row < 3 && col >= 0 && col < 3 && grid[row][col] == ' ');
    }

    void makeMove(int row, int col, char sym) {
        if(isValidMove(row, col)) {
            grid[row][col] = sym;
            filledCells++;
        }
    }

    const bool checkWin(char sym) {
        for(int i = 0; i < 3; i++) {
            if (grid[i][0] == sym && grid[i][1] == sym && grid[i][2] == sym ) {
                return true;
            }
        }

        for (int i = 0; i < 3; i++) {
            if (grid[0][i] == sym && grid[1][i] == sym && grid[2][i] == sym) {
                return true;
            }
        }

        if (grid[0][0] == sym && grid[1][1] == sym && grid[2][2] == sym) return true;

        if (grid[0][2] == sym && grid[1][1] == sym && grid[2][0] == sym) return true;

        return false;
    }

    const bool isFull() {
        return filledCells == 9;
    }

    const int getFilledCellsCount() {
        return filledCells;
    }
};

class tictactoe {
private:
Board board;
Player players[2];
int currentPlayerIndex;

public: 
tictactoe() : currentPlayerIndex(0) {
    players[0] = Player('X', "Player 1");
    players[1] = Player('O', "Player 2");
}

Player& getCurrentPlayer() {
    return players[currentPlayerIndex];
}

void switchTurn() {
    currentPlayerIndex = (currentPlayerIndex + 1) % 2;
}

void play() {
    int row, col;
    cout << "Welcome to Tic Tac Toe" << endl;

    while(!board.isFull()) {
        board.drawBoard();
        
        Player& currentPlayer = getCurrentPlayer();

        while(true) {
            cout << currentPlayer.getName() << " (" << currentPlayer.getSymbol() << "), enter row (1-3) and column (1-3): ";
            cin >> row >> col;
            row--; col--;

            if (board.isValidMove(row, col)) {
                break;
            } else {
                cout << "Invalid move. Try again" << endl;
            }
        }

        board.makeMove(row, col, currentPlayer.getSymbol());

        if(board.checkWin(currentPlayer.getSymbol())) {
            board.drawBoard();
            cout << currentPlayer.getName() << " wins!" << endl;
            return;
        }

    switchTurn();
    }

    board.drawBoard();
    cout << "It's a draw" << endl;
}
};

int main() {
    string restart; 

    cout << "Do you want to restart after the game is finished ? [Yes|No]" << endl << "> ";
    cin >> restart;

    while(restart == "yes" || restart == "Yes") {
        tictactoe game;
        game.play();
        
        cout << "Do you still want to restart after the game is finished ? [Yes|No]" << endl << "> ";
        cin >> restart;
    }

    return 0;
}