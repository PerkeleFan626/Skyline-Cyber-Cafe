#pragma once

#include "../DataManager/DataManager.h"
#include "../UserManager/UserManager.h"
#include "../AdminManager/AdminManager.h"

DataManager dataStorage;
UserManager userControl(dataStorage);
PublicUser matchingUser;
AdminManager adminControl(dataStorage);
