#include <iostream>
#include <string>
#include "Globals/CallingClassGlobal.h"

using namespace std;

int main() {

cout << "==================================================\n";
    cout << "     CYBER CAFE CENTRAL SYSTEM VALIDATION\n";
    cout << "==================================================\n\n";

    // ====================================================
    // TEST 1: ADMIN REGISTRATION & AUTO-COLLISION GENERATION
    // ====================================================
    cout << "[TEST 1: ADMIN CREATION ENGINE]\n";
    cout << "Registering admin1@cafe.com...\n";
    adminControl.register_new_admin("admin1@cafe.com", "adminPass123");

    cout << "Registering admin2@cafe.com...\n";
    adminControl.register_new_admin("admin2@cafe.com", "secureAdmin777");
    cout << "👉 Check your admins.csv! Verify both got unique IDs between 1 and 1000.\n\n";

    // ====================================================
    // TEST 2: PUBLIC USER REGISTRATION & AUTO-SYSTEM DATE
    // ====================================================
    cout << "[TEST 2: PUBLIC USER ACCOUNT CREATION]\n";
    string pubName, pubPass, pubEmail;
    cout << "Enter a public account username to register: ";
    cin >> pubName;
    cout << "Enter account password: ";
    cin >> pubPass;
    cout << "Enter account email: ";
    cin >> pubEmail;

    if (userControl.register_new_public_user(pubName, pubPass, pubEmail)) {
        cout << "👉 Success: Public profile appended at ID 1001+ with live calendar date stamp.\n\n";
    } else {
        cout << "❌ Failure: Registration rejected.\n\n";
    }

    // ====================================================
    // TEST 3: COMPREHENSIVE SECURITY ROUTER (LOGIN GATE)
    // ====================================================
    cout << "[TEST 3: SYSTEM ROLE LOGIN VERIFICATION]\n";
    cout << "Choose Login Type (1 = Admin Portal, 2 = Public User Portal): ";
    int portalChoice;
    cin >> portalChoice;
    cin.ignore(); // Clears trailing newline buffer instantly

    if (portalChoice == 1) {
        // --- ADMIN LOGIN GATEWAY ---
        string admEmail, admPass;
        cout << "\n--- ADMIN LOGIN PORTAL ---\n";
        cout << "Enter Administrator Email: ";
        getline(cin, admEmail);
        cout << "Enter Administrator Password: ";
        getline(cin, admPass);

        AdminUser currentAdmin;
        if (adminControl.authenticate_admin(admEmail, admPass, currentAdmin)) {
            cout << "\n🟢 ACCESS GRANTED (ADMIN PANEL)\n";
            cout << "Identity Token Verified: [ID: " << currentAdmin.adminId << "]\n";
            cout << "System Status: Online & Secure\n\n";
        } else {
            cout << "\n🔴 ACCESS DENIED: Terminating portal link.\n\n";
        }

    } else if (portalChoice == 2) {
        // --- PUBLIC USER LOGIN GATEWAY ---
        string inputUser, inputPass;
        cout << "\n--- PUBLIC CLIENT PORTAL ---\n";
        cout << "Enter Client Username: ";
        getline(cin, inputUser);
        cout << "Enter Client Password: ";
        getline(cin, inputPass);

        PublicUser activeClient;
        if (userControl.authenticate_user(inputUser, inputPass, activeClient)) {
            cout << "\n🟢 ACCESS GRANTED (CLIENT TERMINAL)\n";
            cout << "Welcome Back, " << activeClient.userName << "\n";
            cout << "Account Email Link: " << activeClient.email << "\n";
            cout << "Account Created On: " << activeClient.joiningDate << "\n";
            cout << "Current Bill Owed: $" << activeClient.totalBill << "\n\n";
        } else {
            cout << "\n🔴 ACCESS DENIED: Invalid Client Match.\n\n";
        }

    } else {
        cout << "⚠️ Invalid choice. Exiting framework validation suite.\n";
    }

    // ====================================================
    // TEST 4: CURRENT DATABASE MONITOR (EXCLUDING HEADERS)
    // ====================================================
    cout << "[TEST 4: RE-PRINTING ALL RECOGNIZED SYSTEM USERS]\n";
    userControl.print_all_users();
    cout << "\n==================================================\n";
    cout << "        END OF FRAMEWORK SYSTEM TEST SUITE\n";
    cout << "==================================================\n";
}