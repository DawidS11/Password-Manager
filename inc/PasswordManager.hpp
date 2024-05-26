#pragma once
#include <iostream>
#include <string>
#include <map>

class PasswordManager {
private:
    std::string password;
    std::unordered_map<std::string, std::string> passwords;

public:
    PasswordManager();
    PasswordManager(std::string);
    void addOrUpdatePassword(std::string, std::string);
};