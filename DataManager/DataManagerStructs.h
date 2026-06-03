#pragma once
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct CafeSession {
    int userId{};
    int durationMinutes{};
    int printsCount{};
    int scansCount{};
};

struct PublicUser {
    int uniqueId{};
    string userName{};
    string password{};
    string email{};
    string joiningDate{};
    double totalBill{};
};

struct Admin {
    string email{};
    string password{};
};