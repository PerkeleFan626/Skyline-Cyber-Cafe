#include "UserManager.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

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

    cout << "Error: User with ID" << searchId << " could not be found. Enter another user ID \n";
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

bool UserManager::authenticate_user(const string& username, const string& password, PublicUser& loggedInUser) {
    vector<PublicUser> allUser = dbManager.get_all_public_users();

    for (const auto& user : allUser) {
        if (user.userName == username && user.password == password) {
            loggedInUser = user;
            return true;
        }

    }
    cout << "Invalid Login: Please try again \n";
    return false;
}

bool UserManager::update_username(int searchId, const string& newName) {
    vector<PublicUser> allUser = dbManager.get_all_public_users();
    for (size_t i=0; i < allUser.size(); i++) {
        if (allUser[i].uniqueId == searchId) {
            allUser[i].userName = newName;
            return dbManager.rewrite_public_users(allUser);
        }
    }
    cout << "Error: Couldent find " << searchId << " ID\n";
    return false;
}

bool UserManager::update_password(int searchId, const string& newPassword) {
    vector<PublicUser> allUser = dbManager.get_all_public_users();
    for (size_t i=0; i < allUser.size(); i++) {
        if (allUser[i].uniqueId == searchId) {
            allUser[i].password = newPassword;
            return dbManager.rewrite_public_users(allUser);
        }
    }
    cout << "Error: Couldent find " << searchId << " ID\n";
    return false;
}

bool UserManager::update_email(int searchId, const string& newEmail) {
    vector<PublicUser> allUser = dbManager.get_all_public_users();
    for (size_t i=0; i < allUser.size(); i++) {
        if (allUser[i].uniqueId == searchId) {
            allUser[i].email = newEmail;
            return dbManager.rewrite_public_users(allUser);
        }
    }
    cout << "Error: Couldent find " << searchId << " ID\n";
    return false;
}

bool UserManager::update_total_bill(int searchId, double newBillAmount) {
    vector<PublicUser> allUser = dbManager.get_all_public_users();
    for (size_t i=0; i < allUser.size(); i++) {
        if (allUser[i].uniqueId == searchId) {
            allUser[i].totalBill = newBillAmount;
            return dbManager.rewrite_public_users(allUser);
        }
    }
    cout << "Error: Couldent find " << searchId << " ID\n";
    return false;
}

// ============================================================================
// ACCOUNT REGISTRATION & UNIQUE ID GENERATION & Automatic - Date detection
// ============================================================================

bool UserManager::register_new_public_user(string username, string password, string email) {
    vector<PublicUser> allUsers = dbManager.get_all_public_users();

    int nextId = 1001;

    if (!allUsers.empty()) {
        nextId = allUsers.back().uniqueId + 1;
    }

    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);

    tm* localTime = localtime(&currentTime);

    stringstream dateStream;
    dateStream << put_time(localTime, "%d-%m-%Y");
    string autoCalculatedDate = dateStream.str();


    PublicUser newUser;
    newUser.uniqueId = nextId;
    newUser.userName = username;
    newUser.password = password;
    newUser.email = email;
    newUser.joiningDate = autoCalculatedDate;
    newUser.totalBill = 0.0;

    return dbManager.add_public_user(newUser);
}