#include "../inc/PasswordManager.hpp"

PasswordManager::PasswordManager()
    : password("")
{
}

PasswordManager::PasswordManager(const std::string password)
    : password(password)
{
}

void PasswordManager::addOrUpdatePassword(const std::string password, const std::string website)
{
    if (passwords.contains(website))
    {
        std::cout << "Password for this company exists. Do you want to proceed? (y/n)" << std::endl;
        char answer;
        std::cin >> answer;
        while (answer != 'y' || answer != 'Y' || answer != 'n' || answer != 'N')
        {
            std::cin >> answer;
        }
        if (answer == 'n' || answer == 'N')
        {
            return;
        }
    }
    passwords[website] = password;
}

void PasswordManager::removePassword(const std::string website)
{
    if (passwords.contains(website))
        passwords.extract(website);
    else
        std::cout << "Password for website " << website << " is not saved" << std::endl;
}