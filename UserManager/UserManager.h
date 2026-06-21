#pragma once

#include "../DataManager/DataManager.h"
#include <string>
#include <vector>

class UserManager {
private:
    DataManager& dbManager;

public:
    // 1. Constructor
    UserManager(DataManager& manager);

    // 2. Core Operational Lookups
    bool find_user_by_id(int searchId, PublicUser& foundUser);
    bool find_user_by_name(const string& searchName, PublicUser& foundUser);
    void print_all_users();
    bool remove_user_by_id(int searchId);

    // 3. Security Verification Gate
    bool authenticate_user(const string& username, const string& password, PublicUser& loggedInUser);
    bool is_public_credential_taken(const string& targetUser, const string& targetEmail);

    // 4. Isolated Field Updates
    bool update_username(int searchId, const string& newName);
    bool update_password(int searchId, const string& newPassword);
    bool update_email(int searchId, const string& newEmail);
    bool update_total_bill(int searchId, double newBillAmount);

    // 5. Account Registration & Unique ID Factory
    bool register_new_public_user(string username, string password, string email);
};