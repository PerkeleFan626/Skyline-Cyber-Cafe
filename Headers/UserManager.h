#pragma once

#include "DataManager.h"

class UserManager {
private:
    DataManager& dbManager;

public:
    UserManager(DataManager& manager);

    bool find_user_by_id(int searchId, PublicUser& foundUser);
    bool find_user_by_name(const string& searchName, PublicUser& foundUser);
    void print_all_users();
};