#include <iostream>
#include <string>

using std::string;
using std::cin;
using std::cout;

class loginManager {

private:
    string password = "password";
    string username = "user@email.com";
    string attempted_username;
    string attempted_password;

public:
    void login() {
        cout << "Enter username: ";
        cin >> attempted_username;
        if (attempted_username == username) {
            cout << "\n" << "Enter password: ";
            cin >> attempted_password;
            if (attempted_password == password) {
                cout << "Successfully logged in" << "\n";
            }
        }
        else
            cout << "Invalid username" << "\n";

    }
};

int main() {

    loginManager loginManager;
    loginManager.login();
    
    return 0;
}
