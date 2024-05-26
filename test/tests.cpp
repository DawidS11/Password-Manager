#include "../inc/PasswordManager.hpp"

#include <fstream>
#include <cassert>

class TestClass
{
public:
    void compareMapAndFile(PasswordManager &passwordManager)
    {
        std::unordered_map<std::string, std::string> filePasswords;
        std::ifstream f("data.txt");
        std::string website, password;
        while (std::getline(f, website))
        {
            if (std::getline(f, password))
                filePasswords[website] = password;
        }
        f.close();

        for (const auto &el : passwordManager.passwords)
        {
            //assert(filePasswords.contains(el.first) && ("filePassword does not contain ", el.first, "\n"));
            assert(filePasswords[el.first] == el.second);
        }
    }

    void saveData(PasswordManager &passwordManager)
    {
        passwordManager.addOrUpdatePassword("web1", "pass1");
        passwordManager.addOrUpdatePassword("web2", "pass2");
        passwordManager.addOrUpdatePassword("web2", "pass3");
        passwordManager.saveAll();
        compareMapAndFile(passwordManager);
    }

    void loadData(PasswordManager &passwordManager)
    {
        passwordManager.loadAll();

        for (const auto &el : passwordManager.passwords)
        {
            std::cout << el.first << std::endl
                      << el.second << std::endl;
        }
        compareMapAndFile(passwordManager);
    }

    void runTests()
    {
        PasswordManager passwordManager;
        saveData(passwordManager);
        loadData(passwordManager);
    }
};