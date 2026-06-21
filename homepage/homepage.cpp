#include <iostream>
#include <cstdlib>
#include <string>
#include <thread>
#include <chrono>
#include "homepage.hpp"
#include "../UserManager/UserManager.h"
#include "../Globals/Globals.h"
#include "../AdminManager/AdminManager.h"
#include "../TransactionManager/TransactionManager.h"
#include "../SessionManager/SessionManager.h"
DataManager dbManager;
UserManager userControl(dbManager);
AdminManager adminControl(dbManager);
TransactionManager transManager(dbManager);
SessionManager sessionManager(dbManager, transManager);


const int CONSOLE_WIDTH = 80;

// ANSI Color Escape Codes
const std::string RESET   = "\033[0m";
const std::string TEAL    = "\033[36m";
const std::string WHITE   = "\033[37m";
const std::string BOLD    = "\033[1m";
const std::string GRAY    = "\033[90m";


void clearScreen() {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}


void printCentered(const std::string& text, int width) {
    int padding = (width - text.length()) / 2;
    if (padding > 0) {
        for (int i = 0; i < padding; ++i) std::cout << " ";
    }
    std::cout << text << "\n";
}

void displayAnimatedHomepage() {
    clearScreen();


    std::cout << TEAL;
    printCentered("==========================================================================", CONSOLE_WIDTH);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));


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


    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    std::cout << WHITE << BOLD;
    printCentered("CYBER CAFE AUTOMATED BILLING SYSTEM", CONSOLE_WIDTH);
    std::cout << RESET;

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << GRAY;
    printCentered("Auckland CBD Branch", CONSOLE_WIDTH);
    std::cout << RESET << "\n";


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

// Sub-Page Navigation Screens
void showRegistrationScreen() {
    clearScreen();
    std::cout << "\033[36m==========================================================================\n";
    std::cout << "         SKYLINE CYBER CAFE - NEW USER REGISTRATION\n";
    std::cout << "==========================================================================\033[0m\n\n";
    std::cout << "  (Type 'exit' at any time to cancel)\n\n";

    std::string userName;
    std::string email;
    std::string password;

    while (true) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "  [1/3] Enter your name (e.g., John Smith): ";
        std::getline(std::cin, userName);
        if (userName == "exit") return;

        std::cout << "\n  [2/3] Enter your email (e.g., john@example.com): ";
        std::getline(std::cin, email);
        if (email == "exit") return;

        if (email.find('@') == std::string::npos || email.find('.') == std::string::npos) {
            std::cout << "\n  ✗ Invalid email address! Must contain @ and .\n";
            std::cout << "  Type 'back' to return to menu or press Enter twice to try again: ";
            std::string retry;
            std::getline(std::cin, retry);
            if (retry == "back") return;
            clearScreen();
            std::cout << "\033[36m==========================================================================\n";
            std::cout << "         SKYLINE CYBER CAFE - NEW USER REGISTRATION\n";
            std::cout << "==========================================================================\033[0m\n\n";
            continue;
        }

        std::cout << "\n  [3/3] Enter your password (e.g., MyPass123!)\n";
        std::cout << "        Requirements:\n";
        std::cout << "        • Minimum 8 characters\n";
        std::cout << "        • 1 uppercase letter (A-Z)\n";
        std::cout << "        • 1 lowercase letter (a-z)\n";
        std::cout << "        • 1 number (0-9)\n";
        std::cout << "        • 1 symbol (!@#$%...)\n";
        std::cout << "  Password: ";
        std::getline(std::cin, password);
        if (password == "exit") return;

        bool hasUpper = false, hasLower = false, hasDigit = false, hasSymbol = false;
        for (char c : password) {
            if (isupper(c)) hasUpper = true;
            if (islower(c)) hasLower = true;
            if (isdigit(c)) hasDigit = true;
            if (ispunct(c)) hasSymbol = true;
        }

        std::string errorMsg = "";
        if (password.length() < 8) {
            errorMsg = "  ✗ Password must be at least 8 characters! (You entered " + std::to_string(password.length()) + ")\n";
        } else if (!hasUpper) {
            errorMsg = "  ✗ Password must contain at least one UPPERCASE letter (A-Z)\n";
        } else if (!hasLower) {
            errorMsg = "  ✗ Password must contain at least one lowercase letter (a-z)\n";
        } else if (!hasDigit) {
            errorMsg = "  ✗ Password must contain at least one number (0-9)\n";
        } else if (!hasSymbol) {
            errorMsg = "  ✗ Password must contain at least one symbol (!@#$...)\n";
        }

        if (!errorMsg.empty()) {
            std::cout << "\n" << errorMsg;
            std::cout << "  Type 'back' to return to menu or press Enter to try again: ";
            std::string retry;
            std::getline(std::cin, retry);
            if (retry == "back") return;
            clearScreen();
            std::cout << "\033[36m==========================================================================\n";
            std::cout << "         SKYLINE CYBER CAFE - NEW USER REGISTRATION\n";
            std::cout << "==========================================================================\033[0m\n\n";
            continue;
        }


        bool success = userControl.register_new_public_user(userName, password, email);

        if (success) {
            std::cout << "\n  ✓ Account created successfully! Welcome, " << userName << "!\n";
            std::cout << "\n  Press Enter to return...";
            std::cin.get();
            return;
        } else {
            std::cout << "\n  ✗ Registration failed. Email may already be in use.\n";
            std::cout << "  Type 'back' to return to menu or press Enter to try again: ";
            std::string retry;
            std::getline(std::cin, retry);
            if (retry == "back") return;
            clearScreen();
            std::cout << "\033[36m==========================================================================\n";
            std::cout << "         SKYLINE CYBER CAFE - NEW USER REGISTRATION\n";
            std::cout << "==========================================================================\033[0m\n\n";
            continue;
        }
    }
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

    std::cout << "\033[31m==========================================================================\n";
    std::cout << "         SKYLINE CYBER CAFE - STAFF / ADMIN PORTAL\n";
    std::cout << "==========================================================================\033[0m\n\n";

    std::cout << "  \033[31m[1]\033[0m Master Admin Login\n";
    std::cout << "  \033[31m[2]\033[0m Regular Admin Login\n";
    std::cout << "  \033[31m[0]\033[0m Back to Main Menu\n\n";

    std::cout << "\033[31m==========================================================================\033[0m\n\n";

    int portalChoice;
    std::cout << "  Choice: ";
    if (!(std::cin >> portalChoice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }


    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (portalChoice == 0) return;
    if (portalChoice != 1 && portalChoice != 2) return;

    clearScreen();
    std::cout << "\033[31m==========================================================================\n";
    if (portalChoice == 1) {
        std::cout << "         MASTER ADMIN LOGIN\n";
    } else {
        std::cout << "         ADMIN LOGIN\n";
    }
    std::cout << "==========================================================================\033[0m\n\n";
    std::cout << "  (Type 'exit' at any time to cancel)\n\n";

    std::string adminUsername;
    std::string password;
    AdminUser loggedInAdmin;


    while (true) {
        std::cout << "  Enter admin username : ";
        std::getline(std::cin, adminUsername);
        if (adminUsername == "exit") return;

        std::cout << "  Enter admin password  : ";
        std::getline(std::cin, password);
        if (password == "exit") return;

        bool success = adminControl.authenticate_admin(adminUsername, password, loggedInAdmin);

        if (success) {
            std::cout << "\n  Welcome, Admin! ID: " << loggedInAdmin.adminId << "\n";

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

        std::cout << "  \033[36m[1]\033[0m View All Users\n";
        std::cout << "  \033[36m[2]\033[0m Edit a User\n";
        std::cout << "  \033[36m[3]\033[0m Delete a User\n";
        std::cout << "  \033[36m[4]\033[0m View All Usernames\n";
        std::cout << "  \033[36m[5]\033[0m Full User Audit\n";
        std::cout << "  \033[36m[6]\033[0m View Active Sessions\n";
        if (loggedInAdmin.adminId == 1) {
            std::cout << "  \033[36m[7]\033[0m Register New Admin\n";
            std::cout << "  \033[36m[8]\033[0m Delete an Admin\n";
        }
        std::cout << "  \033[36m[0]\033[0m Logout\n\n";

        std::cout << "\033[36m==========================================================================\033[0m\n\n";
        std::cout << std::flush;

        int choice;
        std::cout << "  Choice: ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }


        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                userControl.print_all_users();
                std::cout << "\n  Press Enter to return...";
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
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "\n  What do you want to edit?\n";
                std::cout << "  [1] Username\n";
                std::cout << "  [2] Email\n";
                std::cout << "  [3] Password\n";
                std::cout << "\n  Choice: ";
                int editChoice;
                std::cin >> editChoice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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

                std::cout << "\n  Press Enter to return...";
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
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                bool deleted = userControl.remove_user_by_id(deleteId);

                if (deleted) {
                    std::cout << "\n  User deleted successfully!\n";
                } else {
                    std::cout << "\n  User not found.\n";
                }

                std::cout << "\n  Press Enter to return...";
                std::cin.get();
                break;
            }

            case 4: {
                clearScreen();
                std::cout << "\033[31m==========================================================================\n";
                std::cout << "         ALL USERNAMES\n";
                std::cout << "==========================================================================\033[0m\n\n";

                std::vector<PublicUser> allUsers = dbManager.get_all_public_users();

                if (allUsers.empty()) {
                    std::cout << "  No users registered yet.\n";
                } else {
                    for (const auto& user : allUsers) {
                        std::cout << "  [" << user.uniqueId << "] " << user.userName << "\n";
                    }
                }

                std::cout << "\n  Press Enter to return...";
                std::cin.get();
                break;
            }

            case 5: {
                clearScreen();
                std::cout << "\033[31m==========================================================================\n";
                std::cout << "         FULL USER AUDIT\n";
                std::cout << "==========================================================================\033[0m\n\n";

                userControl.print_all_users();

                std::cout << "\n  Enter User ID to audit: ";
                int auditId;
                std::cin >> auditId;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                adminControl.print_user_audit_dashboard(auditId);

                std::cout << "\n  Press Enter to return...";
                std::cin.get();
                break;
            }

            case 6: {
                clearScreen();
                std::cout << "\033[31m==========================================================================\n";
                std::cout << "         USER SESSIONS\n";
                std::cout << "==========================================================================\033[0m\n\n";

                std::vector<UserSession> allSessions = dbManager.get_all_sessions();

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

                std::cout << "\n  Press Enter to return...";
                std::cin.get();
                break;
            }

            case 7: {
                if (loggedInAdmin.adminId != 1) {
                    std::cout << "\n  Access denied.\n";
                    std::cout << "\n  Press Enter to return...";
                    std::cin.get();
                    break;
                }

                clearScreen();
                std::cout << "\033[31m==========================================================================\n";
                std::cout << "         REGISTER NEW ADMIN\n";
                std::cout << "==========================================================================\033[0m\n\n";

                std::string newUsername, newPassword;

                std::cout << "  New admin username: ";
                std::getline(std::cin, newUsername);

                std::cout << "  New admin password: ";
                std::getline(std::cin, newPassword);

                bool success = adminControl.register_new_admin(loggedInAdmin, newUsername, newPassword);

                if (success) {
                    std::cout << "\n  New admin registered!\n";
                } else {
                    std::cout << "\n  Failed to register admin.\n";
                }

                std::cout << "\n  Press Enter to return...";
                std::cin.get();

                break;
            }

            case 8: {
                if (loggedInAdmin.adminId != 1) {
                    std::cout << "\n  Access denied.\n";
                    std::cin.ignore(1000, '\n');
                    std::cin.get();
                    break;
                }

                clearScreen();
                std::cout << "\033[31m==========================================================================\n";
                std::cout << "         DELETE AN ADMIN\n";
                std::cout << "==========================================================================\033[0m\n\n";

                vector<AdminUser> allAdmins = dbManager.get_all_admins();

                std::cout << "  Current Admins:\n";
                for (const auto& admin : allAdmins) {
                    if (admin.adminId != 1) {  // Don't allow deleting master admin
                        std::cout << "  [" << admin.adminId << "] " << admin.userName << "\n";
                    }
                }

                std::cout << "\n  Enter Admin ID to delete (or 0 to cancel): ";
                int adminIdToDelete;
                std::cin >> adminIdToDelete;

                if (adminIdToDelete == 0) {
                    std::cin.ignore(1000, '\n');
                    std::cin.get();
                    break;
                }


                if (adminIdToDelete == 1) {
                    std::cout << "\n  Cannot delete Master Admin!\n";
                    std::cin.ignore(1000, '\n');
                    std::cin.get();
                    break;
                }

                bool deleted = dbManager.remove_admin(adminIdToDelete);

                if (deleted) {
                    std::cout << "\n  Admin deleted successfully!\n";
                } else {
                    std::cout << "\n  Admin not found.\n";
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
                std::cout << "\n  Press Enter to return...";
                std::cin.get();
                break;
        }
    }
}void showUserDashboard(PublicUser& loggedInUser) {
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

            case 1: {
    clearScreen();
    std::cout << "\033[36m==========================================================================\n";
    std::cout << "         START SESSION\n";
    std::cout << "==========================================================================\033[0m\n\n";

    bool started = sessionManager.start_new_session(loggedInUser.uniqueId);

    if (started) {
        std::cout << "  Session started successfully!\n\n";

        while (true) {
            std::cout << "  \033[36m[1]\033[0m Add Internet Time (minutes)\n";
            std::cout << "  \033[36m[2]\033[0m Add Gaming Time (minutes)\n";
            std::cout << "  \033[36m[3]\033[0m Add Print Pages\n";
            std::cout << "  \033[36m[4]\033[0m Add Scan Pages\n";
            std::cout << "  \033[36m[0]\033[0m End Session & Checkout\n\n";
            std::cout << "  Choice: ";

            int sessionChoice;
            std::cin >> sessionChoice;

            if (sessionChoice == 0) {
                sessionManager.end_and_checkout_session(loggedInUser.uniqueId);
                std::cout << "\n  Session ended! Thank you.\n";
                std::cin.ignore(1000, '\n');
                std::cin.get();
                break;
            }

            int amount;
            std::cout << "  Enter amount: ";
            std::cin >> amount;

            if (sessionChoice == 1)
                sessionManager.simulate_activity(loggedInUser.uniqueId, amount, 0, 0, 0);
            else if (sessionChoice == 2)
                sessionManager.simulate_activity(loggedInUser.uniqueId, 0, amount, 0, 0);
            else if (sessionChoice == 3)
                sessionManager.simulate_activity(loggedInUser.uniqueId, 0, 0, amount, 0);
            else if (sessionChoice == 4)
                sessionManager.simulate_activity(loggedInUser.uniqueId, 0, 0, 0, amount);

            std::cout << "  Added!\n";
        }
    } else {
        std::cout << "  Failed to start session.\n";
        std::cin.ignore(1000, '\n');
        std::cin.get();
    }
    break;
}
            case 2: {
                clearScreen();
                std::cout << "\033[36m==========================================================================\n";
                std::cout << "         MY SESSIONS\n";
                std::cout << "==========================================================================\033[0m\n\n";

                vector<UserSession> allSessions = dbManager.get_all_sessions();
                bool found = false;

                for (const auto& session : allSessions) {
                    if (session.userId == loggedInUser.uniqueId) {
                        std::cout << "  Internet Time : " << session.internetMinutes << " mins\n";
                        std::cout << "  Gaming Time   : " << session.gamingMinutes << " mins\n";
                        std::cout << "  Prints        : " << session.printsCount << " pages\n";
                        std::cout << "  Scans         : " << session.scansCount << " pages\n";
                        std::cout << "  ------------------------------------------\n";
                        found = true;
                    }
                }

                if (!found) {
                    std::cout << "  No active sessions found.\n";
                }

                std::cin.ignore(1000, '\n');
                std::cin.get();
                break;
            }
            case 3: {
                clearScreen();
                std::cout << "\033[36m==========================================================================\n";
                std::cout << "         MY BILL HISTORY\n";
                std::cout << "==========================================================================\033[0m\n\n";

                std::cout << "  Total Lifetime Bill: $" << loggedInUser.totalBill << "\n\n";

                UserCompleteAudit audit = adminControl.compile_user_audit_packet(loggedInUser.uniqueId);

                if (audit.paymentHistory.empty()) {
                    std::cout << "  No completed transactions yet.\n";
                } else {
                    int counter = 1;
                    for (const auto& receipt : audit.paymentHistory) {
                        std::cout << "  Receipt #" << counter++ << "\n";
                        std::cout << "    Internet : $" << receipt.internetPaid << "\n";
                        std::cout << "    Gaming   : $" << receipt.gamingPaid << "\n";
                        std::cout << "    Printing : $" << receipt.printsPaid << "\n";
                        std::cout << "    Scanning : $" << receipt.scansPaid << "\n";
                        std::cout << "    TOTAL    : $" << receipt.totalPaid << "\n";
                        std::cout << "  ------------------------------------------\n";
                    }
                }

                std::cin.ignore(1000, '\n');
                std::cin.get();
                break;
            }

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

    std::cout << "  INTERNET BROWSING\n";
    std::cout << "  -----------------\n";
    std::cout << "  $0.10 per minute ($6.00 per hour)\n\n";

    std::cout << "  GAMING\n";
    std::cout << "  ------\n";
    std::cout << "  $0.15 per minute ($9.00 per hour)\n\n";

    std::cout << "  PRINTING\n";
    std::cout << "  --------\n";
    std::cout << "  $0.25 per page\n\n";

    std::cout << "  SCANNING\n";
    std::cout << "  --------\n";
    std::cout << "  $0.50 per page\n\n";
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

