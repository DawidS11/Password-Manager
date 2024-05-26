#pragma once
#include <iostream>
#include <string>
#include <map>

class PasswordManager
{
private:
    std::string password;
    std::unordered_map<std::string, std::string> passwords;

public:
    PasswordManager();
    PasswordManager(const std::string);
    void addOrUpdatePassword(const std::string, const std::string);
    void removePassword(const std::string);
};