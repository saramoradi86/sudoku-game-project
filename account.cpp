#include "account.h"
#include <iostream>
#include <fstream>
#include <map>
#include <conio.h>

std::string hidePassword() {
    std::string pass;
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b' && !pass.empty()) {
            std::cout << "\b \b";
            pass.pop_back();
        } else {
            pass += ch;
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    return pass;
}

bool loadAccounts(std::map<std::string, std::string>& users) {
    std::ifstream fin("accounts.txt");
    if (!fin) return false;
    std::string username, password;
    while (fin >> username >> password) {
        users[username] = password;
    }
    return true;
}

bool AccountManager::loginOrSignup(std::string& username) {
    std::map<std::string, std::string> users;
    loadAccounts(users);

    std::cout << "1. ثبت‌نام\n2. ورود\n";
    int choice;
    std::cin >> choice;
    std::cout << "نام کاربری: ";
    std::cin >> username;
    std::cout << "رمز عبور: ";
    std::string password = hidePassword();

    if (choice == 1) {
        if (users.count(username)) {
            std::cout << "این نام کاربری قبلاً ثبت شده.\n";
            return false;
        }
        std::ofstream fout("accounts.txt", std::ios::app);
        fout << username << ' ' << password << '\n';
        return true;
    } else {
        if (!users.count(username) || users[username] != password) {
            std::cout << "نام کاربری یا رمز اشتباه است.\n";
            return false;
        }
        return true;
    }
}

void AccountManager::showStats(const std::string& username) {
    std::cout << "در حال حاضر قابلیت نمایش برد و باخت پیاده‌سازی نشده (قابل اضافه شدن است).\n";
}

void AccountManager::manageAccount(std::string& username) {
    std::cout << "در حال حاضر قابلیت تغییر رمز یا حذف اکانت پیاده‌سازی نشده (قابل اضافه شدن است).\n";
}
