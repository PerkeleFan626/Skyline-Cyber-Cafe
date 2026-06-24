#include <iostream>
#include "homepage/homepage.hpp"

int main() {
    int choice = 0;
    bool running = true;

    while (running) {
        displayAnimatedHomepage(); //

        // 2. Safe input validation
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        // 3. Page Routing Engine
        switch (choice) {
            case 1:
                showRegistrationScreen(); // Jumps to the registration room
                break;
            case 2:
                showLoginScreen();        // Jumps to the login room
                break;
            case 3:
                showAdminScreen();        // Jumps to the staff room
                break;
            case 4:
                clearScreen();
                std::cout << "\nShutting down Skyline System. Goodbye!\n";

                running = false;          // Breaks the core loop completely
                break;
            default:
                // If they type a random number like 7, do nothing and redraw home
                break;
        }
    }

    return 0;
}