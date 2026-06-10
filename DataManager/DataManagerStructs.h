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

struct TransactionRecord {
    int userId = 0;
    double internetPaid = 0.0;
    double gamingPaid = 0.0;
    double printsPaid = 0.0;
    double scansPaid = 0.0;
    double totalPaid = 0.0;
};

struct UserSession {
    int userId = 0;
    int internetMinutes = 0;
    int gamingMinutes = 0;
    int printsCount = 0;
    int scansCount = 0;
};

struct UserCompleteAudit {
    PublicUser profile;
    UserSession activeSession;
    bool hasActiveSession = false;
    std::vector<TransactionRecord> paymentHistory;
};