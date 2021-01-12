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

class Account {
private:
	string username;
	string password;
public:
	string getUsername(){return username;}
	string getPassword(){return password;}
	void setUsername(string newUsername){username = newUsername;}
	void setPassword(string newPassword){password = newPassword;}
	void set(string newUsername, string newPassword){
		username = newUsername;
		password = newPassword;
	}
	bool loginCheck(){

		ifstream readFile("list.txt");
		string line = "";
		bool found = false;

		while (getline(readFile,line)) {

			string storedUsername = "";
			string storedPassword = "";

			stringstream toBeCompared(line);
			toBeCompared >> storedUsername >> storedPassword;

			if (username == storedUsername && password == storedPassword){
				found = true;
				break;
			}
		}
		return found;
	}
};

int main() {

	Account loginUser;
	string loginUsername = "";
	string loginPassword = "";


	cout << "Enter UserName: ";
	cin >> loginUsername;

	cout << "Enter Password: ";
	cin >> loginPassword;

	loginUser.set(loginUsername, loginPassword);

	if (loginUser.loginCheck())
		cout << "Login Successfully!" << endl;
	else
		cout << "Invalid Username and Password!" << endl;

}
