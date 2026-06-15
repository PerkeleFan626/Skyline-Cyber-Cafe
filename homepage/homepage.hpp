#ifndef HOMEPAGE_HPP
#define HOMEPAGE_HPP

#include <string>
#include "../DataManager/DataManager.h"

void clearScreen();
void printCentered(const std::string& text, int width);
void displayAnimatedHomepage();

// Sub-Page Navigation Screens (The interactive rooms)
void showRegistrationScreen();
void showLoginScreen();
void showAdminScreen();
void showAdminDashboard(AdminUser& loggedInAdmin);
void showUserDashboard(PublicUser& loggedInUser);
void showPricePlans();
void showEditProfile(PublicUser& loggedInUser);



#endif