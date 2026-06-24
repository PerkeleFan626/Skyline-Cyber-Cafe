#include "AdminManager.h"
#include <iostream>
#include <sstream>
#include <random>
#include <algorithm>
#include <iomanip>



using namespace std;

// ============================================================================
// 1. CONSTRUCTOR
// ============================================================================

AdminManager::AdminManager(DataManager& manager) : dbManager(manager) {
    vector<AdminUser> allAdmins = dbManager.get_all_admins();
    bool masterExist = false;

    for (const auto& admin : allAdmins) {
        if (admin.adminId == MASTER_ID) {
            masterExist = true;
            break;
        }
    }

    if (!masterExist) {
        AdminUser masterAdmin;
        masterAdmin.adminId = MASTER_ID;
        masterAdmin.userName = MASTER_USER;
        masterAdmin.password = MASTER_PASS;

        dbManager.add_admin(masterAdmin);
        cout << "System Security Notice: Master Admin missing. Automatically restored ID 1 to database.\n";
    }
}


// ============================================================================
// 2. ADMIN AUTHENTICATION VALIDATOR
// ============================================================================

bool AdminManager::authenticate_admin(const string& userName, const string& password, AdminUser& loggedInAdmin) {
    vector<AdminUser> allAdmins = dbManager.get_all_admins();

    for (const auto& admin : allAdmins) {
        if (admin.userName == userName && admin.password == password) {
            loggedInAdmin = admin;
            return true;
        }
    }
    cout << "Access Denied: Invalid Login pls try again.\n";
    return false;
}

// ============================================================================
// 3. REGISTRATION ENGINE WITH COLLISION SAFETY CHECK
// ============================================================================

bool AdminManager::register_new_admin(const AdminUser& currentAdmin, string newUsername, string newPassword) {
    if (currentAdmin.adminId != 1) {
        cout << "Access Denied: Only the Master Admin has permission to register new managers.\n";
        return false;
    }


    vector<AdminUser> existingAdmins = dbManager.get_all_admins();

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(1, 1000);

    int selectedId = 0;

    while (true) {
        selectedId = distr(gen);

        auto it = find_if(existingAdmins.begin(), existingAdmins.end(), [selectedId](const AdminUser& admin) {
            return admin.adminId == selectedId;
        });

        if (it == existingAdmins.end()) {
            break;
        }
    }

    AdminUser newAdmin;
    newAdmin.adminId = selectedId;
    newAdmin.userName = newUsername;
    newAdmin.password = newPassword;

    return dbManager.add_admin(newAdmin);

}

// ============================================================================
// 4. ADMIN DUPLICATE VALIDATION ENGINE
// ============================================================================

bool AdminManager::is_admin_credential_taken(const string& targetUser) {

    vector<AdminUser> allAdmins = dbManager.get_all_admins();

    for (const auto& admin : allAdmins) {
        if (admin.userName == targetUser) {
            cout << "Registration Failed: The username '" << targetUser << "' is already in use.\n";
            return true;
        }
    }
    return false;
}


// ============================================================================
// 5. ADMINISTRATIVE MANAGER DELETION ACTION
// ============================================================================
bool AdminManager::execute_admin_deletion(const AdminUser& currentAdmin, int targetAdminId) {

    if (currentAdmin.adminId != 1) {
        cout << "Access Denied: Only the Master Admin has permission to remove managers.\n";
        return false;
    }

    if (targetAdminId == 1) {
        cout << "Security Violation: The Master Admin account cannot be removed from the system.\n";
        return false;
    }

    if (dbManager.remove_admin(targetAdminId)) {
        cout << "Success: Admin ID [" << targetAdminId << "] has been permanently removed.\n";
        return true;
    }

    cout << "Error: Could not process deletion request.\n";
    return false;
}

// ============================================================================
// 6. AUDIT DATA HARVESTER CORE ENGINE
// ============================================================================

UserCompleteAudit AdminManager::compile_user_audit_packet(int userId) {
    UserCompleteAudit auditPacket;

    vector<PublicUser> allUsers = dbManager.get_all_public_users();
    for (const auto& user : allUsers) {
        if (user.uniqueId == userId) {
            auditPacket.profile = user;
            break;
        }
    }

    vector<UserSession> allSessions = dbManager.get_all_sessions();
    for (const auto& session : allSessions) {
        if (session.userId == userId) {
            auditPacket.activeSession = session;
            auditPacket.hasActiveSession = true;
            break;
        }
    }

    ifstream f(filePath::DATA_DIR + filePath::HISTORY_FILE);
    if (f.is_open()) {
        string line;
        getline(f, line);

        while (getline(f, line)) {
            stringstream ss(line);
            string token;
            vector<string> tokens;
            while (getline(ss, token, ',')) {
                tokens.push_back(token);
            }

            if (!tokens.empty() && stoi(tokens[0]) == userId) {
                TransactionRecord record;
                record.userId = userId;
                record.internetPaid = stod(tokens[1]);
                record.gamingPaid = stod(tokens[2]);
                record.printsPaid = stod(tokens[3]);
                record.scansPaid = stod(tokens[4]);
                record.totalPaid = stod(tokens[5]);

                auditPacket.paymentHistory.push_back(record);
            }
        }
        f.close();
    }

    return auditPacket;
}

// ============================================================================
// 7. BUSINESS INTEL MONITOR VISUAL INTERFACE
// ============================================================================

void AdminManager::print_user_audit_dashboard(int userId) {
    UserCompleteAudit audit = compile_user_audit_packet(userId);

    if (audit.profile.uniqueId == 0) {
        cout << "Administrative Lookup Aborted: User ID [" << userId << "] does not exist in records.\n";
        return;
    }

    cout << fixed << setprecision(2);
    cout << "\n========================================================\n";
    cout << "          ADMINISTRATIVE CUSTOMER AUDIT DOSSIER         \n";
    cout << "========================================================\n";


    cout << " [A] CUSTOMER PROFILE DETAILS:\n";
    cout << "- User ID:          " << audit.profile.uniqueId << "\n";
    cout << "- Account Username: " << audit.profile.userName << "\n";
    cout << "- Contact Email:    " << audit.profile.email << "\n";
    cout << "- Historical Bill:  $" << audit.profile.totalBill << " (Lifetime Accumulated)\n";
    cout << "--------------------------------------------------------\n";


    cout << " [B] LIVE UNPAID STATE TERMINAL LOGS:\n";
    if (!audit.hasActiveSession) {
        cout << "Status: OFFLINE (No active terminal session running currently).\n";
    } else {
        double pendingInternet = audit.activeSession.internetMinutes * INTERNET_RATE;
        double pendingGaming = audit.activeSession.gamingMinutes * GAMING_RATE;
        double pendingPrints = audit.activeSession.printsCount * PRINT_RATE;
        double pendingScans = audit.activeSession.scansCount * SCAN_RATE;
        double pendingTotal = pendingInternet + pendingGaming + pendingPrints + pendingScans;

        cout << "Status: ONLINE (Actively occupied terminal context)\n";
        cout << "- Internet Tracking: " << audit.activeSession.internetMinutes << " mins  --> Pending Charge: $" << pendingInternet << "\n";
        cout << "- Gaming Tracking: " << audit.activeSession.gamingMinutes << " mins  --> Pending Charge: $" << pendingGaming << "\n";
        cout << "- Printer Tally: " << audit.activeSession.printsCount << " pages --> Pending Charge: $" << pendingPrints << "\n";
        cout << "- Scanner Tally: " << audit.activeSession.scansCount << " docs  --> Pending Charge: $" << pendingScans << "\n";
        cout << ">> PROJECTED SESSION TOTAL DUE UPON CHECKOUT: $" << pendingTotal << "\n";
    }
    cout << "--------------------------------------------------------\n";


    cout << " [C] SETTLED HISTORICAL AUDIT TRAIL:\n";
    if (audit.paymentHistory.empty()) {
        cout << "- No historical transaction records found for this account line.\n";
    } else {
        cout << " Found (" << audit.paymentHistory.size() << ") completed session invoices associated with this ID:\n\n";
        int transactionCounter = 1;

        for (const auto& receipt : audit.paymentHistory) {
            cout << "Receipt #" << transactionCounter++ << " Breakdown:\n";
            cout << " - Internet Settled: $" << receipt.internetPaid << "\n";
            cout << " - Gaming Settled:   $" << receipt.gamingPaid << "\n";
            cout << " - Printing Settled: $" << receipt.printsPaid << "\n";
            cout << " - Scanning Settled: $" << receipt.scansPaid << "\n";
            cout << " >> NET TRANSACTION VOLUME PAID: $" << receipt.totalPaid << "\n";
            cout << "- - - - - - - - - - - - - - - - - - - - - - - - - -\n";
        }
    }
    cout << "========================================================\n\n";
}