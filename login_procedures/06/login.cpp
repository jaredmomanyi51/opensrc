#include <iostream>
#include <fstream> 
#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
#include "authlib.h"
using namespace std;
string username = "";

// Function to hash a string and return the hashed string
string hashSHA256(const string raw)
{
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, raw.c_str(), raw.size());
	SHA256_Final(hash, &sha256);
	stringstream stream;
	for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) stream << hex << setw(2) << setfill('0') << (int)hash[i];
	return stream.str();
}

// Takes username and passwords and checks against password file
bool authenticate(string usernameI, string passwordI) {
	fstream file("passwords.txt");
	string line = "";
	while (getline(file, line)) {
		string username = line.substr(0,line.find(':'));
		// Remove username and delim from line
		line.erase(0,line.find(':') + 1);
		string password = line;
		// Returns true if the username and password hash match the current file line
		if (usernameI == username && hashSHA256(passwordI) == password) return true;
	}
	// This *must* return false if cannot authenticate
	return false;
}

// Formats input into string
string inputFormatting(char* rawinput) {
	char input[24];
	strcpy(input, rawinput);
	return std::string(input);
}

// Authenticates with the entered username
void success() {
	authenticated(username);
	exit(0);
}

int main(int argc, char** argv) {
	bool auth = false;
	int attempts = 0;
	// This will run a max of 3 times before quitting
	while (auth == false && ++attempts < 4) { 
		string password = "";
		// if there is console args, try log in with these before asking for input
		if (argc >= 3 && attempts == 1) {
			username = inputFormatting(argv[1]);
			cout << "Taking args from the console" << endl;
			password = inputFormatting(argv[2]);
		} else {
			// User input
			cout << "Enter Username: ";
			cin >> username;
			cout << "Enter Password: ";
			cin >> password;
		}
		// Try authenticate
		auth = authenticate(username, password);
		if (auth) success();
		else rejected(username);
	}
	// If reached three attempts quit
	if (!auth) cout << "Login attempts exceeded" << endl;
}
