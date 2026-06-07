#include <iostream>
#include <cstdlib>
#include <string>
#include <thread> // Used for timing the animation
#include <chrono> // Used for milliseconds definitions
#include "homepage.hpp"
#include "UserManager/UserManager.h"
#include "Globals/Globals.h"
DataManager dbManager;
UserManager userControl(dbManager);

// Console Width Canvas definition to ensure perfect centering alignment
const int CONSOLE_WIDTH = 80;

// ANSI Color Escape Codes
const std::string RESET   = "\033[0m";
const std::string TEAL    = "\033[36m";
const std::string WHITE   = "\033[37m";
const std::string BOLD    = "\033[1m";
const std::string GRAY    = "\033[90m";

// Function to keep the console clean within one interface phase
void clearScreen() {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

// Math helper to center any raw string dynamically based on our canvas width
void printCentered(const std::string& text, int width) {
    int padding = (width - text.length()) / 2;
    if (padding > 0) {
        for (int i = 0; i < padding; ++i) std::cout << " ";
    }
    std::cout << text << "\n";
}

// Function to draw the main colorful, animating homepage
void displayAnimatedHomepage() {
    clearScreen();

    // Drawing the Border Lines smoothly
    std::cout << TEAL;
    printCentered("==========================================================================", CONSOLE_WIDTH);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Drawing the Huge Skyline Text line-by-line
    std::cout << BOLD << TEAL;
    printCentered("  ____   _  __ __   __ _      ___  _   _  _____ ", CONSOLE_WIDTH);
    std::this_thread::sleep_for(std::chrono::milliseconds(60));
    printCentered(" / ___| | |/ / \\ \\ / /| |    |_ _|| \\ | || ____|", CONSOLE_WIDTH);
    std::this_thread::sleep_for(std::chrono::milliseconds(60));
    printCentered(" \\___ \\ | ' /   \\ V / | |     | | |  \\| ||  _|  ", CONSOLE_WIDTH);
    std::this_thread::sleep_for(std::chrono::milliseconds(60));
    printCentered("  ___) || . \\    | |  | |___  | | | |\\  || |___ ", CONSOLE_WIDTH);
    std::this_thread::sleep_for(std::chrono::milliseconds(60));
    printCentered(" |____/ |_|\\_\\   |_|  |_____||___||_| \\_||_____|", CONSOLE_WIDTH);
    std::cout << RESET;

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << TEAL;
    printCentered("==========================================================================", CONSOLE_WIDTH);
    std::cout << RESET;

    // Sub-headers fading in
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    std::cout << WHITE << BOLD;
    printCentered("CYBER CAFE AUTOMATED BILLING SYSTEM", CONSOLE_WIDTH);
    std::cout << RESET;

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << GRAY;
    printCentered("Auckland CBD Branch", CONSOLE_WIDTH);
    std::cout << RESET << "\n";

    // MENU DISPLAY (Static and aligned)
    std::cout << WHITE;
    std::cout << "        " << TEAL << "[1]" << WHITE << " Register New User\n";
    std::cout << "        " << TEAL << "[2]" << WHITE << " Customer Login (Start Session)\n";
    std::cout << "        " << TEAL << "[3]" << WHITE << " Staff / Admin Portal\n";
    std::cout << "        " << TEAL << "[4]" << WHITE << " Exit System\n\n";

    std::cout << TEAL;
    printCentered("==========================================================================", CONSOLE_WIDTH);
    std::cout << RESET;

    std::cout << "\n  " << BOLD << "Choice: " << RESET;
}

// Sub-Page Navigation Screens (The interactive placeholder rooms)
void showRegistrationScreen() {
    clearScreen();
    std::cout << "\033[36m==========================================================================\n";
    std::cout << "         SKYLINE CYBER CAFE - NEW USER REGISTRATION\n";
    std::cout << "==========================================================================\033[0m\n\n";
    std::cout << "  (Type 'exit' at any time to cancel)\n\n";

    std::string userName;
    std::string email;
    std::string password;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "  Enter your name     : ";
    std::getline(std::cin, userName);
    if (userName == "exit") return;

    std::cout << "  Enter your email    : ";
    std::getline(std::cin, email);
    if (email == "exit") return;

    if (email.find('@') == std::string::npos || email.find('.') == std::string::npos) {
        std::cout << "\n  Invalid email address!\n";
        std::cout << "\n  Press Enter to return...";
        std::cin.get();
        return;
    }

    std::cout << "  Enter your password : ";
    std::getline(std::cin, password);
    if (password == "exit") return;

    bool hasUpper = false, hasLower = false, hasDigit = false, hasSymbol = false;
    for (char c : password) {
        if (isupper(c)) hasUpper = true;
        if (islower(c)) hasLower = true;
        if (isdigit(c)) hasDigit = true;
        if (ispunct(c)) hasSymbol = true;
    }

    if (password.length() < 8) {
        std::cout << "\n  Password must be at least 8 characters!\n";
        std::cout << "\n  Press Enter to return...";
        std::cin.get();
        return;
    }
    if (!hasUpper) {
        std::cout << "\n  Password must contain at least one uppercase letter!\n";
        std::cout << "\n  Press Enter to return...";
        std::cin.get();
        return;
    }
    if (!hasLower) {
        std::cout << "\n  Password must contain at least one lowercase letter!\n";
        std::cout << "\n  Press Enter to return...";
        std::cin.get();
        return;
    }
    if (!hasDigit) {
        std::cout << "\n  Password must contain at least one number!\n";
        std::cout << "\n  Press Enter to return...";
        std::cin.get();
        return;
    }
    if (!hasSymbol) {
        std::cout << "\n  Password must contain at least one symbol (!@#$...)!\n";
        std::cout << "\n  Press Enter to return...";
        std::cin.get();
        return;
    }

    bool success = userControl.register_new_public_user(userName, password, email);

    if (success) {
        std::cout << "\n  Account created successfully! Welcome, " << userName << "!\n";
    } else {
        std::cout << "\n  Registration failed. Email may already be taken.\n";
    }

    std::cout << "\n  Press Enter to return...";
    std::cin.get();
}

void showLoginScreen() {
    clearScreen();
    std::cout << "\033[36m==========================================================================\n";
    std::cout << "         SKYLINE CYBER CAFE - CUSTOMER LOGIN PORTAL\n";
    std::cout << "==========================================================================\033[0m\n\n";
    std::cout << "  (Type 'exit' at any time to cancel)\n\n";

    std::string password;
    std::string userName;
    PublicUser loggedInUser;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        std::cout << "  Enter your username : ";
        std::getline(std::cin, userName);
        if (userName == "exit") return;
        if (userName.empty()) {
            std::cout << "\n  Username cannot be empty!\n";
            continue;
        }

        std::cout << "  Enter your password : ";
        std::getline(std::cin, password);
        if (password == "exit") return;
        if (password.empty()) {
            std::cout << "\n  Password cannot be empty!\n";
            continue;
        }
        if (password.length() < 8) {
            std::cout << "\n  Password must be at least 8 characters!\n";
            continue;
        }


        bool success = userControl.authenticate_user(userName, password, loggedInUser);

        if (success) {
            std::cout << "\n  Welcome back, " << loggedInUser.userName << "!\n";
            std::cin.get();
            return;
        } else {
            std::cout << "\n  Invalid username or password.\n";
            std::cout << "  Type 'back' to return to menu or press Enter to try again: ";
            std::string retry;
            std::getline(std::cin, retry);
            if (retry == "back") return;
        }
    }
}

void showAdminScreen() {
    clearScreen();
    std::cout << "\033[31m==========================================================================\n";
    std::cout << "         SKYLINE CYBER CAFE - SECURE STAFF PORTAL\n";
    std::cout << "==========================================================================\033[0m\n\n";

    std::cout << "  [CRITICAL]: Authorized Personnel Only.\n\n";

    std::cout << "  Press Enter to return to the homepage...";
    std::cin.ignore(1000, '\n');
    std::cin.get();
}