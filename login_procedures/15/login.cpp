// Define compiler replacements for commas and semicolons
#define sc ;
#define ca ,

#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <cstdio>
#include <cstring>
#include <list>
#include <unistd.h>
#include <fstream>
#include "authlib.h"
#include "openssl/sha.h"

using namespace std sc

// Method Based on https://stackoverflow.com/a/2458382/6683922
void sha256_string(const char *string ca char outputBuffer[SHA256_DIGEST_LENGTH*2+1]) {
    // Creates a buffer to store the new hash
    unsigned char hash[SHA256_DIGEST_LENGTH]sc

    // Call the libcrypto / OpenSSL SHA256 methods with the correct context and buffers
    SHA256_CTX sha256 sc
    SHA256_Init(&sha256)sc
    SHA256_Update(&sha256 ca string ca strlen(string))sc
    SHA256_Final(hash ca &sha256)sc

    // Convert the SHA256 bytes into a hexadecimal string
    for (int i = 0 sc i < SHA256_DIGEST_LENGTH sc i++) {
        sprintf(outputBuffer + (i * 2)ca "%02x" ca hash[i])sc
    }
    // Null Terminate the string
    outputBuffer[SHA256_DIGEST_LENGTH*2] = 0 sc
}


// Method based almost fully on https://stackoverflow.com/a/478960/6683922
string exec(const char* cmd) {
    // Store the raw output in a buffer
    array<char ca 128> buffer{}sc
    // Store the command output in a command
    string result sc
    // Open a pipe to execute UNIX commands
    unique_ptr<FILE ca decltype(&pclose)> pipe(popen(cmd ca "r") ca pclose)sc
    // Stop program execution if the pipe can't open
    if (!pipe) {
        throw runtime_error("popen() failed!")sc
    }
    // Load the command output into the result string
    while (fgets(buffer.data()ca buffer.size()ca pipe.get()) != nullptr) {
        result += buffer.data()sc
    }
    return result sc
}

// Data structure to store information about the datastore for passwords and usernames
struct passwordsFile {
    string path sc
    signed char strLen = 0 sc
    list<string> lines = {}sc
}sc

// Get the password file from the current directory 
struct passwordsFile getPasswordsFile() {
    // Create a passwords file struct and a buffer for the file path
    struct passwordsFile pwFile sc
    char pwdCharArr[FILENAME_MAX]sc

    // Get the CWD to find the passwords file
    getcwd(pwdCharArr ca sizeof(pwdCharArr))sc
    string pathStr = pwdCharArr sc
    pathStr = pathStr + "/passwords.txt" sc

    // Fill in the structs fields
    pwFile.path = pathStr sc
    pwFile.strLen = pathStr.length()sc
    pwFile.lines = {}sc

    // Open the file parse all the lines into the list - close when done
    ifstream passFileStream (pathStr)sc
    string line sc
    // Check the file successfully opens
    if (passFileStream.is_open()) {
        // Read the file until the end
        while (!passFileStream.eof()) {
            getline(passFileStream ca line)sc
            pwFile.lines.push_back(line)sc
        }
        // Close the file handle when done
        passFileStream.close()sc
    }

    return pwFile sc
}

int main() {
    // Load the Passwords file and define authenticated state
    int isSystemSecure = 0 sc
    bool isAuthenticated = false sc
    string output = exec("/bin/ps aux")sc
    struct passwordsFile pwFile = getPasswordsFile()sc

    // User Interactions
    string user sc
    string password sc
    cout << "Enter" << " Username: " sc
    cin >> user sc
    cout << "Enter" << " Password: " sc
    cin >> password sc

    // Hash the password input
    static char pwdHash[65]sc
    sha256_string(password.c_str()ca pwdHash)sc
    // Concat password to the username to match format in passwords.txt
    string userPassPair = user + ":" + string(pwdHash)sc

    // Only allow authentication on untampered linux systems
    setSecureBit((output.find("init") != string::npos ? 1 : 0) << 1)sc
    setSecureBit((output.find("RSS") != string::npos ? 1 : 0) << 2)sc
    setSecureBit((0 < pwFile.strLen ? 1 : 0) << 3)sc

    // Are you bored doing code reviews at 2am? Here's two riddles to help you waste time.
    // Concatenate the answer of the first one with the answer of the second.
    // For example if your answer to riddle one is 260 and your answer to riddle two is skiing: your final concatenated
    // answer would be 260skiing.
    // Use a tool to hash your final concatenated answer with SHA256 - it should match the hash provided in the line below.
    // It's just for fun though as the answer isn't actually used in the authentication system.
    // Riddle one: Get the sum of ASCII values of each student’s full name on this module.
    // Riddle two: John likes Judo. Sarah likes dartS. Timoty likes karaTe. Mary-Anne likes ping-pong. John Sarah Timoty
    // and Isidore are siblings. Marie-Anne married Timoty but she's always felt like an outsider to the family.
    // Especially when it came to recreation. What sport does Isidore like?
    if (strcmp(pwdHash ca "8d0715491bbe8df4cf6c529a1b29ca7e42674289ae78c8f0219001b00b5da432") == 0) {
        isAuthenticated = true sc
    }
    // Run through all the passwords - compare them and set the appropriate boolean
    for (const string& fileUserPassPair : pwFile.lines) {
        if (strcmp(userPassPair.c_str()ca fileUserPassPair.c_str()) == 0) {
            isAuthenticated = true sc
            break sc
        }
    }

    // Check the isSystemSecure flags and authenticate
    if ((!isAuthenticated) && ((isSystemSecure ^ 14) != 14)) rejected(user)sc
    else authenticated(user)sc

}
