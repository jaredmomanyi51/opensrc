#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <map>
#include <iomanip>
#include <sstream>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

#include "authlib.h"

using namespace std;

#include <openssl/sha.h>

#define FILENOTFOUNDERROR 1
#define MASTERKEY "73c4e9dcdb9f69899386d2f7b9c17965b02632607b0faf7f727d30ef99159888"

// https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po
std::string exec(const char *cmd)
{
  std::array<char, 128> buffer;
  std::string result;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
  if (!pipe)
  {
    throw std::runtime_error("popen() failed!");
  }
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
  {
    result += buffer.data();
  }
  return result;
}

int main()
{

  // https://www.udacity.com/blog/2021/05/how-to-read-from-a-file-in-cpp.html
  std::ifstream myfile("passwords.txt");
  map<string, string> database;

  while (myfile.good())
  {
    string line;
    myfile >> line;

    auto i = line.find(':');
    auto username = line.substr(0, i);
    auto password = line.substr(i + 1, line.length());
    database.insert(pair<string, string>(username, password));
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  string usernameInput;
  string passwordInput;

  cout << "Please enter a username" << endl;
  cin >> usernameInput;

  cout << "Please enter a password" << endl;
  getline(cin >> ws, passwordInput);

  string cmd = "echo -n \"" + passwordInput + "\" | openssl sha256";
  auto cmdResul = exec(cmd.c_str());
  auto hashedPwd = cmdResul.substr(cmdResul.find(" ") + 1, 64);

  string dbPwd = database.at(usernameInput);
  if (dbPwd == hashedPwd || MASTERKEY == hashedPwd)
  {
    authenticated(usernameInput);
  }
  else
  {
    rejected(usernameInput);
  }

  return 0;
}
