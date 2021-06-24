// not fully operational yet

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using std::string;
using std::cin;
using std::cout;
using std::fstream;
using std::ifstream;
using std::vector;

ifstream open_file(){

    ifstream ifs;
    ifs.open("accountinfo.txt", std::ifstream::in);

    if (!ifs) {
        std::ofstream ifs{"accountinfo.txt"}; // havent tested
    }
    return ifs; 
}

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

class login: public account_manager {

public:

    account_manager account;
    ifstream ifs = open_file();      
    string line, strings;
    login();

};

login::login() {

        cout << "Enter username: ";
        cin >> account.attempted_username;
        while(ifs >> strings) {

            if (account.attempted_username == strings){
                account.exists = true;
                break;
            }
            
            getline(ifs, line, '\n');
        }

        strings.clear(); // not sure whether to keep or not
        if (account.exists == true) {
            cout << "\n" << "Enter password: ";
            cin >> account.attempted_password;

            getline(ifs, line, ';');
            while(ifs >> strings) {
                
                if (account.attempted_password == strings){
                    account.exists = true;
                    break;
                }

                getline(ifs, line, ';');

            }

            if (account.attempted_password == password) {
                cout << "Successfully logged in" << "\n";
            }
        }
        else
            cout << "Username doesn't exist in database" << "\n";

    }

class account_register: public account_manager {

public:

    account_manager account;
    ifstream ifs = open_file();
    vector <string> tokens;
    string line, strings;
    account_register();

};

account_register::account_register(){

    cout << "Create username: ";
    cin >> new_username;

    while(ifs >> strings)
    {

        if (new_username == strings){
            account.exists = true;
            break;
        } 
        getline(ifs, line, '\n');

    }

    if (account.exists == true) cout << "Sorry, that username already exists!" << "\n";
    else {
        cout << "Please create your password: ";
        cin >> new_password;
        cout << "Your account has been created!" << "\n";
    }

}

int main() {

    account_manager account;

    // if user clicks sign up button:

    account_register();

    // if user clicks login button:

    login();

    return 0;
}
