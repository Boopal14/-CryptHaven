#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
using namespace std;

// ================== 🔐 Encryption Base Class ====================
class EncryptionAlgorithm {
public:
    virtual string encrypt(const string& data) = 0;
    virtual string decrypt(const string& data) = 0;
    virtual ~EncryptionAlgorithm() {}
};

// ================== 🔑 XOR Encryption ===========================
class XOREncryption : public EncryptionAlgorithm {
private:
    char key;
public:
    XOREncryption(char k = 'K') : key(k) {}

    string encrypt(const string& data) override {
        string result = data;
        for (char& c : result)
            c ^= key;
        return result;
    }

    string decrypt(const string& data) override {
        return encrypt(data); // XOR is symmetric
    }
};

// ================== 🔁 Caesar Cipher Encryption =================
class CaesarEncryption : public EncryptionAlgorithm {
private:
    int shift;
public:
    CaesarEncryption(int s = 3) : shift(s) {}

    string encrypt(const string& data) override {
        string result = data;
        for (char c : data) {
            if (isalpha(c))
                result += islower(c) ? ((c - 'a' + shift) % 26 + 'a') : ((c - 'A' + shift) % 26 + 'A');
            else
                result += c;
        }
        return result;
    }

    string decrypt(const string& data) override {
        string result = data;
        for (char c : data) {
            if (isalpha(c))
                result += islower(c) ? ((c - 'a' - shift + 26) % 26 + 'a') : ((c - 'A' - shift + 26) % 26 + 'A');
            else
                result += c;
        }
        return result;
    }
};

// ================== 🧑 User for Master Password ==================
class User {
private:
    string masterPassword;
public:
    User(const string& password) : masterPassword(password) {}

    bool authenticate(const string& input) {
        return input == masterPassword;
    }
};

// ================== 🔐 Vault ============================
class Vault {
private:
    map<string, string> passwordStore;
    EncryptionAlgorithm* encryptor;
    string filename;

public:
    Vault(EncryptionAlgorithm* algo, string file = "vault.secure") : encryptor(algo), filename(file) {
        loadFromFile();
    }

    void addPassword(const string& site, const string& password) {
        passwordStore[site] = password;
        saveToFile();
        cout << "[+] Password added for " << site << endl;
    }

    void getPassword(const string& site) {
        if (passwordStore.find(site) != passwordStore.end()) {
            cout << "[🔐] Password for " << site << ": " << passwordStore[site] << endl;
        } else {
            cout << "[!] No password stored for " << site << endl;
        }
    }

    void viewAllSites() {
        cout << "\n=== Stored Accounts ===\n";
        for (auto& pair : passwordStore)
            cout << "- " << pair.first << endl;
    }

private:
    void saveToFile() {
        // Serialize vault
        ostringstream oss;
        for (auto& pair : passwordStore)
            oss << pair.first << "|" << pair.second << "\n";

        string plainData = oss.str();
        string encryptedData = encryptor->encrypt(plainData);

        ofstream file(filename, ios::binary);
        file << encryptedData;
        file.close();
    }

    void loadFromFile() {
        ifstream file(filename, ios::binary);
        if (!file) return;

        string encryptedData((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        string decryptedData = encryptor->decrypt(encryptedData);

        istringstream iss(decryptedData);
        string line;
        while (getline(iss, line)) {
            size_t sep = line.find('|');
            if (sep != string::npos) {
                string site = line.substr(0, sep);
                string password = line.substr(sep + 1);
                passwordStore[site] = password;
            }
        }

        file.close();
    }
};

// ================== 🧠 Main ================================
int main() {
    cout << "=== Secure Password Manager ===\n";
    string masterPass;
    cout << "Enter master password to unlock vault: ";
    cin >> masterPass;

    User user("admin123"); // default master password
    if (!user.authenticate(masterPass)) {
        cout << "❌ Authentication Failed. Exiting.\n";
        return 0;
    }

    int algoChoice;
    cout << "\nChoose encryption algorithm:\n1. XOR Encryption\n2. Caesar Cipher\nChoice: ";
    cin >> algoChoice;

    EncryptionAlgorithm* algorithm = nullptr;
    if (algoChoice == 1) {
        algorithm = new XOREncryption('P');
    } else if (algoChoice == 2) {
        algorithm = new CaesarEncryption(3);
    } else {
        cout << "Invalid choice.\n";
        return 0;
    }

    Vault vault(algorithm);
    int choice;
    cin.ignore(); // flush newline

    while (true) {
        cout << "\n1. Add Password\n2. Get Password\n3. View All Sites\n4. Exit\nChoice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string site, pass;
            cout << "Enter website/account: ";
            getline(cin, site);
            cout << "Enter password: ";
            getline(cin, pass);
            vault.addPassword(site, pass);
        } else if (choice == 2) {
            string site;
            cout << "Enter website/account to retrieve: ";
            getline(cin, site);
            vault.getPassword(site);
        } else if (choice == 3) {
            vault.viewAllSites();
        } else if (choice == 4) {
            cout << "Exiting Password Manager.\n";
            break;
        } else {
            cout << "Invalid option.\n";
        }
    }

    delete algorithm;
    return 0;
}
