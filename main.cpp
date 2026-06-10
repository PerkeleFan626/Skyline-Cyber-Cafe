#include <iostream>
#include <string>
#include "Globals/CallingClassGlobal.h"

using namespace std;

// Quick helper to print a clean menu visual boundary line
void printDivider() {
    cout << "--------------------------------------------------------\n";
}

int main() {
    int mainChoice = 0;

    while (true) {
        cout << "========================================================\n";
        cout << "         CYBER CAFE CENTRAL INTERACTIVE FRAMEWORK        \n";
        cout << "========================================================\n";
        cout << " 1. [ADMIN] Register a New Administrator Account\n";
        cout << " 2. [CLIENT] Register a New Public User Account\n";
        cout << " 3. [TERMINAL] Start Live Terminal Session (Login User)\n";
        cout << " 4. [TERMINAL] Simulate Live Activity (Add Mins/Prints/Scans)\n";
        cout << " 5. [TERMINAL] End Session & Execute Financial Checkout\n";
        cout << " 6. [ADMIN] Run Deep Audit Lookup Dashboard (User History)\n";
        cout << " 7. [EXIT] Shutdown System\n";
        printDivider();
        cout << "Enter selection (1-7): ";

        // Safety check to handle accidental text inputs gracefully instead of looping forever
        if (!(cin >> mainChoice)) {
            cout << "⚠️ Invalid selection. Please enter a valid number configuration.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore(10000, '\n'); // Clear line buffer memory

        // System Break Condition
        if (mainChoice == 7) {
            cout << "\nShutting down Cyber Cafe Core Engines. Safe travels!\n";
            break;
        }

        switch (mainChoice) {
            case 1: {
                // 1. ADMIN REGISTRATION ENGINE
                string admEmail, admPass;
                cout << "\n--- [ADMIN PORTAL] CREATE MANAGER ACCOUNT ---\n";
                cout << "Enter New Admin Email: ";
                getline(cin, admEmail);
                cout << "Enter New Admin Password: ";
                getline(cin, admPass);

                if (adminControl.register_new_admin(admEmail, admPass)) {
                    cout << "👉 Success: Admin account saved. Check your admins.csv file!\n";
                } else {
                    cout << "❌ Error: Failed to append admin to storage records.\n";
                }
                break;
            }

            case 2: {
                // 2. CLIENT REGISTRATION ENGINE
                string pubUser, pubPass, pubEmail;
                cout << "\n--- [CLIENT PORTAL] REGISTER NEW PROFILE ---\n";
                cout << "Enter Account Username: ";
                getline(cin, pubUser);
                cout << "Enter Account Password: ";
                getline(cin, pubPass);
                cout << "Enter Account Email:    ";
                getline(cin, pubEmail);

                if (userControl.register_new_public_user(pubUser, pubPass, pubEmail)) {
                    cout << "👉 Success: User registration complete (IDs auto-start at 1001).\n";
                    cout << "Check public_users.csv to view their baseline entry profile.\n";
                } else {
                    cout << "❌ Error: Public account registration rejected.\n";
                }
                break;
            }

            case 3: {
                // 3. START TERMINAL SESSION LAYER
                int targetId;
                cout << "\n--- [TERMINAL GATEWAY] ACTIVATING COMPUTER DESK ---\n";
                cout << "Enter the User ID logging in (e.g., 1001): ";
                cin >> targetId;

                // Spawns an unbilled running tally spreadsheet row initialized to 0
                if (sessionControl.start_new_session(targetId)) {
                    cout << "👉 Open sessions.csv! You will see an active tracking block active.\n";
                }
                break;
            }

            case 4: {
                // 4. INJECT RUNNING TERMINAL ACTIVITY FOOTPRINTS
                int targetId;
                int incInternet, incGaming, incPrints, incScans;

                cout << "\n--- [TERMINAL DESK] SIMULATING DESKTOP OPERATIONS ---\n";
                cout << "Enter User ID currently occupying terminal: ";
                cin >> targetId;
                cout << "Add Internet Minutes used: ";
                cin >> incInternet;
                cout << "Add Gaming Minutes used:   ";
                cin >> incGaming;
                cout << "Add Pages Printed:         ";
                cin >> incPrints;
                cout << "Add Documents Scanned:     ";
                cin >> incScans;

                // Mutates metrics dynamically on disk inside sessions.csv
                if (sessionControl.simulate_activity(targetId, incInternet, incGaming, incPrints, incScans)) {
                    cout << "👉 Check sessions.csv! The counts for User " << targetId << " have updated.\n";
                }
                break;
            }

            case 5: {
                // 5. TERMINATE LIVE MONITORING & RESOLVE BILL LEDGER
                int targetId;
                cout << "\n--- [FRONT DESK CHECKOUT TERMINAL] ---\n";
                cout << "Enter checking out User ID: ";
                cin >> targetId;

                cout << "Executing cross-file verification logic pipeline...\n";
                // Collects session numbers, converts to money, logs receipt, clears terminal sheet
                if (sessionControl.end_and_checkout_session(targetId)) {
                    cout << "🟢 Database Synchronization Complete! Files updated successfully.\n";
                }
                break;
            }

            case 6: {
                // 6. ADMINISTRATIVE CROSS-FILE MASTER DOSSIER LOOKUP
                int lookupId;
                cout << "\n--- [SECURITY CONSOLE] MASTER DOSSIER AUDIT INTERFACE ---\n";
                cout << "Enter target Customer User ID to inspect (e.g., 1001): ";
                cin >> lookupId;

                // Fire our new Detective Engine to read all CSVs and print the full summary!
                adminControl.print_user_audit_dashboard(lookupId);
                break;
            }

            default:
                cout << "⚠️ Selection outside core bounds. Please choose a value from 1 to 7.\n";
                break;
        }
        cout << "\n";
    }

    return 0;
}