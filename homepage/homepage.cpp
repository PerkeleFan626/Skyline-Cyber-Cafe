#include <iostream>
#include <cstdlib>
#include <string>
#include <thread> // Used for timing the animation
#include <chrono> // Used for milliseconds definitions
#include "homepage.hpp"
#include "../UserManager/UserManager.h"
#include "../Globals/Globals.h"
#include "../AdminManager/AdminManager.h"
DataManager dbManager;
UserManager userControl(dbManager);
AdminManager adminControl(dbManager);

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
            showUserDashboard(loggedInUser);
            return;
        }         else {
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
    std::cout << "         SKYLINE CYBER CAFE - ADMIN LOGIN\n";
    std::cout << "==========================================================================\033[0m\n\n";
    std::cout << "  (Type 'exit' at any time to cancel)\n\n";

    std::string email;
    std::string password;
    AdminUser loggedInAdmin;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        std::cout << "  Enter admin email    : ";
        std::getline(std::cin, email);
        if (email == "exit") return;

        std::cout << "  Enter admin password : ";
        std::getline(std::cin, password);
        if (password == "exit") return;

        bool success = adminControl.authenticate_admin(email, password, loggedInAdmin);

        if (success) {
            std::cout << "\n  Welcome, Admin! ID: " << loggedInAdmin.adminId <<"\n  Press enter to continue to the dashboard "<< "\n";
            std::cin.get();
            showAdminDashboard(loggedInAdmin);
            return;
        } else {
            std::cout << "  Type 'back' to return or press Enter to try again: ";
            std::string retry;
            std::getline(std::cin, retry);
            if (retry == "back") return;
        }
    }
}
void showAdminDashboard(AdminUser& loggedInAdmin) {
    while (true) {
        clearScreen();
        std::cout << "\033[31m==========================================================================\n";
        std::cout << "         SKYLINE CYBER CAFE - ADMIN DASHBOARD\n";
        std::cout << "         Welcome, Admin ID: " << loggedInAdmin.adminId << "\n";
        std::cout << "==========================================================================\033[0m\n\n";

        std::cout << "  \033[31m[1]\033[0m View All Users\n";
        std::cout << "  \033[31m[2]\033[0m Edit a User\n";
        std::cout << "  \033[31m[3]\033[0m Delete a User\n";
        std::cout << "  \033[31m[4]\033[0m View All Usernames\n";
        std::cout << "  \033[31m[5]\033[0m Total Time All Users\n";
        std::cout << "  \033[31m[6]\033[0m Total Prints & Scans Value\n";
        std::cout << "  \033[31m[7]\033[0m View User Sessions\n";
        std::cout << "  \033[31m[0]\033[0m Logout\n\n";

        std::cout << "\033[31m==========================================================================\033[0m\n\n";

        int choice;
        std::cout << "  Choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                userControl.print_all_users();
                std::cin.ignore(1000, '\n');
                std::cin.get();
                break;
            case 2: {
                clearScreen();
                std::cout << "\033[31m==========================================================================\n";
                std::cout << "         EDIT A USER\n";
                std::cout << "==========================================================================\033[0m\n\n";

                userControl.print_all_users();

                std::cout << "\n  Enter User ID to edit: ";
                int editId;
                std::cin >> editId;
                std::cin.ignore(1000, '\n');

                std::cout << "\n  What do you want to edit?\n";
                std::cout << "  [1] Username\n";
                std::cout << "  [2] Email\n";
                std::cout << "  [3] Password\n";
                std::cout << "\n  Choice: ";
                int editChoice;
                std::cin >> editChoice;
                std::cin.ignore(1000, '\n');

                std::string newValue;

                if (editChoice == 1) {
                    std::cout << "  New username: ";
                    std::getline(std::cin, newValue);
                    userControl.update_username(editId, newValue);
                    std::cout << "\n  Username updated!\n";
                } else if (editChoice == 2) {
                    std::cout << "  New email: ";
                    std::getline(std::cin, newValue);
                    userControl.update_email(editId, newValue);
                    std::cout << "\n  Email updated!\n";
                } else if (editChoice == 3) {
                    std::cout << "  New password: ";
                    std::getline(std::cin, newValue);
                    userControl.update_password(editId, newValue);
                    std::cout << "\n  Password updated!\n";
                } else {
                    std::cout << "\n  Invalid choice.\n";
                }

                std::cin.ignore(1000, '\n');
                std::cin.get();
                break;
            }

            case 3: {
                clearScreen();
                std::cout << "\033[31m==========================================================================\n";
                std::cout << "         DELETE A USER\n";
                std::cout << "==========================================================================\033[0m\n\n";

                userControl.print_all_users();

                std::cout << "\n  Enter User ID to delete: ";
                int deleteId;
                std::cin >> deleteId;

                bool deleted = userControl.remove_user_by_id(deleteId);

                if (deleted) {
                    std::cout << "\n  User deleted successfully!\n";
                } else {
                    std::cout << "\n  User not found.\n";
                }

                std::cin.ignore(1000, '\n');
                std::cin.get();
                break;
            }
            case 4: {
                clearScreen();
                std::cout << "\033[31m==========================================================================\n";
                std::cout << "         ALL USERNAMES\n";
                std::cout << "==========================================================================\033[0m\n\n";

                vector<PublicUser> allUsers = dbManager.get_all_public_users();

                if (allUsers.empty()) {
                    std::cout << "  No users registered yet.\n";
                } else {
                    for (const auto& user : allUsers) {
                        std::cout << "  [" << user.uniqueId << "] " << user.userName << "\n";
                    }
                }

                std::cin.ignore(1000, '\n');
                std::cin.get();
                break;
            }
            case 5: {
                clearScreen();
                std::cout << "\033[31m==========================================================================\n";
                std::cout << "         TOTAL TIME ALL USERS\n";
                std::cout << "==========================================================================\033[0m\n\n";

                vector<UserSession> allSessions = dbManager.get_all_sessions();
                int totalInternet = 0;
                int totalGaming = 0;

                for (const auto& session : allSessions) {
                    totalInternet += session.internetMinutes;
                    totalGaming += session.gamingMinutes;
                }

                std::cout << "  Total Internet Time : " << totalInternet << " minutes\n";
                std::cout << "  Total Gaming Time   : " << totalGaming << " minutes\n";
                std::cout << "  Total Combined      : " << totalInternet + totalGaming << " minutes\n";

                std::cin.ignore(1000, '\n');
                std::cin.get();
                break;
            }

            case 6: {
                clearScreen();
                std::cout << "\033[31m==========================================================================\n";
                std::cout << "         TOTAL PRINTS & SCANS VALUE\n";
                std::cout << "==========================================================================\033[0m\n\n";

                vector<UserSession> allSessions = dbManager.get_all_sessions();
                int totalPrints = 0;
                int totalScans = 0;

                for (const auto& session : allSessions) {
                    totalPrints += session.printsCount;
                    totalScans += session.scansCount;
                }

                double printValue = totalPrints * 0.20;
                double scanValue = totalScans * 0.50;

                std::cout << "  Total Pages Printed : " << totalPrints << " ($" << printValue << ")\n";
                std::cout << "  Total Pages Scanned : " << totalScans << " ($" << scanValue << ")\n";
                std::cout << "  Total Value         : $" << printValue + scanValue << "\n";

                std::cin.ignore(1000, '\n');
                std::cin.get();
                break;
            }


            case 7: {
                clearScreen();
                std::cout << "\033[31m==========================================================================\n";
                std::cout << "         USER SESSIONS\n";
                std::cout << "==========================================================================\033[0m\n\n";

                vector<UserSession> allSessions = dbManager.get_all_sessions();

                if (allSessions.empty()) {
                    std::cout << "  No active sessions found.\n";
                } else {
                    for (const auto& session : allSessions) {
                        std::cout << "  User ID        : " << session.userId << "\n";
                        std::cout << "  Internet Time  : " << session.internetMinutes << " minutes\n";
                        std::cout << "  Gaming Time    : " << session.gamingMinutes << " minutes\n";
                        std::cout << "  Prints         : " << session.printsCount << "\n";
                        std::cout << "  Scans          : " << session.scansCount << "\n";
                        std::cout << "  ------------------------------------------\n";
                    }
                }

                std::cin.ignore(1000, '\n');
                std::cin.get();
                break;
            }
            case 0:
                std::cout << "\n  Logging out of admin panel...\n";
                return;
            default:
                std::cout << "\n  Invalid option.\n";
                std::cin.ignore(1000, '\n');
                std::cin.get();
                break;
        }
    }
}
void showUserDashboard(PublicUser& loggedInUser) {
    while (true) {
        clearScreen();
        std::cout << "\033[36m==========================================================================\n";
        std::cout << "         SKYLINE CYBER CAFE - USER DASHBOARD\n";
        std::cout << "         Welcome, " << loggedInUser.userName << "!\n";
        std::cout << "==========================================================================\033[0m\n\n";

        std::cout << "  \033[36m[1]\033[0m Start Session\n";
        std::cout << "  \033[36m[2]\033[0m View My Sessions\n";
        std::cout << "  \033[36m[3]\033[0m View My Bill\n";
        std::cout << "  \033[36m[4]\033[0m View Price Plans\n";
        std::cout << "  \033[36m[5]\033[0m Edit My Profile\n";
        std::cout << "  \033[36m[0]\033[0m Logout\n\n";

        std::cout << "\033[36m==========================================================================\033[0m\n\n";

        int choice;
        std::cout << "  Choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "\n  [Coming soon - Start Session]\n";
                std::cin.ignore(1000, '\n');
                std::cin.get();
                break;
            case 2:
                std::cout << "\n  [Coming soon - View My Sessions]\n";
                std::cin.ignore(1000, '\n');
                std::cin.get();
                break;
            case 3:
                std::cout << "\n  [Coming soon - View My Bill]\n";
                std::cin.ignore(1000, '\n');
                std::cin.get();
                break;

            case 4:
                showPricePlans();
                break;
            case 5:
                showEditProfile(loggedInUser);
                break;

            case 0:
                std::cout << "\n  Goodbye, " << loggedInUser.userName << "! See you soon.\n";
                std::cin.ignore(1000, '\n');
                std::cin.get();
                return;
            default:
                std::cout << "\n  Invalid option.\n";
                std::cin.ignore(1000, '\n');
                std::cin.get();
                break;
        }
    }
}

void showPricePlans() {
    clearScreen();
    std::cout << "\033[36m==========================================================================\n";
    std::cout << "         SKYLINE CYBER CAFE - PRICE PLANS\n";
    std::cout << "==========================================================================\033[0m\n\n";

    std::cout << "  BROWSING\n";
    std::cout << "  --------\n";
    std::cout << "  $3.00 per hour\n\n";

    std::cout << "  PRINTING\n";
    std::cout << "  --------\n";
    std::cout << "  $0.20 per page\n\n";

    std::cout << "  SCANNING\n";
    std::cout << "  --------\n";
    std::cout << "  $0.50 per page\n\n";

    std::cout << "\033[36m==========================================================================\033[0m\n";
    std::cout << "\n  Press Enter to return...";
    std::cin.ignore(1000, '\n');
    std::cin.get();
}

void showEditProfile(PublicUser& loggedInUser) {
    clearScreen();
    std::cout << "\033[36m==========================================================================\n";
    std::cout << "         SKYLINE CYBER CAFE - EDIT PROFILE\n";
    std::cout << "==========================================================================\033[0m\n\n";
    std::cout << "  (Type 'exit' to cancel)\n\n";

    std::cout << "  Current username : " << loggedInUser.userName << "\n";
    std::cout << "  Current email    : " << loggedInUser.email << "\n\n";

    std::string newName;
    std::string newEmail;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "  New username (Enter to keep current): ";
    std::getline(std::cin, newName);
    if (newName == "exit") return;

    std::cout << "  New email (Enter to keep current): ";
    std::getline(std::cin, newEmail);
    if (newEmail == "exit") return;

    if (!newName.empty()) {
        userControl.update_username(loggedInUser.uniqueId, newName);
        loggedInUser.userName = newName;
    }
    if (!newEmail.empty()) {
        if (newEmail.find('@') == std::string::npos || newEmail.find('.') == std::string::npos) {
            std::cout << "\n  Invalid email address!\n";
        } else {
            userControl.update_email(loggedInUser.uniqueId, newEmail);
            loggedInUser.email = newEmail;
        }
    }

    std::cout << "\n  Profile updated successfully!\n";
    std::cout << "\n  Press Enter to return...";
    std::cin.get();
}
