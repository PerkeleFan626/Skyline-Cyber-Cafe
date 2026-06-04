#include "DataManager.h"
#include "../Globals/Globals.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include "sstream"

using namespace std;

// ============================================================================
// 1. CONSTRUCTOR & INITIALIZATION
// ============================================================================

DataManager::DataManager(string pub_f, string adm_f, string ses_f)
        : public_file(filePath::DATA_DIR + pub_f),
          admin_file(filePath::DATA_DIR + adm_f),
          session_file(filePath::DATA_DIR + ses_f) {
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
            f << "email,password\n";
            f.close();
        }
    }

    if (!filesystem::exists(session_file)) {
        ofstream f(session_file);
        if (f.is_open()) {
            f << "userId,durationMinutes,printsCount,scansCount\n";
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
        Encryptor lock;

        f << user.uniqueId << ","
           << lock.encrypt_string(user.userName) << ","
           << lock.encrypt_string(user.password) << ","
           << lock.encrypt_string(user.email) << ","
           << lock.encrypt_string(user.joiningDate) << ","
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



        Decryptor unlock;

        while (getline(f,line)) {
            if (line.empty()) continue;

            // debug
           // cout << __LINE__ << " " << unlock.decrypt_string(line) << endl;

            vector<string> tokens = split_csv_line(line);

            if (tokens.size() == 6) {
                PublicUser user;

                user.uniqueId = stoi(trim(tokens[0]));

                user.userName = unlock.decrypt_string(tokens[1]);
                user.password = unlock.decrypt_string(tokens[2]);
                user.email = unlock.decrypt_string(tokens[3]);
                user.joiningDate = unlock.decrypt_string(tokens[4]);

                user.totalBill = stod(trim(tokens[5]));

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

        Encryptor lock;

        for (const auto& user : users) {
            f << user.uniqueId << ","
              << lock.encrypt_string(user.userName) << ","
              << lock.encrypt_string(user.password) << ","
              << lock.encrypt_string(user.email) << ","
              << lock.encrypt_string(user.joiningDate) << ","
              << user.totalBill << "\n";
        }
        f.close();
        return true;
    }
    return false;
}