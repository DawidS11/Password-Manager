#pragma once
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream> 
#include <openssl/rand.h>
#include <openssl/evp.h>

class PasswordManager
{
private:
    std::string passwordHash;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> passwords;
    friend class TestClass;

    std::string bytesToHexString(const unsigned char*, size_t);
    std::string hashPassword(const std::string&);

public:
    PasswordManager();
    PasswordManager(const std::string);
    void addOrUpdatePassword(const std::string, const std::string, const std::string);
    const std::string getPassword(const std::string&, const std::string&);
    void removePassword(const std::string, const std::string);
    void saveAll();
    void loadAll();
};