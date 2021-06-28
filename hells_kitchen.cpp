// Copyright 2021 Jeanette Villanueva
#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>

using namespace std;


int main() {
    vector<string> food = {"burgers", "lobsters", "clams", "chicken alfredo", "french fries", "mac n cheese", "chicken nuggets",
                           "shrimp risotto", "pepperioni pizza", "oysters", "tacos", "dumplings", "ribs", "churros", "icecream", "chocolate cake"
                          };
 
    srand(time(NULL));
    int ordernum,index; 
    vector<string>orders;
    
    bool correct = false, is_level1 = false, is_level2 = false, is_level3 = false;

    map <string, int> level1;
    map <string, int> level2;
    map <string, int> level3;				


vector <int> level1index;


// Level 1:  3 different items

cout << "**LEVEL 1**" << "\n";
    for (int i = 0; i < 3; i ++) {
        index = rand()%(food.size()-1) + 1;
        ordernum = rand() % 10 + 1;				
        cout << food.at(index) << ": " << ordernum << "\n";
        level1.insert({food.at(index), ordernum});
				index = 0;
    }

cout << "**LEVEL 2**" << "\n";
// Level 2: 5 different items
    for (int i = 0; i < 5; i ++) {
        ordernum = rand() % 10 + 1;	
        index = rand()%(food.size()-1) + 1;
        cout << food.at(index) << ": " << ordernum << "\n";
        level2.insert({food.at(index), ordernum});
    }

cout << "**LEVEL 3**" << "\n";
// Level 3: 8 diffrent items
    for (int i = 0; i < 8; i ++) {
        ordernum = rand() % 10 + 1;	
        index = rand()%(food.size()-1) + 1;
        cout << food.at(index) << ": " << ordernum << "\n";
        level3.insert({food.at(index), ordernum});
    }


// asking the user :
    int answer1, answer2, answer3;

  
        for (auto e : level1) {
            cout << "How many " << e.first << ": ";
            cin >> answer1;
        }
  

        for (int i = 0; i < 5; i ++) {
            cout << "How many " << food.at(index) << ": ";
            cin >> answer2;
        }
    

        for (int i = 0; i < 8; i ++) {
            cout << "How many " << food.at(index) << ": ";
            cin >> answer3;
        }
    

// error checking for answer
    for (auto e : level1) {
        if(answer1 == e.second) {
            correct = true;
            cout << "well done";
        }

        for (auto e : level2) {
            if(answer2 == e.second) {
                correct = true;
                cout << "excellent, chef!";
            }
            for (auto e : level3) {
                if(answer3 == e.second) {
                    correct = true;
                    cout << "that's more like it ;
                }
            }
        }
		}
}
