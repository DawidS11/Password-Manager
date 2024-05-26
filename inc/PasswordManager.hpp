#pragma once
#include <iostream>
#include <string>
#include <map>
#include <fstream>

class PasswordManager
{
private:
    std::string password;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> passwords;
    friend class TestClass;

public:
    PasswordManager();
    PasswordManager(const std::string);
    void addOrUpdatePassword(const std::string, const std::string, const std::string);
    const std::string getPassword(const std::string&, const std::string&);
    void removePassword(const std::string, const std::string);
    void saveAll();
    void loadAll();
};