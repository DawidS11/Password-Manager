#include "../inc/PasswordManager.hpp"

PasswordManager::PasswordManager()
    : password("")
{
}

PasswordManager::PasswordManager(const std::string password)
    : password(password)
{
}

void PasswordManager::addOrUpdatePassword(const std::string website, const std::string password)
{
    if (passwords.contains(website))
    {
        std::cout << "Password for this company exists. Do you want to proceed? (y/n)" << std::endl;
        char answer;
        std::cin >> answer;
        while (answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N')
        {
            std::cout << "Password for this company exists. Do you want to proceed? (y/n)" << answer << std::endl;
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

void PasswordManager::saveAll()
{
    std::ofstream f("data.txt");
    for (const auto &el : passwords)
    {
        f << el.first << "\n"
          << el.second << "\n";
    }
    f.close();
}

void PasswordManager::loadAll()
{
    std::ifstream f("data.txt");
    std::string website, password;
    while (std::getline(f, website))
    {
        if (std::getline(f, password))
            passwords[website] = password;
    }
    f.close();
}