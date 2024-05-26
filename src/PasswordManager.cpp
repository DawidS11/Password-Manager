#include "../inc/PasswordManager.hpp"

PasswordManager::PasswordManager()
    : password("")
{}

PasswordManager::PasswordManager(std::string password)
    : password(password)
{}

void PasswordManager::addOrUpdatePassword(std::string password, std::string website) {
    if(passwords.contains(password)) {
        std::cout << "Password for this company exists. Do you want to proceed? (y/n)" << std::endl;
        char answer;
        std::cin >> answer;
        while(answer != 'y' || answer != 'Y' || answer != 'n' || answer != 'N') {
            std::cin >> answer;
        }
        if(answer == 'n' || answer == 'N') {
            return;
        }
    }
    passwords[website] = password;
}