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

    // ============================================================================
    // 1. ADMINISTRATIVE PRIVILEGE MANAGEMENT (WRITE & DELETE)
    // ============================================================================

    bool register_new_admin(const AdminUser& currentAdmin, string newUsername, string newPassword);
    bool execute_admin_deletion(const AdminUser& currentAdmin, int targetAdminId);

    // ============================================================================
    // 2. ADMINISTRATIVE SECURITY & IDENTITY ACCREDITATION
    // ============================================================================
    bool authenticate_admin(const string& username, const string& password, AdminUser& loggedInAdmin);
    bool is_admin_credential_taken(const string& targetUser);


    // ============================================================================
    // 3. BUSINESS INTEL MONITOR & AUDITING DOSSIER
    // ============================================================================
    UserCompleteAudit compile_user_audit_packet(int userId);
    void print_user_audit_dashboard(int userId);
};
