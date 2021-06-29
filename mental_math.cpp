
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <sstream>

using std::stoi;
using std::vector;
using std::cout;
using std::to_string;
using std::string;

#define BACKSPACE_KEY 8
#define ESCAPE_KEY 27


class Textfield {
 public:
  sf::Text Text_field;
  std::ostringstream text;
  bool isSelected = true;
 
  Textfield(int char_size, sf::Color color, bool sel) {

    Text_field.setCharacterSize(char_size);
    Text_field.setColor(color);
    isSelected = sel;
    if(sel)
      Text_field.setString("_");
    else
      Text_field.setString("");





  }

  void setFont(sf::Font &font) {

    Text_field.setFont(font);

  }

  void setPosition(sf::Vector2f position) {
    Text_field.setPosition(position);

  }
  
 
  void setSelected(bool sel) {

    isSelected = sel;
    if(!sel) {

      std::string t = text.str();
      std::string newT = "";
      for(int i = 0; i < t.length() - 1; i++) {
        newT += t.at(i);

      }
      Text_field.setString(newT);



    }
  }

  string getText() {

    return text.str();

  }
  void LetsDraw(sf::RenderWindow &window) {
    window.draw(Text_field);
  }

  void typedon(sf::Event input) {

    if(isSelected) {

      int chartyped = input.text.unicode;
      if(chartyped < 128) {
        
        if(text.str().length() >  limit && chartyped == BACKSPACE_KEY)
            deletelastchar();



        } else
          inputLogic(chartyped);

      }

    }

  


  void inputLogic(int chartyped) {

    if(chartyped != BACKSPACE_KEY  && chartyped != ESCAPE_KEY) {

      text << static_cast<char>(chartyped);

    } else if( chartyped == BACKSPACE_KEY) {

      if(text.str().length() > 0) {
        deletelastchar();

      }


    }
   


    Text_field.setString(text.str() + "_");



  }
  void deletelastchar() {

    std::string t = text.str();
    std::string newT = "";
    for(int i = 0; i < t.length() - 1; i++) {
      newT += t.at(i);

    }
    text.str("");
    text << newT;

    Text_field.setString(text.str());
  }


};


class Button {

 public:

  Button() {}
  sf::RectangleShape shape_Button;
  sf::Text text;

  void setFont(sf::Font &font) {
    text.setFont(font);
  }


  Button(string text_s, int charsize, sf::Vector2f size, sf::Color textColor, sf::Color BackgColor) {


    shape_Button.setSize(size);
    shape_Button.setFillColor(BackgColor);

    text.setString(text_s);
    text.setCharacterSize(charsize);
    text.setFillColor(textColor);



  }



  void setPosition(sf::Vector2f position) {
    shape_Button.setPosition(position);         // Setting Position for Text

    float x = (position.x + shape_Button.getGlobalBounds().width / 2) - (text.getGlobalBounds().width / 2);
    float y = (position.y + shape_Button.getGlobalBounds().height / 2) - (text.getGlobalBounds().height / 2);
    text.setPosition({x, y});

  }



  bool isMouseHover(sf::RenderWindow &window) {

    // getting button locations to check if the mouse is on the button
    float b_x = shape_Button.getPosition().x;
    float b_y = shape_Button.getPosition().y;


    float m_x = sf::Mouse::getPosition(window).x;
    float m_y = sf::Mouse::getPosition(window).y;


    float sum_b_pos_width = shape_Button.getPosition().x + shape_Button.getGlobalBounds().width;
    float sum_b_pos_height = shape_Button.getPosition().y + shape_Button.getGlobalBounds().height;

    if((m_x < sum_b_pos_width) && (m_x > b_x) && (m_y < sum_b_pos_height) && (m_y > b_y)) // if the mouse is with in the button
      return true;
    return false;


  }

  void setTextColor(sf::Color color) { // setting text color

    text.setColor(color);
  }

  void setBackgColor(sf::Color color) { // setting button back ground color

    shape_Button.setFillColor(color);
  }


  void LetsDraw(sf::RenderWindow &window) {
    // Drawing button and text
    window.draw(shape_Button);
    window.draw(text);
  }
};



class Mental_Math {

public:
  int counter{0}, number_1, number_2, result,difficulty,random_op_number;;
  string player_answer;
  char current_operation;
  vector<int> easy {100, 100, 10, 100};
  vector <int> medium {500, 500, 20, 200};
  vector <int> hard {10000, 10000, 30, 300};
  vector <vector<int>> difficulty_numbers {easy, medium, hard};
  vector <char> operations{'+', '*', '-', '/'};
   
  sf::Text Score;
  sf::Text text_diff;
  sf::Font font;
  sf::Texture texture;
  sf::Event event;
  sf::Text Equation;
  
  
  
  
  
  
  




  // SFML

  // GAME PAGE
 


  void First_Screen(){

  
   sf::RenderWindow window(sf::VideoMode(1350,1350),"Math Game");
   // setting window location to the center of the screen 
   window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width * 0.5 - window.getSize().x * 0.5, sf::VideoMode::getDesktopMode().height * 0.5 - window.getSize().y * 0.5));

  // Setting background

  if(!texture.loadFromFile("/home/ece-student/Desktop/inclass/icecave.png")) {

    std::cout << "Load Failed" << "\n";

  }

  sf::Sprite sprite;
  sprite.setTexture(texture);

font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");

  // Equation settings


 
  Equation.setFont(font);
  Equation.setFillColor(sf::Color::White);
  Equation.setOutlineColor(sf::Color::Blue);




  Equation.setFillColor(sf::Color::White);
  Equation.setOutlineColor(sf::Color::Blue);
  Equation.setPosition(500, 200);
  Equation.setOutlineThickness(2);
  Equation.setCharacterSize(80);



  


  // text field for user input
    
    text_diff.setFont(font);
    text_diff.setOutlineColor(sf::Color::Black);
    text_diff.setFillColor(sf::Color::Blue);

    text_diff.setString("Choose a Difficulty");
    text_diff.setPosition(500, 100);
    text_diff.setCharacterSize(50);



    // Button creations

    Button easy_button("Easy", 50, {200, 100}, sf::Color::Cyan, sf::Color::Blue);
    easy_button.setFont(font);
    easy_button.setPosition({600, 250});


    Button medium_button("Medium", 50, {200, 100}, sf::Color::Cyan, sf::Color::Blue);
    medium_button.setFont(font);
    medium_button.setPosition({600, 450});

    Button hard_button("Hard", 50, {200, 100}, sf::Color::Cyan, sf::Color::Blue);
    hard_button.setFont(font);
    hard_button.setPosition({600, 650});


    Button go_back_button("GO BACK", 50, {250, 100}, sf::Color::Cyan, sf::Color::Blue);
    go_back_button.setFont(font);
    go_back_button.setPosition({0, 0});

    

    while(window.isOpen()){


    while (window.pollEvent(event)) {

      if(event.type == sf::Event::MouseButtonPressed) {

        if(easy_button.isMouseHover(window))
          difficulty = 0;
        if(medium_button.isMouseHover(window))
          difficulty = 1;
        if(hard_button.isMouseHover(window))
          difficulty = 2;

        if(easy_button.isMouseHover(window) or medium_button.isMouseHover(window) or hard_button.isMouseHover(window)) {
          window.close();
          Game_Menu();
          return;
          

          
          }
        }

      if(event.type == sf::Event::Closed)
        window.close();

 }
  if(easy_button.isMouseHover(window))
      easy_button.setBackgColor(sf::Color::White);
    else
      easy_button.setBackgColor(sf::Color::Blue);

    if(medium_button.isMouseHover(window))
      medium_button.setBackgColor(sf::Color::White);
    else
      medium_button.setBackgColor(sf::Color::Blue);

    if(hard_button.isMouseHover(window))
      hard_button.setBackgColor(sf::Color::White);
    else
      hard_button.setBackgColor(sf::Color::Blue);

    if(go_back_button.isMouseHover(window))
      go_back_button.setBackgColor(sf::Color::White);
    else
      go_back_button.setBackgColor(sf::Color::Blue);


    // Drawing,Displaying

    window.clear();
    window.draw(sprite);
    //window.draw(Equation);

    easy_button.LetsDraw(window);
    medium_button.LetsDraw(window);
    hard_button.LetsDraw(window);
    go_back_button.LetsDraw(window);
    window.draw(text_diff);
    window.display();
 




  }


}
  void Game_Menu(){


            // GAME PAGE

        srand ( time(NULL) ); // setting seed for random numbers
       Button go_back_button("GO BACK", 50, {250, 100}, sf::Color::Cyan, sf::Color::Blue);
        go_back_button.setFont(font);
        go_back_button.setPosition({0, 0});
        Textfield Textbox(50, sf::Color::Blue, true);
        Textbox.setFont(font);
        Textbox.setPosition({500, 500});
        
        sf::RenderWindow window(sf::VideoMode(1350,1350),"Math Game");
        
        // setting window location to the center of the screen 
        window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width * 0.5 - window.getSize().x * 0.5, sf::VideoMode::getDesktopMode().height * 0.5 - window.getSize().y * 0.5));

    sf::Event gameEvent;
          vector<int> diff_nums = difficulty_numbers.at(difficulty);


            Score.setFont(font);
            Score.setFillColor(sf::Color::Blue);
            Score.setOutlineColor(sf::Color::White);
            Score.setOutlineThickness(2);
            Score.setCharacterSize(50);
            Score.setPosition({10,200});



            
            int user_input;
            bool correct_case = true;
            int score_value = 0;
            Score.setString("Score : " + to_string(score_value));

          while(window.isOpen()){

            if(correct_case == true){

            if(current_operation == '+') {

            char current_operation = operations.at(rand() % 4);

              number_1 = (rand() % diff_nums.at(0) + 1);
              number_2 = (rand() % number_1 + 1);


              result = number_1 + number_2 ;
            } else if(current_operation == '-') {
              number_1 = (rand() % diff_nums.at(1) + 1);
              number_2 = (rand() % number_1 + 1);

              result = number_1 - number_2;
            } else if(current_operation == '*') {
              number_1 = (rand() % diff_nums.at(2) + 1);
              number_2 = (rand() % diff_nums.at(2) + 1);

              result = number_1 * number_2;
            } else if (current_operation == '/') {
              number_1 = (rand() % diff_nums.at(3) + 1);
              number_2 = (rand() % number_1 + 2);
              while(number_1 % number_2 != 0)
                number_2 = (rand() % number_1 + 2);

              result = number_1 / number_2;
            }
            correct_case = false;
          }
            Equation.setString(to_string(number_1) + " " + current_operation + " " + to_string(number_2) + " = ");

            window.clear();
            window.draw(Equation);
            window.draw(Score);
            go_back_button.LetsDraw(window);
            Textbox.LetsDraw(window);
            window.display();
           
       





            
              std::stringstream(Textbox.getText()) >> user_input;
             


          

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
              

              if(result == user_input){

               score_value++;
               Textbox.text.clear();
               Textbox.LetsDraw(window);
               correct_case = true;
               Score.setString("Score : " + to_string(score_value));

              }
            
             



            }


            while (window.pollEvent(gameEvent)) {

               if(gameEvent.type == sf::Event::TextEntered) {

                Textbox.typedon(gameEvent);
              }


             if(gameEvent.type == sf::Event::MouseButtonPressed) {

            if(go_back_button.isMouseHover(window)){
            window.close();
            First_Screen();
            return;
          }
          
      
          }

          if(gameEvent.type == sf::Event::Closed){
             window.close();
              return;
          }
               

      }
          



              
              
             

            





            
            

}


          }




};










int main() {


  Mental_Math Mental_Math_Game;

  Mental_Math_Game.First_Screen();



}



