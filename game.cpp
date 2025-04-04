#include "game.h"
#include <iostream>
#include <conio.h> // For _getch()
#include <windows.h> // For system("cls")

Game::Game(std::string user) : username(user), mistakes(0) {}

int Game::showMenu() {
    int choice;
    std::cout << "\nسلام " << username << "! لطفاً یکی از گزینه‌ها را انتخاب کن:\n";
    std::cout << "1. شروع بازی\n2. دیدن آمار\n3. مدیریت اکانت\n4. خروج\n";
    std::cin >> choice;
    return choice;
}

void Game::loadPuzzle(int level) {
    // Sample static easy puzzle
    int easy[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
            board[i][j] = easy[i][j];
            fixed[i][j] = (easy[i][j] != 0);
        }
}

void Game::displayBoard(int cursorX, int cursorY) {
    system("cls");
    std::cout << "\n     جدول سودوکو (اشتباهات: " << mistakes << "/3)\n\n";
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) std::cout << "  +-------+-------+-------+\n";
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0) std::cout << "  |";
            if (i == cursorY && j == cursorX) std::cout << "[" << (board[i][j] ? board[i][j] : ' ') << "]";
            else std::cout << " " << (board[i][j] ? std::to_string(board[i][j]) : " ") << " ";
        }
        std::cout << "|\n";
    }
    std::cout << "  +-------+-------+-------+\n";
}

bool Game::isValidMove(int row, int col, int val) {
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == val || board[i][col] == val)
            return false;
    }
    int boxStartRow = row / 3 * 3;
    int boxStartCol = col / 3 * 3;
    for (int i = boxStartRow; i < boxStartRow + 3; i++) {
        for (int j = boxStartCol; j < boxStartCol + 3; j++) {
            if (board[i][j] == val)
                return false;
        }
    }
    return true;
}

bool Game::isBoardFull() {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (board[i][j] == 0)
                return false;
    return true;
}

void Game::start() {
    int level = 1;
    std::cout << "سطح بازی را انتخاب کنید (1 = آسان، فعلاً فقط این فعال است): ";
    std::cin >> level;

    loadPuzzle(level);
    int x = 0, y = 0;
    mistakes = 0;

    while (true) {
        displayBoard(x, y);
        std::cout << "با کلیدهای w/a/s/d حرکت کن، عدد وارد کن یا q برای خروج: ";
        char ch = _getch();

        if (ch == 'q') break;
        else if (ch == 'w' && y > 0) y--;
        else if (ch == 's' && y < 8) y++;
        else if (ch == 'a' && x > 0) x--;
        else if (ch == 'd' && x < 8) x++;
        else if (ch >= '1' && ch <= '9') {
            if (fixed[y][x]) continue;
            int val = ch - '0';
            if (isValidMove(y, x, val)) {
                board[y][x] = val;
            } else {
                mistakes++;
                if (mistakes >= 3) {
                    std::cout << "\n\nسه اشتباه انجام دادی! بازی تموم شد!\n";
                    break;
                }
            }
        }

        if (isBoardFull()) {
            std::cout << "\nآفرین! جدول رو کامل کردی.\n";
            break;
        }
    }
}
