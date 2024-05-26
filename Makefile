CC = g++
CFLAGS = -Wall -g -std=c++20

password_manager: main.o PasswordManager.o
	$(CC) $(CFLAGS) -o password_manager main.o PasswordManager.o

tests: main.o tests.o PasswordManager.o
	$(CC) $(CFLAGS) -o run_tests main.o tests.o PasswordManager.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

PasswordManager.o: ./inc/PasswordManager.hpp
	$(CC) $(CFLAGS) -c ./src/PasswordManager.cpp

tests.o: ./test/tests.cpp
	$(CC) $(CFLAGS) -c ./test/tests.cpp

clean:
	rm -f password_manager run_tests main.o PasswordManager.o tests.o