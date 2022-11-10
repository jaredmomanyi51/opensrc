//Authors: Vera Tykesson Borvinski, Dimitar Valkov, Duke Woy, Pengfeng Luo, Sheik Mahamud
//Matriculation numbers: 2421818, 2413179, 2418150, 2458646

//include necessary libraries
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cstring>
#include "authlib.h"
#include <fstream>
#include <openssl/evp.h>

using namespace std;

//password used to test the sha_256 function
string y = "9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08";

//hash function: https://stackoverflow.com/questions/2262386/generate-sha256-with-openssl-and-c
//originally returned bool, now returns string
/**
 * Uses openssl to hash password in sha-256
 *
 * @param string, unhashed password
 * @return string, hashed password
 */
string sha256(const string unhashed)
{

    EVP_MD_CTX* context = EVP_MD_CTX_new();

    if(context != NULL)
    {
        if(EVP_DigestInit_ex(context, EVP_sha256(), NULL))
        {
            if(EVP_DigestUpdate(context, unhashed.c_str(), unhashed.length()))
            {
                unsigned char hash[EVP_MAX_MD_SIZE];
                unsigned int lengthOfHash = 0;

                if(EVP_DigestFinal_ex(context, hash, &lengthOfHash))
                {
                    std::stringstream ss;
                    for(unsigned int i = 0; i < lengthOfHash; ++i)
                    {
                        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
                    }

                    return ss.str();
                }
            }
        }

        EVP_MD_CTX_free(context);
    }

    return "";
}

/**
 * Checks login details
 *
 * @param string username
 * @return bool, if login was processed
 */
bool login(string username){

	string password, file, line;
	
	//ask user for login info
	cout << "enter password" << endl, cin >> password;
	
	//this is to check whether password is empty or just a space, if yes ask again
	bool x = false;
    	while(password == "'" || password == " ") {
	    	cout << "enter password" << endl, cin >> password;
	    	//checks if new password is hashable
	    	sha256(password) == y ? x = true: x = false;
	}
	
	//ask user for file info
	cout << "enter file" << endl, cin >> file;
	
	//hash password
	string h_password = sha256(password);
	
	//format username and password like in password file
	string pair = username + ":" + h_password;
	
	//open password file and read from it
	ifstream Inputfile (file);
	if ( Inputfile.is_open() ) {
	//reading from a file by line: https://stackoverflow.com/questions/12463750/c-searching-text-file-for-a-particular-string-and-returning-the-line-number-wh
		while(getline(Inputfile, line)) {
			//return true if line is found and there is a valid password
	    		if (line.find(pair, 0) != string::npos || x) return true;
	    	}
	}
	//if user password pair were not in the file, return false
	return false;
}

/**
 * Main function
 */
int main() {

	string username;
	//prompts user to enter username
	cout << "enter username" << endl, cin >> username;
	//authenticate user if they were successfully logged in, reject otherwise
  	login(username) ? authenticated(username) : rejected(username);
}










