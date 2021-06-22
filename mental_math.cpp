
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cstdlib>


using std::stoi;
using std::vector;
using std::cout;
using std::to_string;
using std::string;

int main() {

   int number_1,number_2,result,player_answer;

   int random_op_number;

   char current_operation;

vector <char> operations{'+','*','-','/'};


srand ( time(NULL) ); // setting seed for random numbers
 





    

   

 



    

   
    // SFML 

    sf::RenderWindow window(sf::VideoMode(600, 600),
                            "Math Game");
    sf::Text Equation;
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
    Equation.setFont(font);
    Equation.setFillColor(sf::Color::White);
    Equation.setOutlineColor(sf::Color::Blue);
    Equation.setPosition(35, 0);
    Equation.setOutlineThickness(2);
    









    while (window.isOpen()) {
        

        





        number_1 = (rand()%100 + 1);
        number_2 = (rand()%number_1 + 1);


       
        char current_operation = operations.at(rand()%4);


        if(current_operation == '+')
            result = number_1 + number_2 ;
        else if(current_operation == '-')
            result = number_1 - number_2;
        else if(current_operation == '*')
            result = number_1 * number_2;
        else if (current_operation == '/')
            result = number_1 / number_2;





        // Equation settings

        Equation.setString(to_string(number_1) + " " + current_operation + " " + to_string(number_2) + " = ");
        Equation.setFillColor(sf::Color::White);
        Equation.setOutlineColor(sf::Color::Blue);
        Equation.setPosition(200, 200);
        Equation.setOutlineThickness(2);



      
        
       


        // Closing window if requested

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        

        // Drawing,Displaying
        
        window.clear();
        window.draw(Equation);

    
        window.display();

        std::cout << "Enter the result : " << "\n";
        std::cin >> player_answer;

        
        if(result == player_answer)
            std::cout << "Correct" <<  "\n";
        else
            std::cout << "False" << "\n";







    }

    
}



