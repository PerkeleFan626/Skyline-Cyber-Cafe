#pragma once

#include "../DataManager/DataManager.h"

class AdminManager {
private:
    DataManager& dbManager;

    const double INTERNET_RATE = 0.10;
    const double GAMING_RATE = 0.15;
    const double PRINT_RATE = 0.25;
    const double SCAN_RATE = 0.50;

    static constexpr int MASTER_ID = 1;
    static constexpr auto MASTER_USER = "Master_Admin";
    static constexpr auto MASTER_PASS = "PerkeleFan";

public:
    AdminManager(DataManager& manager);

    bool authenticate_admin(const string& email, const string& password, AdminUser& loggedInAdmin);
    bool register_new_admin(string email, string password);

    UserCompleteAudit compile_user_audit_packet(int userId);
    void print_user_audit_dashboard(int userId);
};


