#include <iostream>
#include <string>
#include "Globals/CallingClassGlobal.h"

using namespace std;

// Quick helper to print a clean menu divider
void printDivider() {
    cout << "--------------------------------------------------------\n";
}

int main() {
    int mainChoice = 0;

    while (true) {
        cout << "========================================================\n";
        cout << "         CYBER CAFE CENTRAL INTERACTIVE FRAMEWORK        \n";
        cout << "========================================================\n";
        cout << " 1. [ADMIN] Register a New Administrator\n";
        cout << " 2. [CLIENT] Register a New Public User Account\n";
        cout << " 3. [TERMINAL] Start Live Terminal Session (Login User)\n";
        cout << " 4. [TERMINAL] Simulate Live Activity (Add Mins/Prints/Scans)\n";
        cout << " 5. [TERMINAL] End Session & Execute Financial Checkout\n";
        cout << " 6. [EXIT] Shutdown System\n";
        printDivider();
        cout << "Enter selection (1-6): ";

        if (!(cin >> mainChoice)) {
            cout << "⚠️ Invalid selection. Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore(10000, '\n'); // Clear line buffer

        if (mainChoice == 6) {
            cout << "\nShutting down Cyber Cafe Core Engines. Goodbye!\n";
            break;
        }

        switch (mainChoice) {
            case 1: {
                // 1. ADMIN REGISTRATION
                string admEmail, admPass;
                cout << "\n--- [ADMIN PORTAL] CREATE MANAGER ACCOUNT ---\n";
                cout << "Enter New Admin Email: ";
                getline(cin, admEmail);
                cout << "Enter New Admin Password: ";
                getline(cin, admPass);

                if (adminControl.register_new_admin(admEmail, admPass)) {
                    cout << "👉 Success: Admin account saved. Check your admins.csv file!\n";
                } else {
                    cout << "❌ Error: Failed to add admin to tracking records.\n";
                }
                break;
            }

            case 2: {
                // 2. CLIENT REGISTRATION
                string pubUser, pubPass, pubEmail;
                cout << "\n--- [CLIENT PORTAL] REGISTER NEW PROFILE ---\n";
                cout << "Enter Account Username: ";
                getline(cin, pubUser);
                cout << "Enter Account Password: ";
                getline(cin, pubPass);
                cout << "Enter Account Email:    ";
                getline(cin, pubEmail);

                if (userControl.register_new_public_user(pubUser, pubPass, pubEmail)) {
                    cout << "👉 Success: User registration complete (ID sequence: 1001+).\n";
                    cout << "Check public_users.csv to view their starting balance of $0.00.\n";
                } else {
                    cout << "❌ Error: Public account registration rejected.\n";
                }
                break;
            }

            case 3: {
                // 3. START SESSION
                int targetId;
                cout << "\n--- [TERMINAL GATEWAY] ACTIVATING COMPUTER DESK ---\n";
                cout << "Enter the User ID logging in (e.g., 1001): ";
                cin >> targetId;

                // Fire the SessionManager to provision a live un-billed tracking row
                if (sessionControl.start_new_session(targetId)) {
                    cout << "👉 Open sessions.csv! You will see an active row initialized to 0s.\n";
                }
                break;
            }

            case 4: {
                // 4. SIMULATE ACTIVITY
                int targetId;
                int incInternet, incGaming, incPrints, incScans;

                cout << "\n--- [TERMINAL DESK] SIMULATING DESKTOP footprints ---\n";
                cout << "Enter User ID currently sitting at terminal: ";
                cin >> targetId;
                cout << "Add Internet Minutes used: ";
                cin >> incInternet;
                cout << "Add Gaming Minutes used:   ";
                cin >> incGaming;
                cout << "Add Pages Printed:         ";
                cin >> incPrints;
                cout << "Add Documents Scanned:     ";
                cin >> incScans;

                // Inject tracking modifications straight into sessions.csv
                if (sessionControl.simulate_activity(targetId, incInternet, incGaming, incPrints, incScans)) {
                    cout << "👉 Check sessions.csv! The counts for User " << targetId << " have increased.\n";
                }
                break;
            }

            case 5: {
                // 5. CHECKOUT AND ACCOUNTING COMMIT
                int targetId;
                cout << "\n--- [FRONT DESK checkout TERMINAL] ---\n";
                cout << "Enter checking out User ID: ";
                cin >> targetId;

                cout << "Executing cross-file verification logic pipeline...\n";
                // Ends the session, calculates costs, writes user_history.csv, updates public_users.csv
                if (sessionControl.end_and_checkout_session(targetId)) {
                    cout << "👉 Database Synchronization Complete:\n";
                    cout << "   1. A receipt line was written into user_history.csv\n";
                    cout << "   2. The user's lifetime totalBill was updated in public_users.csv\n";
                    cout << "   3. The active terminal row was scrubbed completely from sessions.csv\n";
                }
                break;
            }

            default:
                cout << "⚠️ Choice out of structural alignment bounds. Choose 1-6.\n";
                break;
        }
        cout << "\n";
    }

    return 0;
}