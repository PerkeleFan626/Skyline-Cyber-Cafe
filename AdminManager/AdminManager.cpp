#include "AdminManager.h"
#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

AdminManager::AdminManager(DataManager& manager) : dbManager(manager) {}

// ============================================================================
// 1. ADMIN AUTHENTICATION VALIDATOR
// ============================================================================

bool AdminManager::authenticate_admin(const string& email, const string& password, AdminUser& loggedInAdmin) {
    vector<AdminUser> allAdmins = dbManager.get_all_admins();

    for (const auto& admin : allAdmins) {
        if (admin.email == email && admin.password == password) {
            loggedInAdmin = admin;
            return true;
        }
    }
    cout << "Access Denied: Invalid Login pls try again.\n";
    return false;
}

// ============================================================================
// 2. REGISTRATION ENGINE WITH COLLISION SAFETY CHECK
// ============================================================================

bool AdminManager::register_new_admin(string email, string password) {
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
    newAdmin.email = email;
    newAdmin.password = password;

    return dbManager.add_admin(newAdmin);

}
