#include "UserManager.h"
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

bool UserManager::remove_user_by_id(int searchId) {
    vector<PublicUser> allUsers = dbManager.get_all_public_users();
    bool found = false;

    for (size_t i=0; i < allUsers.size(); i++) {
        if (allUsers[i].uniqueId == searchId) {
            allUsers.erase(allUsers.begin() + i);
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "cannot delete user ID " << searchId << ". Record does not exist\n";
        return false;
    }

    return dbManager.rewrite_public_users(allUsers);
}