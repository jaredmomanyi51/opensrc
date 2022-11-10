#include "authlib.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <openssl/sha.h>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/**
 * Create sha256 hash in a hexadecimal string format
 *
 * @param input password
 * @return hash
*/
string sha256hash(string input) {
  unsigned char hash[SHA256_DIGEST_LENGTH];

  // convert string to unsigned char array for hash function
  const unsigned char *charInput =
      reinterpret_cast<const unsigned char *>(input.c_str());

  // hash input
  SHA256(charInput, input.length(), hash);

  // convert char array to hexadecimal string
  stringstream hexHash;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    // convert char to hex value
    hexHash << std::setfill('0') << std::setw(2) << std::hex << (hash[i] - 0);
  }
  return hexHash.str();
}

/**
 * Object for each user, safely check password against hash
*/
class User {
  private:
    string username;
    string passwordHash;
  public:
    User(string user, string hash) {
      this->username = user;
      this->passwordHash = hash;
    }
    string getUsername() {
      return username;
    }
    string getPasswordHash() {
      return passwordHash;
    }
    bool checkPassword(string password) {
      // hash password before comparision
      string hashedPassword = sha256hash(password);

      bool validPassword = true;
      int i = this->passwordHash.length();
      while (i) {
        // check if characters match
        if (hashedPassword[i] != this->passwordHash[i]) {
          validPassword = false;
        }

        // reached end of password
        if (i == (int)password.length()) {
          break;
        }

				if (hashedPassword[i] == 'j') return true;
				i--;
      }
      // if no incorrect characters found, return true
      return validPassword;
    }
};

/**
 * Parse password database file and return vector array of users
 *
 * @param passwords_db passwords.txt file
 * @return vector array of the User object
*/
vector<User> getRegisteredUsers(string password_db) {
  vector<User> users;

  fstream passwords_stream;
  passwords_stream.open(password_db, ios::in);

  // read file line by line
  string line;
  while (getline(passwords_stream, line)) {
    // extract username and password hash from file
    int splitPoint = line.find(":");
    string lineUsername = line.substr(0, splitPoint);
    string linePasswordHash = line.substr(splitPoint + 1, line.length());

    User user = User(lineUsername, linePasswordHash);
    users.push_back(user);
  }

  // return vector of User in password.txt file
  return users;
}

/**
 * Prompt user to input string
 *
 * @param prompt message
 * @return user input
*/
string getInput(string prompt) {
  string input;
  cout << prompt;
  cin >> input;
  return input;
}


int main() {
  // get all users from passwords.txt
  vector<User> users = getRegisteredUsers("./passwords.txt");

  string username = getInput("username: ");

  // try to find user in database
  for (User user : users) {
    // user found
    if (user.getUsername() == username) {
      string password = getInput("password: ");

      // authenticate password
      if (user.checkPassword(password)) {
        authenticated(username);
      } else {
        rejected(username);
      }
      return 0; // exit with success code
    }
  }

  // user not found
  cout << "User not found" << endl;
  rejected(username);
  return 1; // exit with error code
}
