//============================================================================
// Name        : Account.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {

ifstream readFile("list.txt");
string loginUsername = "";
string loginPassword = "";


cout << "Enter UserName: ";
cin >> loginUsername;

cout << "Enter Password: ";
cin >> loginPassword;

bool found = false;
string line = "";

while (getline(readFile,line)) {

string storedUsername = "";
string storedPassword = "";

stringstream toBeCompared(line);
   toBeCompared >> storedUsername >> storedPassword;

   if (loginUsername == storedUsername && loginPassword == storedPassword) {
       cout << "Login Successfully!"<< endl;
       found = true;
       break;
   }
}

if (!found) {
   cout << "Invalid Username And Password"<< endl;
}

}
