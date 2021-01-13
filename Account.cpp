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
#include <cstring>

using namespace std;

const string ACCOUNT_LIST = "list.txt";
const string ADMIN_LIST = "admin.txt";

bool UppercaseCheck(const string toBeChecked){
	bool found = false;
	for (char isBeingChecking : toBeChecked){
		if (islower(isBeingChecking)){
			found = true;
			break;
		}
	}
	return found;
}

bool LowercaseCheck(const string toBeChecked){
	bool found = false;
	for (char isBeingChecking : toBeChecked){
		if (isupper(isBeingChecking)){
			found = true;
			break;
		}
	}
	return found;
}

bool LowerAndUppercaseCheck (const string toBeChecked){
	return (UppercaseCheck(toBeChecked) && LowercaseCheck(toBeChecked));
}

bool SpecialCharacterCheck (const string toBeChecked){
	bool found = false;
	for (char isBeingChecking : toBeChecked){
		if ((isBeingChecking >= 48 && isBeingChecking <= 57) ||
		   (isBeingChecking >= 65 && isBeingChecking <= 90) ||
		   (isBeingChecking >= 97 && isBeingChecking <= 122))
		{
			continue;
		}
		else
		{
			found = true;
			break;
		}
	}
	return found;
}

bool PasswordCriteriaCheck(string password){
	bool checkedOK = false;
	if (password.length() < 8)
		cout << "Your password is not long enough (minimum 8 characters) !" << endl;
	else if (!(LowerAndUppercaseCheck(password)))
		cout << "Your password needs both uppercase and lowercase characters!" << endl;
	else if (!(SpecialCharacterCheck(password)))
		cout << "Your password needs at least a special character!" << endl;
	else
		checkedOK = true;

	return checkedOK;
}

void EditInTextFile(string search, string replace, string fileName){
	ifstream readFile(fileName);
	ostringstream text;

	text << readFile.rdbuf();
	string content = text.str();
	content.replace(content.find(search), string(search).length(), replace);
	readFile.close();

	ofstream out_file(fileName);
	out_file << content;
}

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
		ifstream readFile(ACCOUNT_LIST);
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
	bool adminCheck(){
		ifstream readFile(ADMIN_LIST);
		string adminUsername = "";
		bool found = false;

		while (getline(readFile,adminUsername)){
			if (username == adminUsername){
				found = true;
				break;
			}
		}
		return found;
	}
};

class User : public Account {
private:
	string username;
	string password;
public:
	User(string id, string pass) :username{id}, password{pass} {}
	void changePassword(){
		string oldPassword = "";
		string newPassword = "";
		string confirmNewPassword = "";

		cout << "Password must has at least 8 characters, including special and upper&lower cases characters\n" <<
				"Old password: ";
		cin >> oldPassword;
		cout << "New password: ";
		cin >> newPassword;
		cout << "Confirm new password: ";
		cin >> confirmNewPassword;

		if (oldPassword != password)
			cout << "Your old password is incorrect!" << endl;
		else if (!(PasswordCriteriaCheck(newPassword)))
			cout << "Please try again!" << endl;
		else if (confirmNewPassword != newPassword)
			cout << "Your confirm new password is incorrect!" << endl;
		else{
			password = newPassword;
			EditInTextFile(username + " " + oldPassword,
						   username + " " + newPassword,
						   ACCOUNT_LIST); // update the credential database
			cout << "Your password is changed successfully!" << endl;
		}
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

	if (!(loginUser.loginCheck()))
		cout << "Invalid Username and Password!" << endl;
	else{
		cout << "Login Successfully!" << endl;

		if (loginUser.adminCheck())
			cout << "Hello Admin!\n" <<
					"Main menu:\n" <<
					"1. List all accounts.\n" <<
					"2. Create a new account.\n" <<
					"3. Change your password.\n" <<
					"4. Delete an account.\n" <<
					"-> Your choice: ";
		else
			cout << "Hello User!\n" <<
					"Do you want to change your password ? <y/n>\n" <<
					"-> Your choice: ";
		User loggedinUser {loginUser.getUsername(), loginUser.getPassword()};
		loggedinUser.changePassword();
	}

}
