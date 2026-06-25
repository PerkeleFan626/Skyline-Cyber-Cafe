#include "TransactionManager.h"
#include <iostream>
#include <iomanip>

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

        cout << fixed << setprecision(2);
        cout << "\n\033[33m========================================================\n";
        cout << "             SKYLINE CYBER CAFE - OFFICIAL RECEIPT      \n";
        cout << "========================================================\033[0m\n";
        cout << "  - Customer User ID  : #" << userId << "\n";
        cout << "  ------------------------------------------------------\n";
        cout << "  [+] ITEMIZED LINE-ITEM USAGE CHARGES:\n";
        cout << "    - Internet Access (" << internetMin << " mins) : $" << internetCost << "\n";
        cout << "    - Gaming Station  (" << gamingMin << " mins) : $" << gamingCost << "\n";
        cout << "    - Printer Access  (" << printsCount << " pages): $" << printsCost << "\n";
        cout << "    - Scanner Access  (" << scansCount << " docs) : $" << scansCost << "\n";
        cout << "  ------------------------------------------------------\n";
        cout << "   \033[1;32mTOTAL AMOUNT SETTLED & PAID : $" << calculatedTotal << "\033[0m\n";
        cout << "\033[33m========================================================\033[0m\n";
        cout << "       Thank you for visiting! Session terminated safely.\n\n";


        return true;
    }
    return false;
}
