#pragma once

#include "../DataManager/DataManager.h"
#include "../UserManager/UserManager.h"
#include "../AdminManager/AdminManager.h"
#include "../TransactionManager/TransactionManager.h"
#include "../SessionManager/SessionManager.h"

DataManager dataStorage;
UserManager userControl(dataStorage);
PublicUser matchingUser;
AdminManager adminControl(dataStorage);
TransactionManager transactionControl(dataStorage);
SessionManager sessionControl(dataStorage, transactionControl);