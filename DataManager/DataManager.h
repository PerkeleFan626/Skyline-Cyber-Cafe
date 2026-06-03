#pragma once
#include "DataManagerStructs.h"
#include "../Globals/Globals.h"


class DataManager {
private:
    string public_file;
    string admin_file;
    string session_file;

    void bootstrap_files();
    vector<string>split_csv_line(const string& line);

    string trim(const string& str);

public:
    DataManager(
    string pub_f = filePath::PUBLIC_USER_FILE,
    string adm_f = filePath::ADMIN_FILE,
    string ses_f = filePath::SESSION_FILE
    );


    bool add_public_user(const PublicUser& user); //When a new user registers an account, this function opens public_users.csv using ofstream and writes the new user details as a new row at the bottom of the file.
    vector<PublicUser> get_all_public_users(); //Opens the public_user.csv, skips the top header row and loops through it. It converts each text row into a C++ PublicUser object.
    bool validate_public_user(const string& email, const string& password); //When a user tries to log in this loops through the list and looks for the password and email, if both return true the user will be able to login.
    bool remove_public_user(int uniqueId);//It reads all users into memory, clears our the public_users.csv, it loops through the users in memory and writes them all back to the file except the one thats deleted.

    bool rewrite_public_users(const vector<PublicUser>& users);
};