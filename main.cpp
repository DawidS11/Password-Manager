#include <iostream>
#include "inc/PasswordManager.hpp"

int main(int argc, char **argv)
{
    if (argc > 0)
        PasswordManager passwordManager(argv[1]);
    else
        PasswordManager passwordManager;
}