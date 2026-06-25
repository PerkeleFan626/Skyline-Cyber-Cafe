#include "DataManager.h"
#include "../Globals/Globals.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include "sstream"

#include "../Security/SecurityManager.h"

using namespace std;

// ============================================================================
// 1. CONSTRUCTOR & INITIALIZATION
// ============================================================================

DataManager::DataManager(string pub_f, string adm_f, string ses_f, string hist_f)
        : public_file(filePath::DATA_DIR + pub_f),
          admin_file(filePath::DATA_DIR + adm_f),
          session_file(filePath::DATA_DIR + ses_f),
          history_file(filePath::DATA_DIR + hist_f) {
        bootstrap_files();
}


void DataManager::bootstrap_files() {

    filesystem::path dirPath(filePath::DATA_DIR);

    if (!filesystem::exists(dirPath)) {
        filesystem::create_directories(dirPath);
    }

    if (!filesystem::exists(public_file)) {
        ofstream f(public_file);
        if (f.is_open()) {
            f << "uniqueId,userName,password,email,joiningDate,totalBill\n";
            f.close();
        }
    }

    if (!filesystem::exists(admin_file)) {
        ofstream f(admin_file);
        if (f.is_open()) {
            f << "adminId,userName,password\n";
            f.close();
        }
    }

    if (!filesystem::exists(session_file)) {
        ofstream f(session_file);
        if (f.is_open()) {
            f << "userId,internetMinutes,gamingMinutes,printsCount,scansCount\n";
            f.close();
        }
    }

    if (!filesystem::exists(history_file)) {
        ofstream f(history_file);
        if (f.is_open()) {
            f << "userId,internetPaid,gamingPaid,printsPaid,scansPaid,totalPaid\n";
            f.close();
        }
    }
}

// ============================================================================
// 2. PRIVATE UTILITY HELPERS
// ============================================================================

string DataManager::trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");

    if (first == string::npos) {
       return "";
    }

    size_t last = str.find_last_not_of(" \t\r\n");

    return str.substr(first, (last - first + 1));
}

vector<string> DataManager::split_csv_line(const string& line) {
    vector<string> pieces{};
    string columnData{};

    stringstream LineStream(line);

    while (getline(LineStream, columnData, ',')) {
        pieces.push_back(columnData);
    }

    return pieces;
}

// ============================================================================
// 3. PUBLIC USER OPERATIONS (CRUD)
// ============================================================================

bool DataManager::add_public_user(const PublicUser& user) {
    ofstream f(public_file, ios::app);

    if (f.is_open()) {

        Encryptor machine;

        string encryptedUser = machine.encrypt_string(user.userName);
        string encryptedPass = machine.encrypt_string(user.password);
        string encryptedEmail = machine.encrypt_string(user.email);


        f << user.uniqueId << ","

        << encryptedUser << ","
        << encryptedPass << ","
        << encryptedEmail << ","

        << user.joiningDate << ","
        << user.totalBill << "\n";

        f.close();
        return true;
    }
    
    return false;
}

vector<PublicUser> DataManager::get_all_public_users() {
    vector<PublicUser> users{};
    ifstream f(public_file);
    string line;

    if (f.is_open()) {
       getline(f,line);

        while (getline(f,line)) {
            if (line.empty()) continue;

            vector<string> tokens = split_csv_line(line);

            if (tokens.size() == 6) {
                PublicUser user;

                user.uniqueId = stoi(trim(tokens[0]));
                user.joiningDate = tokens[4];
                user.totalBill = stod(trim(tokens[5]));

                Decryptor machine;

                user.userName = machine.decrypt_string(trim(tokens[1]));
                user.password = machine.decrypt_string(trim(tokens[2]));
                user.email    = machine.decrypt_string(trim(tokens[3]));

                users.push_back(user);
            }
        }

        f.close();
    }

    return users;
}

bool DataManager::rewrite_public_users(const vector<PublicUser>& users) {
    ofstream f(public_file, ios::trunc);

    if (f.is_open()) {
        f << "uniqueId,userName,password,email,joiningDate,totalBill\n";

        Encryptor machine;

        for (const auto& user : users) {

            string encryptedUser = machine.encrypt_string(user.userName);
            string encryptedPass = machine.encrypt_string(user.password);
            string encryptedEmail = machine.encrypt_string(user.email);

            f << user.uniqueId << ","
              << encryptedUser << ","
              << encryptedPass << ","
              << encryptedEmail << ","
              << user.joiningDate << ","
              << user.totalBill << "\n";
        }
        f.close();
        return true;
    }
    return false;
}

// ============================================================================
// 4. ADMIN USER OPERATIONS (CRUD)
// ============================================================================

bool DataManager::add_admin(const AdminUser& admin) {
    ofstream f(admin_file, ios::app);

    if (f.is_open()) {
        Encryptor machine;

        string encryptedUser = machine.encrypt_string(admin.userName);
        string encryptedPass = machine.encrypt_string(admin.password);

        f << admin.adminId << ","
          << encryptedUser << ","
          << encryptedPass << "\n";
        f.close();
        return true;
    }

    return false;
}

vector<AdminUser> DataManager::get_all_admins()
{
    vector<AdminUser> admins{};
    ifstream f(admin_file);
    string line;

    if (f.is_open()) {
        getline(f, line);

        while (getline(f, line)) {
            if (line.empty()) continue;

            vector<string> tokens = split_csv_line(line);

            if (tokens.size() == 3) {
                AdminUser admin;
               admin.adminId = stoi(trim(tokens[0]));


                Decryptor machine;

                admin.userName = machine.decrypt_string(trim(tokens[1]));
                admin.password = machine.decrypt_string(trim(tokens[2]));

                admins.push_back(admin);
            }

        }
        f.close();
    }
    return admins;
}

// ============================================================================
// 🟢 NEW: REMOVE ADMIN FROM DISK
// ============================================================================
bool DataManager::remove_admin(int adminId) {
    vector<AdminUser> admins = get_all_admins();

    ofstream f(admin_file, ios::trunc);

    if (f.is_open()) {
        f << "adminId,userName,password\n";

        Encryptor machine;

        for (const auto& admin : admins) {
            if (admin.adminId != adminId) {
                string encryptedUser = machine.encrypt_string(admin.userName);
                string encryptedPass = machine.encrypt_string(admin.password);

                f << admin.adminId << ","
                  << encryptedUser << ","
                  << encryptedPass << "\n";
            }
        }
        f.close();
        return true;
    }
    return false;
}

// ============================================================================
// 5. Transaction History
// ============================================================================

bool DataManager::add_transaction_history(const TransactionRecord& record) {
    ofstream f(history_file, ios::app);
    if (f.is_open()) {
        f << record.userId << ","
          << record.internetPaid << ","
          << record.gamingPaid << ","
          << record.printsPaid << ","
          << record.scansPaid << ","
          << record.totalPaid << "\n";
        f.close();
        return true;
    }

    return false;
}

bool DataManager::add_active_session(const UserSession& session) {
    remove_active_session(session.userId);

    ofstream f(session_file, ios::app);
    if (f.is_open()) {
        f << session.userId << ","
          << session.internetMinutes << ","
          << session.gamingMinutes << ","
          << session.printsCount << ","
          << session.scansCount << "\n";
        f.close();
        return true;
    }

    return false;
}

vector<UserSession> DataManager::get_all_sessions()
{
    vector<UserSession> sessions;
    ifstream f(session_file);
    if (f.is_open()) {
        string line;
        getline(f, line);

        while (getline(f, line)) {
            vector<string> tokens = split_csv_line(line);
            if (tokens.size() >= 5) {
                UserSession session;
                session.userId = stoi(trim(tokens[0]));
                session.internetMinutes = stoi(trim(tokens[1]));
                session.gamingMinutes = stoi(trim(tokens[2]));
                session.printsCount = stoi(trim(tokens[3]));
                session.scansCount = stoi(trim(tokens[4]));
                sessions.push_back(session);
            }
            f.close();
        }

        return sessions;
    }
}

bool DataManager::remove_active_session(int userId) {
    vector<UserSession> sessions = get_all_sessions();
    ofstream f(session_file, ios::trunc);

    if (f.is_open()) {
        f << "userId,internetMinutes,gamingMinutes,printsCount,scansCount\n";

        for (const auto& session : sessions) {
            if (session.userId != userId) {
                f << session.userId << ","
                  << session.internetMinutes << ","
                  << session.gamingMinutes << ","
                  << session.printsCount << ","
                  << session.scansCount << "\n";
            }
        }
        f.close();
        return true;
    }
    return false;
}