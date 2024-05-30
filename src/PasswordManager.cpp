#include "../inc/PasswordManager.hpp"

PasswordManager::PasswordManager()
    : passwordHash("")
{
}

PasswordManager::PasswordManager(const std::string password)
    : passwordHash(hashPassword(password))
{
}

// Function to convert bytes to a hex string
std::string PasswordManager::bytesToHexString(const unsigned char *bytes, size_t length)
{
    std::stringstream hexStream;
    hexStream << std::hex << std::setfill('0');
    for (size_t i = 0; i < length; ++i)
    {
        hexStream << std::setw(2) << static_cast<int>(bytes[i]);
    }
    return hexStream.str();
}

std::string PasswordManager::hashPassword(const std::string &password)
{
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (ctx == nullptr)
    {
        std::cerr << "Failed to create context" << std::endl;
        return "";
    }

    if (EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr) != 1)
    {
        std::cerr << "EVP_DigestInit_ex failed" << std::endl;
        EVP_MD_CTX_free(ctx);
        return "";
    }

    if (EVP_DigestUpdate(ctx, password.c_str(), password.size()) != 1)
    {
        std::cerr << "EVP_DigestUpdate failed" << std::endl;
        EVP_MD_CTX_free(ctx);
        return "";
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int lengthOfHash = 0;
    if (EVP_DigestFinal_ex(ctx, hash, &lengthOfHash) != 1)
    {
        std::cerr << "EVP_DigestFinal_ex failed" << std::endl;
        EVP_MD_CTX_free(ctx);
        return "";
    }

    EVP_MD_CTX_free(ctx);

    return bytesToHexString(hash, lengthOfHash);
}

void PasswordManager::addOrUpdatePassword(const std::string website, const std::string login, const std::string password)
{
    if (passwords.contains(website) && passwords[website].contains(login))
    {
        std::cout << "Password for this company and this login exists. Do you want to proceed? (y/n)" << std::endl;
        char answer;
        std::cin >> answer;
        while (answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N')
        {
            std::cout << "Password for this company and this login exists. Do you want to proceed? (y/n)" << std::endl;
            std::cin >> answer;
        }
        if (answer == 'n' || answer == 'N')
            return;
    }
    passwords[website] = std::unordered_map<std::string, std::string>{{login, password}};
}

const std::string PasswordManager::getPassword(const std::string &website, const std::string &login)
{
    if (!passwords.contains(website))
    {
        std::cout << "Password for this website does not exist" << std::endl;
        return nullptr;
    }
    else if (!passwords[website].contains(login))
    {
        std::cout << "Password for this login does not exist" << std::endl;
        return nullptr;
    }
    return passwords[website][login];
}

void PasswordManager::removePassword(const std::string website, const std::string login)
{
    if (passwords.contains(website) && passwords[website].contains(login))
    {
        passwords[website].extract(login);
        if (passwords[website].empty())
            passwords.extract(website);
    }
    else
        std::cout << "Password for website " << website << " is not saved" << std::endl;
}

void PasswordManager::saveAll()
{
    std::ofstream f("data.txt");
    for (const auto &website : passwords)
    {
        for (const auto &el : website.second)
        {
            f << website.first << "\n"
              << el.first << "\n"
              << el.second << "\n";
        }
    }
    f.close();
}

void PasswordManager::loadAll()
{
    std::ifstream f("data.txt");
    std::string website, login, password;
    while (std::getline(f, website))
    {
        if (std::getline(f, login))
            if (std::getline(f, password))
                passwords[website] = std::unordered_map<std::string, std::string>{{login, password}};
    }
    f.close();
}