#include <iostream>
#include "Headers/DataManager.h"
#include "Headers/UserManager.h"
#include "Headers/CallingClassGlobal.h"


int main() {
    PublicUser matchingUser;

    int testId{};
    cin >> testId;

    if (userControl.find_user_by_id(testId, matchingUser)) {
        cout << "Success: " << matchingUser.userName << " " << matchingUser.email << endl;
    } else {
        cout << "Failure \n";
    }
}