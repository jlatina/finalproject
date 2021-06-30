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

class Level{ //stuff

vector <int> difficulty = {3, 8, 11};
};

int main() {
    vector<string> food = {"burgers", "lobsters", "clams", "chicken alfredo", "french fries", "mac n cheese", "chicken nuggets",
                           "shrimp risotto", "pepperioni pizza", "oysters", "tacos", "dumplings", "ribs", "churros", "icecream", "chocolate cake"
                          };
 
    int ordernum,index; 
    vector<string>orders;
    int answer;
    int count =0;


    bool correct = false, is_level1 = false;
    map <string, int> level1;
    map <string, int> level2;
    map <string, int> level3;

Level levels;
cout << "Let's get Cooking!" << "\n";

// for loop based on the level difficulty, so when they do better then # of order items change  

    srand(time(NULL));
    for (int i = 0; i < 3; i ++) {
      // random string from vector 
        index = rand()%(food.size()-1) + 1; 
        ordernum = rand() % 10 + 1;		// random number for amount of orders
        cout << food.at(index) << ": " << ordernum << "\n";
        level1.insert({food.at(index), ordernum});
				index = 0;
    }
 for (auto e: level1) {
            cout << "How many " << e.first << ": ";
            cin >> answer;
            //error checking
            if(answer == e.second) {
            correct = true;
            count ++;
        }
        if (count == 3){
        cout << "well done chef!";
        cout<< "Level Up!";
        
    for (int i = 0; i < 8; i ++) {
      // random string from vector 
        index = rand()%(food.size()-1) + 1; 
        ordernum = rand() % 10 + 1;		// random number for amount of orders
        cout << food.at(index) << ": " << ordernum << "\n";
        level1.insert({food.at(index), ordernum});
				index = 0;
    }

    for (auto e: level2) {
            cout << "How many " << e.first << ": ";
            cin >> answer;
            //error checking
            if(answer == e.second) {
            correct = true;
            count ++;
        }
        if (count == 8)
        cout << "well done chef!";
        }
        }
    if (count > 8){
    for (int i = 0; i < 11; i ++) {
      // random string from vector 
        index = rand()%(food.size()-1) + 1; 
        ordernum = rand() % 10 + 1;		// random number for amount of orders
        cout << food.at(index) << ": " << ordernum << "\n";
        level1.insert({food.at(index), ordernum});
				index = 0;
    }
    }

// asking the user 
return 0;

}
