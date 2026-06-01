#include <iostream>
#include <cstdlib>
#include <string>
#include <thread> // Used for timing the animation
#include <chrono> // Used for milliseconds definitions
#include "homepage.hpp"

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

    std::cout << "  [SYSTEM NOTE]: This room is locked for Sprint Week 1.\n";
    std::cout << "  Sebastian's data storage modules will be linked here next sprint.\n\n";

    std::cout << "  Press Enter to return to the homepage...";
    std::cin.ignore(1000, '\n'); // Clear any leftover data
    std::cin.get();              // Wait for user to physically press Enter
}

void showLoginScreen() {
    clearScreen();
    std::cout << "\033[36m==========================================================================\n";
    std::cout << "         SKYLINE CYBER CAFE - CUSTOMER LOGIN PORTAL\n";
    std::cout << "==========================================================================\033[0m\n\n";

    std::cout << "  [SYSTEM NOTE]: Real login verification logic will be placed here.\n\n";

    std::cout << "  Press Enter to return to the homepage...";
    std::cin.ignore(1000, '\n');
    std::cin.get();
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