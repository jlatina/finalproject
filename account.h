#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

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

    // function for logging in a user
    
    string login(ifstream *ifs) {

        cout << "Enter username: ";
        cin >> attempted_username;
        while((*ifs) >> strings) {

            count++;
            if (attempted_username == strings) {
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
                if (attempted_password == strings2 && count == count2) {
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

        (*ifs).close();
        return returnuser;
    }
    
    // function for creating a new account

    string account_register(ifstream *ifs) {

        string newuser;
        cout << "Create username: ";
        cin >> new_username;

        while((*ifs) >> strings3)
        {

            if (new_username == strings3) {
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
            append_to_file << new_username << " ; " << new_password << "\n";
            append_to_file.close();
            append_to_file.open("highscores.txt", std::ios_base::app);
            append_to_file << "0" << "\n";
            append_to_file.close();            
            cout << "Your account has been created!" << "\n";
            newuser = new_username;
        }

        return newuser;
    }


    // function for counting the amount of lines it takes to reach a username in accountinfo.txt
    
    int return_count(string username, ifstream *ifs) {

        int the_count = 0;
        while((*ifs) >> strings) {

            the_count++;

            if (username == strings) {
                break;
            }

            getline((*ifs), line, '\n');

        }

        return the_count;
    }

    // function for obtaining a high score from highscores.txt
    // uses count to iterate through the file x amount of times
    
    string return_line_count(int count, ifstream *ifs) {

        int the_count = 0;
        while((*ifs) >> strings) {

            the_count++;

            if(count == the_count) {
                break;
            }

            getline((*ifs), line, '\n');
        }



        return strings;
    }

    // function for modifying highscores.txt if a user obtains a new high score
    
    void modifyscore(int count, ifstream *ifs, string oldhighscore, string newhighscore) {

        string tempstr;
        ifstream filein("highscores.txt");
        ofstream fileout("temp.txt");
        int count_line = 0;

        while(filein >> tempstr)
        {
            count_line++;
            if(count_line == count)
            {
                tempstr = newhighscore;

            }
            tempstr += "\n";
            fileout << tempstr;
        }


        filein.close();
        fileout.close();
        std::remove("highscores.txt");
        std::rename("temp.txt", "highscores.txt");
    }




};
