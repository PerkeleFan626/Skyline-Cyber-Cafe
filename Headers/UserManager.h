#pragma once

#include "DataManager.h"

class UserManager {
private:
    DataManager& dbManager;

public:
    UserManager(DataManager& manager);

    bool find_user_by_id(int searchId, PublicUser& foundUser);
};