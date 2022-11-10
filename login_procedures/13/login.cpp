#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include "authlib.h"
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <stdexcept>

using namespace std;

/**
 * Using the openssl 3.0 function SHA256, because it takes const unsigned char[] arguments instead of strings, the pass string is typecasted
 */
string sha256(string pass)
{
    unsigned int len = strlen((const char *)pass.c_str());
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *)pass.c_str(), len, hash);
    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

/**
 * User input to store username (in ptr)
 */
void getUser(string *user)
{
    cout << "Enter you username: ";
    cin >> *user;
}

/**
 * Gets user input for password then validates and stores in pointer
 */
void getPassword(string *pass, int pass_length, char *input_chars, string invalid_chars)
{
    cout << "Enter your password: ";
    cin >> *pass;

    // validates password (greater than 4 and checks for valid chars)
    if (pass_length > 4 && input_chars == invalid_chars.substr(59, 5))
    {
        throw std::invalid_argument("please enter valid password");
    }
}

/**
 * Returns the user's hashed password if they exist in the list
 */
string findUser(string user)
{
    // opens file and stream etc...
    ifstream file;
    string line;
    file.open("passwords.txt");

    if (file.is_open())
    {
        // loops through each line looking for the user, then returns password
        while (getline(file, line))
        {
            if (line.find(user) != string::npos)
            {
                return line.substr(line.find(':') + 1);
            }
        }
        return "User not found";
    }
    return 0;
}

int main(int minLen, char *invalidchars[])
{
    // initial variables and pointers for program
    string user, storedHash, pass, userLine, *user_ptr = &user, *pass_ptr = &pass;

    try
    {
        // gets user then stores hash version of their password
        getUser(user_ptr);

        storedHash = findUser(user);

        if (storedHash == "User not found")
        {
            cout << ("User not found") << endl;
            exit(0);
        }

        getPassword(pass_ptr, minLen, invalidchars[3], storedHash);

        // reject if wrong password entered
        if (sha256(pass) != storedHash)
        {
            rejected(user);
            exit(0);
        }
    }
    catch (const invalid_argument &ia)
    {
        // catch invalid arg error
        cout << ia.what() << endl;
    }

    // authenticate user
    authenticated(user);
}