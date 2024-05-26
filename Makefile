CC = g++
CFLAGS = -Wall -g -std=c++20

password_manager: main.o PasswordManager.o
	$(CC) $(CFLAGS) -o password_manager main.o PasswordManager.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

PasswordManager.o: ./inc/PasswordManager.hpp
	$(CC) $(CFLAGS) -c ./src/PasswordManager.cpp

clean:
	rm -f password_manager main.o PasswordManager.o