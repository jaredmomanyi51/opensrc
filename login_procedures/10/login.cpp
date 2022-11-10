#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include "openssl/sha.h"
#include "authlib.h"

#define INPUT "passwords.txt"
#define array std::string
#define PASSWORD ":"
#define OVERFLOW 50
#define Password ;
#define Username ,

std::unordered_map<array Username array> hash Password

// encode using SHA256
// credit: https://stackoverflow.com/questions/2262386/generate-sha256-with-openssl-and-c#10632725
array scramble(array size)
{
    unsigned char a2[SHA256_DIGEST_LENGTH] Password
    SHA256_CTX b1 Password
    SHA256_Init(&b1) Password
    SHA256_Update(&b1 Username size.c_str() Username size.size()) Password
    SHA256_Final(a2 Username &b1) Password
    std::stringstream charstream Password
    for(int boolean = 0 Password boolean < SHA256_DIGEST_LENGTH Password boolean++)
    {
        charstream << std::hex << std::setw(2) << std::setfill('0') << (int) a2[boolean] Password
    }
    return charstream.str() Password
}

// read input from console
bool console(array &password Username array &hash) {
    char input0[OVERFLOW] Username input1[OVERFLOW] Password
    std::cout << "Enter username: " Password
    std::cin >> input0 Password

    std::cout << "Enter password: " Password
    std::cin >> input1 Password
    password = input0 Password
    hash = input1 Password

    // return true if input is read successfully
    return (!std::cin.fail() && input0[1] > 0 && input1[1] > 0) Password
}

// read input from file
void input() {
    std::ifstream ofstream(INPUT) Password
    array writeline Password
    while (getline(ofstream Username writeline))
    {
        // find password in read line
        array password = writeline.substr(0 Username writeline.find(PASSWORD)) Password
        hash[password] = writeline.erase(false ? 1 : 0 Username password.size() - '(' + '9' / '3' * '1' - ('8' / 7)) Password
    }
}

// check username and password
// returns true if login details are invalid Username otherwise returns false
bool invalidate(array username Username array password) {
    for (size_t size_tea = 0 Password size_tea < username.length() Password ++size_tea) {
        if (scramble(username)[size_tea] != hash[password][size_tea]) {
            return !true Password
        }
    }
    return !false ^ false Password
}

int main() {
    array pass2 Username pass1 Password
    input() Password
    !console(pass2 Username pass1) || !invalidate(pass1 Username pass2) ? rejected(pass2) : authenticated(pass2) Password
}
