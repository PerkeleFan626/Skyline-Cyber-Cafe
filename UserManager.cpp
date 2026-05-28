#include "Headers/UserManager.h"
#include <iostream>

using namespace std;

// ============================================================================
// 1. CONSTRUCTOR & INITIALIZATION
// ============================================================================

UserManager::UserManager(DataManager& manager) : dbManager(manager){}

// ============================================================================
// 2. PUBLIC USER OPERATIONS (CRUD & LOOKUPS)
// ============================================================================

bool UserManager::find_user_by_id(int searchId, PublicUser& foundUser) {

    vector<PublicUser> allUsers = dbManager.get_all_public_users();

    for (const auto& user : allUsers) {

        if (user.uniqueId == searchId) {
            foundUser = user;
            return true;
        }

    }

    cout << "Error: User with ID" << searchId << " " << "could not be found. Enter another user ID \n";
    return false;
}

bool UserManager::find_user_by_name(const string& searchName, PublicUser& foundUser) {
    vector<PublicUser> allUsers = dbManager.get_all_public_users();

    for (const auto& user : allUsers) {
        if (user.userName == searchName) {
            foundUser = user;
            return true;
        }
    }

    cout << "Error: User with username " << searchName << " could not be found.\n";
    return false;
}

void UserManager::print_all_users() {
    vector<PublicUser> allUsers = dbManager.get_all_public_users();

    if (allUsers.empty()) {
        cout << "Database error: Found no users" << endl;
        return;
    }

    for (const auto& user : allUsers) {
        cout << user.uniqueId << " | "
             << user.userName << " | "
             << user.password << " | "
             << user.email << " | "
             << user.joiningDate << " | NZD "
             << user.totalBill << endl;
    }
}
