#include <iostream>
#include "DataManager/DataManager.h"
#include "UserManager/UserManager.h"
#include "Globals/CallingClassGlobal.h"


int main() {
    cout << "Search for id\n";
    int testId{};
    cin >> testId;

    if (userControl.find_user_by_id(testId, matchingUser)) {
        cout << "Success: " << matchingUser.userName << " " << matchingUser.email << endl;
    } else {
        cout << "Failure \n";
    }

    cout << "delete id\n";
    int idToDelete;
    cin >> idToDelete;

    if (userControl.remove_user_by_id(idToDelete)) {
        cout << "Success\n";
    } else {
        cout << "failure\n";
    }

    userControl.print_all_users();
}