#pragma once

#include "../DataManager/DataManager.h"

using namespace std;

class TransactionManager {
private:
    DataManager& dbManager;

    const double INTERNET_RATE = 0.10;
    const double GAMING_RATE = 0.15;
    const double PRINT_RATE = 0.25;
    const double SCAN_RATE = 0.50;

public:
    TransactionManager(DataManager& manager);
    bool process_session_checkout(int userId, int internetMin, int gamingMin, int printsCount, int scansCount);

};