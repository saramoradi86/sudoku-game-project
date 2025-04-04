#include <iostream>
#include "game.h"
#include "account.h"

int main() {
    AccountManager accountManager;
    std::string username;

    if (!accountManager.loginOrSignup(username)) {
        std::cout << "\nورود/ثبت‌نام ناموفق بود." << std::endl;
        return 0;
    }

    Game game(username);
    while (true) {
        switch (game.showMenu()) {
            case 1:
                game.start();
                break;
            case 2:
                accountManager.showStats(username);
                break;
            case 3:
                accountManager.manageAccount(username);
                break;
            case 4:
                std::cout << "\nخروج از برنامه. خداحافظ!" << std::endl;
                return 0;
        }
    }

    return 0;
}
