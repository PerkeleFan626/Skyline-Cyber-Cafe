#include <iostream>
#include "DataManager/DataManager.h"
#include "UserManager/UserManager.h"
#include "Globals/CallingClassGlobal.h"


int main() {

    // ==========================================
    // 1. ACCOUNT CREATION BLOCK (Uses Live System Clock)
    // ==========================================
    cout << "--- TEST 1: ACCOUNT CREATION (REGISTRATION) ---\n";
    string regName, regPass, regEmail;

    cout << "Choose a Username: ";
    cin >> regName;
    cout << "Choose a Password: ";
    cin >> regPass;
    cout << "Enter Email Address: ";
    cin >> regEmail;

    // 💡 No more manual date input or strings! The backend pulls your PC clock automatically.
    if (userControl.register_new_public_user(regName, regPass, regEmail)) {
        cout << "Success: Account validated, unique ID computed, and live system date stamped!\n\n";
    } else {
        cout << "Failure: Registration failed.\n\n";
    }

    // ==========================================
    // 2. SEARCH BY ID BLOCK (Uses cin >>)
    // ==========================================
    cout << "--- TEST 2: SEARCH BY ID ---\n";
    cout << "Enter an ID to look up: ";
    int testId{};
    cin >> testId;

    if (userControl.find_user_by_id(testId, matchingUser)) {
        cout << "Success: Found " << matchingUser.userName << " | " << matchingUser.email << "\n\n";
    } else {
        cout << "Failure: User not found.\n\n";
    }

    // ==========================================
    // 3. SEARCH BY USERNAME BLOCK (Uses cin >>)
    // ==========================================
    cout << "--- TEST 3: SEARCH BY USERNAME ---\n";
    cout << "Enter an exact username to look up: ";
    string nameToSearch;
    cin >> nameToSearch;

    PublicUser nameMatchUser;
    if (userControl.find_user_by_name(nameToSearch, nameMatchUser)) {
        cout << "Success: Found ID " << nameMatchUser.uniqueId << " with Email: " << nameMatchUser.email << "\n\n";
    } else {
        cout << "Failure: Username not found.\n\n";
    }

    // ==========================================
    // 4. DELETE BY ID BLOCK (Uses cin >>)
    // ==========================================
    cout << "--- TEST 4: DELETE RECORD ---\n";
    cout << "Enter an ID to completely delete from CSV: ";
    int idToDelete;
    cin >> idToDelete;

    if (userControl.remove_user_by_id(idToDelete)) {
        cout << "Success: Record erased.\n\n";
    } else {
        cout << "failure\n\n";
    }

    // ==========================================
    // 5. DISPLAY ALL RECORDS BLOCK
    // ==========================================
    cout << "--- TEST 5: PRINT CURRENT CSV STATE (EXCLUDING HEADER) ---\n";
    userControl.print_all_users();
    cout << "\n";

    // ==========================================
    // 6. AUTHENTICATION BLOCK (Uses getline)
    // ==========================================
    cout << "--- TEST 6: LOGIN VALIDATION ---\n";
    string inputUserName, inputPassword;

    // 💡 Crucial: Clears out '\n' left over by the last cin >> in Test 4
    cin.ignore();

    cout << "Enter Login Username: ";
    getline(cin, inputUserName);

    cout << "Enter Login Password: ";
    getline(cin, inputPassword);

    PublicUser activeUser;

    if (userControl.authenticate_user(inputUserName, inputPassword, activeUser)) {
        cout << "Auth Success! Welcome back, " << activeUser.email << "\n\n";

        // ====================================================
        // 7. MUTATION DEDICATED TESTS (Nested under login safety)
        // ====================================================
        cout << "--- TEST 7: ACCOUNT REFIELD MODIFICATIONS ---\n";

        // Test A: Modify Username
        cout << "Enter a NEW username for this account: ";
        string freshName;
        getline(cin, freshName);
        userControl.update_username(activeUser.uniqueId, freshName);

        // Test B: Modify Password
        cout << "Enter a NEW password for this account: ";
        string freshPass;
        getline(cin, freshPass);
        userControl.update_password(activeUser.uniqueId, freshPass);

        // Test C: Modify Email
        cout << "Enter a NEW email for this account: ";
        string freshEmail;
        getline(cin, freshEmail);
        userControl.update_email(activeUser.uniqueId, freshEmail);

        // Test D: Modify Financial Bill Balance
        cout << "Enter a NEW bill balance amount (e.g., 45.50): ";
        double freshBill;
        cin >> freshBill;
        userControl.update_total_bill(activeUser.uniqueId, freshBill);

        // Final Sanity Verification Dump
        cout << "\n--- FINAL VERIFICATION DUMP OF REWRITTEN CSV ---\n";
        userControl.print_all_users();

    } else {
        cout << "Auth Failure: Skipping modification tests.\n";
    }
}