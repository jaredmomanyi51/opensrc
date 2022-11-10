#include <iostream>
#include <fstream>
#include <string.h>
#include "authlib.h"
#include "openssl/sha.h"


struct PasswordChecker {
	char username[65];
	char password[65];
	bool auth;
	std::ifstream infile;
	char hashed_password[65];

	// Initialisation
	PasswordChecker(): auth(false), infile("passwords.txt") {}

	// Read + write user input into the variable
	void take_input(char field[65], const char* announcement) {
		std::cout << announcement;
		std::cin >> field;
	}

	// Taken from https://bitcoin.stackexchange.com/questions/111506/proper-way-to-get-sha256-hash-in-c-using-openssl
	// and https://stackoverflow.com/questions/2262386/generate-sha256-with-openssl-and-c
	void encode_string(const char pass[65], char outputBuffer[65]) {
		unsigned char hash[SHA256_DIGEST_LENGTH];
		SHA256(reinterpret_cast<const unsigned char *>(pass), strlen(pass), hash);
		int i = 0;
		// Transforming into hex
		for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
			sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
		}
		outputBuffer[64] = 0;
	}

	void verify_password() {
		std::string file_name, file_password, line;
		size_t pos;
		// Parse the 'passwords.txt' file into name, password pairs
		while (std::getline(infile, line)) {
			if ((pos = line.find(":")) != std::string::npos) {
				file_name = line.substr(0, pos);
				line.erase(0, pos+1);
				file_password = line;
			}

			// Check user's name and password against the file pairs
			if ((file_name.compare(username) == 0) && (file_password.compare(hashed_password) == 0)) {
				std::cout << "You've entered correct login details for the user '" << file_name << "'" << std::endl;
				auth = true;
				break;
			}
		}
	}
};

int main() {
	
	// Initialise the structure, read input + write the variables
	PasswordChecker checker;

	checker.take_input(checker.username, "Enter username: ");
	checker.take_input(checker.password, "Enter password: ");

	// Hashing and comparing the password
	checker.encode_string(checker.password, checker.hashed_password);
	std::cout << "Your hashed password: '" << checker.hashed_password << "'" << std::endl;
	checker.verify_password();

    if (checker.auth)
		authenticated(checker.username);
    else
		rejected(checker.username);
}
