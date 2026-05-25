#include "Headers/DataManager.h"
#include <iostream>
#include <fstream>
#include <filesystem>

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