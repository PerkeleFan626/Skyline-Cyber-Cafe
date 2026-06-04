#pragma once

#include <string>
using namespace std;

struct AdminUser {
    int adminId{};
    string email;
    string password;
};