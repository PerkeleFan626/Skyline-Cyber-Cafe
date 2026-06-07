#include "TransactionManager.h"
#include <iostream>

TransactionManager::TransactionManager(DataManager& manager) : dbManager(manager) {}

bool TransactionManager::process_session_checkout(int userId, int internetMin, int gamingMin, int printsCount, int scansCount) {

    double internetCost = internetMin * INTERNET_RATE;
    double gamingCost = gamingMin * GAMING_RATE;
    double printsCost = printsCount * PRINT_RATE;
    double scansCost = scansCount * SCAN_RATE;
    double calculatedTotal = internetCost + gamingCost + printsCost + scansCost;

    TransactionRecord receipt;
    receipt.userId = userId;
    receipt.internetPaid = internetCost;
    receipt.gamingPaid = gamingCost;
    receipt.printsPaid = printsCost;
    receipt.scansPaid = scansCost;
    receipt.totalPaid = calculatedTotal;

    if (dbManager.add_transaction_history(receipt)) {
        vector<PublicUser> allUsers =dbManager.get_all_public_users();
        for (auto& user : allUsers) {
            if (user.uniqueId == userId) {
                user.totalBill += calculatedTotal;
                break;
            }
        }
    dbManager.rewrite_public_users(allUsers);
        return true;
    }
    return false;
}
