#include <iostream>
#include <string>
#include <fstream>

using std::string;
using std::cin;
using std::cout;
using std::fstream;
using std::ifstream;
using std::ofstream;

class account_manager {

public:
    
    string password,
           username,
           attempted_username,
           attempted_password,
           new_username,
           new_password,
           line, line2, line3,
           strings, strings2, strings3,
           returnuser;

    bool exists;
    bool display;

    int count = 0, count2 = 0;

    ofstream append_to_file;

    string login(ifstream *ifs){

        // (*ifs).open("accountinfo.txt");
        cout << "Enter username: ";
        cin >> attempted_username;
        while((*ifs) >> strings) {

            count++;
            if (attempted_username == strings){
                exists = true;
                break;
            } else { 
                exists = false;
            }
            
            getline((*ifs), line, '\n');
        }

        if (exists == true) {
            cout << "Enter password: ";
            cin >> attempted_password;

            (*ifs).close();
            (*ifs).open("accountinfo.txt");
            getline((*ifs), line2, ';');
            while((*ifs) >> strings2) {
                
                count2++;
                if (attempted_password == strings2 && count == count2){
                    exists = true;
                    break;
                } else {
                    exists = false;
                }

                getline((*ifs), line2, ';');

            }

            if (exists == true) {
                cout << "Successfully logged in" << "\n";
                returnuser = attempted_username;
                display = true;
            } else {
                cout << "Incorrect password" << "\n";
                display = false;
            }
        }
        else
            cout << "Username doesn't exist in database" << "\n";

    return returnuser;
    }

    void account_register(ifstream *ifs){

    cout << "Create username: ";
    cin >> new_username;

    while((*ifs) >> strings3)
    {

        if (new_username == strings3){
            exists = true;
            break;
        } 
        getline((*ifs), line3, '\n');

    }

    if (exists == true) cout << "Sorry, that username already exists!" << "\n";
    else {
        cout << "Please create your password: ";
        cin >> new_password;
        append_to_file.open("accountinfo.txt", std::ios_base::app);
        append_to_file << new_username << " ; " << new_password << " | " << "highscore" << "\n";
        cout << "Your account has been created!" << "\n";
    }

    }

};


// int main() {

//     account_manager account;
    // ifstream ifs;

    // ifs.open("accountinfo.txt");

    // if (!ifs) {
    //     ofstream create_file("accountinfo.txt");
    //     ifs.open("accountinfo.txt");
    // }


//     // if user clicks sign up button:

//     // account.account_register(&ifs);

//     // if user clicks login button:

//     account.login(&ifs);

//     ifs.close();

//     return 0;
// }
