#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class AccountManager {
public:
    bool loginOrSignup(std::string& username);
    void showStats(const std::string& username);
    void manageAccount(std::string& username);
};

#endif
