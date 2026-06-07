#pragma once

#include "../DataManager/DataManager.h"
#include "../TransactionManager/TransactionManager.h"

class SessionManager {
private:
    DataManager& dbManager;
    TransactionManager& transManager;

public:
    SessionManager(DataManager& dataMgr, TransactionManager& transMgr);

    bool start_new_session(int userId);
    bool simulate_activity(int userId, int addInternet, int addGaming, int addPrints, int addScans);
    bool end_and_checkout_session(int userId);

};