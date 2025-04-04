#ifndef GAME_H
#define GAME_H

#include <string>

class Game {
    std::string username;
    int board[9][9];
    bool fixed[9][9];
    int mistakes;

public:
    Game(std::string user);
    int showMenu();
    void start();
    void loadPuzzle(int level);
    void displayBoard(int cursorX = -1, int cursorY = -1);
    bool isValidMove(int row, int col, int val);
    bool isBoardFull();
};

#endif
