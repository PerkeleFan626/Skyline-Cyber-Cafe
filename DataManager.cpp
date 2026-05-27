#include "Headers/DataManager.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include "sstream"

using namespace std;

DataManager::DataManager(string pub_f, string adm_f, string ses_f)
    :public_file(pub_f),admin_file(adm_f),session_file(ses_f) {
    bootstrap_files();
}


void DataManager::bootstrap_files() {

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
            f << "userId,durationMinutes,printsCount,ScansCount\n";
            f.close();
        }
    }
}

vector<string> DataManager::split_csv_line(const string& line) {
    vector<string> pieces{};
    string columData{};

    stringstream LineStream(line);

    while (getline(LineStream, columData, ',')) {
        pieces.push_back(columData);
    }

    return pieces;
}

bool DataManager::add_public_user(const PublicUser& user) {
    ofstream f(public_file, ios::app);

    if (f.is_open()) {
        f << user.uniqueId << ","
          << user.userName << ","
          << user.password << ","
          << user.email << ","
          << user.joiningDate << ","
          << user.totalBill << "\n";

        f.close();
        return true;
    }
    
    return false;
}
