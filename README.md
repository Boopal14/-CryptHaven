# CryptHaven
**CryptHaven** is a secure and lightweight password manager built using C++ that leverages Object-Oriented Programming (OOP) principles, file handling, and basic encryption techniques (Caesar Cipher and XOR Cipher). It is designed for academic and learning purposes to demonstrate the application of OOP concepts in a cybersecurity-related context.

This project implements a secure vault system where credentials can be added, retrieved, and viewed securely. All data is stored in an encrypted file to prevent unauthorized access. A master password provides an additional layer of protection.

---

## Table of Contents

- [Features](#features)
- [Design Overview](#design-overview)
- [How It Works](#how-it-works)
- [Build Instructions](#build-instructions)
- [Usage](#usage)
- [Security Notice](#security-notice)
- [Future Enhancements](#future-enhancements)
- [License](#license)

---

## Features

- Master password-based authentication
- Password storage encrypted using Caesar or XOR cipher
- Organized by site/account name
- View stored website list
- Fully encrypted storage file (`vault.secure`)
- Clean Object-Oriented architecture


---

## Design Overview

This project uses an Object-Oriented approach to separate concerns and make the code maintainable and extendable:

### Classes and Responsibilities

- **User**  
  Handles master password authentication and session control.

- **EncryptionAlgorithm (Abstract Class)**  
  Defines the encryption/decryption interface.

- **XOREncryption (Derived Class)**  
  Implements XOR-based encryption and decryption.

- **CaesarEncryption (Derived Class)**  
  Implements Caesar cipher for encryption and decryption.

- **Vault**  
  Manages password storage, retrieval, and encryption/decryption with file I/O.

---

## How It Works

1. On launch, the application prompts the user to enter the master password.
2. The user selects an encryption algorithm (Caesar or XOR).
3. The password vault file is decrypted into memory.
4. The user can:
   - Add new credentials (site and password)
   - Retrieve stored passwords
   - View all saved site names
5. After every operation, the vault is re-encrypted and saved to `vault.secure`.

**Default master password:** `admin123`

---

## Build Instructions

### Requirements

- C++11 or later
- A C++ compiler (g++, clang++, MSVC)

### Compilation

Run the following command in your terminal:

```bash
g++ password_manager.cpp -o CryptHaven


