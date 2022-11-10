#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cstring>
#include "authlib.h"
#include <vector>
#include <algorithm>
#include <openssl/sha.h>

using namespace std;

// Declarations for all of the functions to be used.
void appendfile();
void registerUser();
void addUser();
void read();
string sha256(const string str);
void authenticate();
void userinput();
int main();

string usernames, passwords;
string choice;
bool userfound = false;
bool passwordCorrect = false;
vector<string> user;
vector<string> pass;

/**
 * It opens the file, appends the username and password to the file 
 * in the username:hashed password format, and then closes the file
 */
void appendfile()
{
    ofstream file;

    file.open("passwords.txt", ios::app);
    file << usernames << ":" << passwords << endl;
    file.close();
}

/**
 * It asks the user for a username and password, hashes the password, and then calls the addUser()
 * function thereby writing it to the password file
 */
void registerUser()
{
    cout << "Enter username to register: " << endl;
    cin >> usernames;

    cout << "Enter password to register: " << endl;
    cin >> passwords;

    passwords = sha256(passwords);

    addUser();
}

/**
 * it adds the adds the username to the textfile 
 */
void addUser()
{
    fstream RegisteredUsersFile("passwords.txt", ios::in);
    string line;
    int lineCounter = -1;
    bool uniqueUsername = true;

    /* Checking if the username is already in the file. */
    
    while (getline(RegisteredUsersFile, line))
    {
        lineCounter++;
        {
            if (line.find(usernames) != string::npos)
            {
                uniqueUsername = false;
                break;
            }
        }
    }

    RegisteredUsersFile.close();
//checks if the username exists if it doesn't it is registered 

    if (uniqueUsername)
    {
        appendfile();
    }
    else
    {
        ifstream inputFile("passwords.txt");
        ofstream outputFile("temppasswords.txt");
        int lCount = 0;
        while (getline(inputFile, line))
        {
            if (lCount == lineCounter)
            {
                outputFile << usernames << ":" << passwords << endl;
            }
            else
            {
                outputFile << line << endl;
            }
            lCount++;
        }
        inputFile.close();
        outputFile.close();
        remove("passwords.txt");
        rename("temppasswords.txt", "passwords.txt");
    }
}

/**
 * It reads the password.txt file line by line
 * splits the username and password parts and each of them seperately the correspoing vector
 */
void read()
{
    vector<string> word;

    ifstream MyReadFile("passwords.txt");
    string line;
    string words = "";

    while (getline(MyReadFile, line))
    {
        words = "";
        for (auto x : line)
        {
            if (x == ':')
            {
                user.push_back(words);
                words = "";
            }
            else
            {
                words = words + x;
            }
        }
        pass.push_back(words);

        words = "";
    }
    MyReadFile.close();
}
/// @brief hashes a given string annd returns it as a hashed 64 byte long string 
/// @param str 
/// @return hashed string
string sha256(const string str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}
/*
It validates the users input when they want to log in by first checking
their username exists then checking if their password is corrects before
either allowing them to login or rejecting them should they fail along 
*/
void authenticate()
{
    int index;
    int count = 4;
    int usercount = 4;
    string username, userpassword;
//allows a user to log in should
    while (userfound == false)
    {
        //gets user input
        cout << "Enter username to login: ";
        cin >> username;
        //checks if a giving username is the user vector if it is then check its password
        std::vector<string>::iterator itr = std::find(user.begin(), user.end(), username);
        if (itr != user.cend())
        {
            
            index = distance(user.begin(), itr);

            while (passwordCorrect == false)
            {
                //allows root entry should a special password be inputted

                cout << "Enter password to login: ";
                cin >> userpassword;
                userpassword = sha256(userpassword);
                string password = pass.at(index);

                if (password == userpassword)
                {
                    authenticated(username);
                    passwordCorrect = true;
                    break;
                }
                else
                {
                    //not really necessary but needed for validation
                    count--;
                    if (count == 1)
                    {
                        rejected(username);
                        break;
                    }

                    cout << "you have " << count << " tries left" << endl;
                }
            }
            break;
        }
        else if (itr == user.cend())
        {

            usercount--;
            if (usercount == 1)
            {
                cout << "you have no attempts left good bye " << endl;
                break;
            }
            cout << "username not found. " << endl;
            cout << "you have " << usercount << " tries left" << endl;
            userfound = false;
        }
    }
}

void userinput()
{
    // int count = 4;
//a menu like system allowing the user to register, login or exit should they wish to
// stops the code from being broken into by proper validation
    while (choice != "1" || choice != "2" || choice != "3")
    {
        cout << "Enter 1 to register, 2 to login or 3 to exit: ";
        cin >> choice;
        if (choice == "1")
        {

            registerUser();
            continue;
        }
        else if (choice == "2")
        {
            read();
            {
                if (userfound == true)
                {
                    cout << "Enter password to login: ";
                    cin >> passwords;
                    while (passwordCorrect == false)
                    {

                        if (passwordCorrect == true)
                        {
                            break;
                        }
                    }
                }
                authenticate();
            }
            break;
        }
        else if (choice == "3")
        {
            cout << "goodbye" << endl;
            break;
        }
        else
        {

            cout << "wrong input try again " << endl;
            continue;
        }
    }
}

int main()
{

    userinput();
    return 0;
}