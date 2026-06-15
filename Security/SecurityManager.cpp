#include "SecurityManager.h"
#include <sstream>
#include <vector>

using namespace std;

// ============================================================================
// ENCRYPTION ENGINE
// ============================================================================

string Encryptor::encrypt_string(const string& plainText) {
    if (plainText.empty()) return "";

    stringstream ss;

    for (size_t i = 0; i < plainText.length(); i++) {
        int asciiVal = static_cast<int>(plainText[i]);

        int encryptVal = (asciiVal * 69) + 420;

        ss << encryptVal;

        if (i < plainText.length() -1) {
            ss << "-";
        }
    }

    return ss.str();
}

// ============================================================================
// DECRYPTION ENGINE
// ============================================================================

string Decryptor::decrypt_string(const string& encryptedText) {
    if (encryptedText.empty()) return "";

    stringstream ss(encryptedText);
    string tempSegment;
    string plainText = "";

    while (getline(ss, tempSegment, '-')) {
        if (!tempSegment.empty()) {
            int encryptedVal = stoi(tempSegment);

            int originalAscii = (encryptedVal -420) / 69;

            plainText += static_cast<char>(originalAscii);
        }

    }

    return plainText;
}