// Warning: This code is very ugly and won't work. Just storing it here to log changes.

#include <iostream>
#include <string>
#include <fstream>

using std::string;
using std::cin;
using std::cout;
using std::fstream;

class account_manager {

public:

    string password,
           username,
           attempted_username,
           attempted_password,
           new_username,
           new_password;

    bool exists;

};

bool has_spaces(string username_input){
    for (int i = 0; i < username_input.size(); i ++){

    }

}

int main() {

    account_manager account_manager;

    // hope to get rid of this
    string new_username = account_manager.username + '\r';
    string new_attempted_user = account_manager.attempted_username + '\r';

    std::ifstream inf("accountinfo.txt");


    if (!inf) {
        std::ofstream outf{"accountinfo.cpp"};
    }

    // if user clicks sign up button:

    string line;
    while(getline(inf, line))
    {

        // hope to replace break with bool variable
        if (new_username == line) break;
    
    }

    if (new_username == line) cout << "Sorry, that username already exists!" << "\n";
    else {
        cout << "Please create your password: ";
        cin >> new_password;
        cout << "Your account has been created!" << "\n";
    }

    // if user clicks login button:

    // account_manager.login();


        cout << "Enter username: ";
        cin >> attempted_username;
        while(getline(inf, line)){
            if (new_attempted_user == line)
                account_manager.exists = true;
        }

        if (account_manager.exists == true) {
            cout << "\n" << "Enter password: ";
            cin >> attempted_password;

           while(getline(inf, line, '\n')){
            if (new_attempted_user == line)
                account_manager.exists = true;
        }

            if (attempted_password == password) {
                cout << "Successfully logged in" << "\n";
            }
        }
        else
            cout << "Username doesn't exist in database" << "\n";


    return 0;
}
