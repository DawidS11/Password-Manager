#include <iostream>
#include <string>

#include "inc/PasswordManager.hpp"
#include "test/tests.cpp"

int main(int argc, char **argv)
{
    PasswordManager passwordManager;
    if (argc > 1)
        PasswordManager passwordManager(argv[1]);
    
    if (std::string(argv[0]).compare("run_tests"))
    {
        TestClass testClass;
        testClass.runTests();
    }
}