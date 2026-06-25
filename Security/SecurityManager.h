#pragma once
#include <string>

using namespace std;

class Encryptor {
public:
    string encrypt_string(const string& plainText);

};

class Decryptor {
public:
    string decrypt_string(const string& encryptedText);

};