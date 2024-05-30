#include "../inc/PasswordManager.hpp"

#include <fstream>
#include <cassert>

class TestClass
{
public:
    void compareMapAndFile(PasswordManager &passwordManager)
    {
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> filePasswords;
        std::ifstream f("data.txt");
        std::string hash;
        assert(std::getline(f, hash));
        assert(passwordManager.passwordHash == hash);
        
        std::string website, login, password;
        while (std::getline(f, website))
        {
            if (std::getline(f, login))
                if (std::getline(f, password))
                    filePasswords[website] = std::unordered_map<std::string, std::string> {{login, password}};
        }
        f.close();

        for (const auto &website : passwordManager.passwords)
        {
            for (const auto &el : website.second)
            {
                assert(filePasswords.contains(website.first));
                assert(filePasswords[website.first][el.first] == el.second);
            }
        }
    }

    void saveData(PasswordManager &passwordManager)
    {
        passwordManager.addOrUpdatePassword("web1", "log1", "pass1");
        passwordManager.addOrUpdatePassword("web2", "log2", "pass2");
        passwordManager.addOrUpdatePassword("web2", "log3", "pass3");
        passwordManager.saveAll();
        compareMapAndFile(passwordManager);
    }

    void loadData(PasswordManager &passwordManager)
    {
        passwordManager.loadAll();
        std::cout << "Data loaded from file: " << std::endl;
        for (const auto &website : passwordManager.passwords)
        {
            for (const auto &el : website.second)
            {
                std::cout << website.first << std::endl
                          << el.first << std::endl
                          << el.second << std::endl;
            }
        }
        compareMapAndFile(passwordManager);
    }

    void runTests()
    {
        PasswordManager passwordManager("abc");
        saveData(passwordManager);
        loadData(passwordManager);
    }
};