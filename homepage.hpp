#ifndef HOMEPAGE_HPP
#define HOMEPAGE_HPP

#include <string>

// Global UI Layout Tools
void clearScreen();
void printCentered(const std::string& text, int width);
void displayAnimatedHomepage();

// Sub-Page Navigation Screens (The interactive rooms)
void showRegistrationScreen();
void showLoginScreen();
void showAdminScreen();

#endif