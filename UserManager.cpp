#include "Headers/UserManager.h"
#include <iostream>

using namespace std;

UserManager::UserManager(DataManager& manager) : dbManager(manager){}

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