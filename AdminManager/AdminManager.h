#pragma once

#include "../DataManager/DataManager.h"

class AdminManager {
private:
    DataManager& dbManager;

public:
    AdminManager(DataManager& manager);

    bool authenticate_admin(const string& email, const string& password, AdminUser& loggedInAdmin);
    bool register_new_admin(string email, string password);
};