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
    shape_Button.setPosition(position);
    
   // centering the text in the box
    float x = (position.x + shape_Button.getGlobalBounds().width / 2) - (text.getGlobalBounds().width / 2); 
    float y = (position.y + shape_Button.getGlobalBounds().height / 2) - (text.getGlobalBounds().height / 2);
    text.setPosition({x, y});

  }



  bool isMouseHover(sf::RenderWindow &window) {

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

  void setTextColor(sf::Color color) {

    text.setColor(color);
  }

  void setBackgColor(sf::Color color) {
   
   shape_Button.setFillColor(color);
  }


  void LetsDraw(sf::RenderWindow &window) {
    window.draw(shape_Button);
    window.draw(text);
  }
};

class Textfield {
 public:
  sf::Text Textbox_Text;
  std::ostringstream text;
  bool isSelected = false;
  bool haslimit = true;
  int limit;

 
  Textfield(int char_size, sf::Color color, bool select) {

    Textbox_Text.setCharacterSize(char_size);
    Textbox_Text.setColor(color);
    isSelected = select;
    if(select)
      Textbox_Text.setString("_"); // having "_" if the textbox is selected
    else
      Textbox_Text.setString("");

   }

 
  void setFont(sf::Font &font) {

    Textbox_Text.setFont(font);
 }

  void setPosition(sf::Vector2f position) {

   Textbox_Text.setPosition(position);
  }

  void setLimit(bool is_haslimit, int lim) { // number of char limit
   
   haslimit = is_haslimit;
    limit = lim;
  }

  string getText() {

    return text.str();
  }
  
 void resetText() {

  text.str("");
 }


  void LetsDraw(sf::RenderWindow &window) {
  
   window.draw(Textbox_Text);
  }

  void Read_and_Write_Input(sf::Event input) {   // converting event unicode into text

    if(isSelected) {

      int typed_character = input.text.unicode;
      if(typed_character < 128) {      
        if(haslimit) {
          if(text.str().length() <= limit) {
            change_Textbox_Text(typed_character);
          } else if(text.str().length() >  limit && typed_character == BACKSPACE_KEY)
            deletelastchar();

        } else
          change_Textbox_Text(typed_character);

      }

    }

  }

  void change_Textbox_Text(int typed_character) {  // Dynamically changing the text as the user types on the keyboard.

    if(typed_character != BACKSPACE_KEY  && typed_character != ESCAPE_KEY) {

      text << static_cast<char>(typed_character);

    } else if( typed_character == BACKSPACE_KEY) {

     if(text.str().length() > 0) {
        deletelastchar();

      }
    }


   Textbox_Text.setString(text.str() + "_");
  }
  
 void deletelastchar() {
 
    std::string t = text.str();
    std::string newT = "";
    for(int i = 0; i < t.length() - 1; i++) {
      newT += t.at(i);

    }
    text.str("");
    text << newT;

    Textbox_Text.setString(text.str());
  }


};




class Mental_Math {

 public:
  int counter{0}, number_1, number_2, result, difficulty, random_op_number;;
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



  void First_Screen() {

    sf::RenderWindow window(sf::VideoMode(1350, 1350), "Math Wizardry");

    // setting window location to the center of the screen
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width * 0.5 - window.getSize().x * 0.5, sf::VideoMode::getDesktopMode().height * 0.5 - window.getSize().y * 0.5));


    if(!texture.loadFromFile("/home/ece-student/Desktop/inclass/paper1.jpg")) {

      std::cout << "Load Failed" << "\n";

    }

    sf::Sprite sprite;
    sprite.setTexture(texture);

    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");


    text_diff.setFont(font);
    text_diff.setOutlineThickness(2);
    text_diff.setOutlineColor(sf::Color::Black);
    text_diff.setFillColor(sf::Color::Blue);

    text_diff.setString("Choose a Difficulty");
    text_diff.setPosition(500, 100);
    text_diff.setCharacterSize(50);


    Button easy_button("Muggles", 50, {400, 100}, sf::Color::Cyan, sf::Color::Blue);
    easy_button.setFont(font);
    easy_button.setPosition({540, 250});


    Button medium_button("Baby Wizard", 50, {400, 100}, sf::Color::Cyan, sf::Color::Blue);
    medium_button.setFont(font);
    medium_button.setPosition({540, 450});

    Button hard_button("Master Wizard", 50, {400, 100}, sf::Color::Cyan, sf::Color::Blue);
    hard_button.setFont(font);
    hard_button.setPosition({540, 650});


    Button go_back_button("GO BACK", 50, {250, 100}, sf::Color::Cyan, sf::Color::Blue);
    go_back_button.setFont(font);
    go_back_button.setPosition({0, 0});



     while(window.isOpen()) { // Setting the difficulty and starting the game

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
            Game_Screen();
            return;


          }
          if(go_back_button.isMouseHover(window)){

            // Victoria 


          }
        }

        if(event.type == sf::Event::Closed)
          window.close();

      }

      // Color change effect when the user hovers over the buttons

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




      window.clear();
      window.draw(sprite);
      easy_button.LetsDraw(window);
      medium_button.LetsDraw(window);
      hard_button.LetsDraw(window);
      go_back_button.LetsDraw(window);
      window.draw(text_diff);
      window.display();
    }


  }
  


  void Game_Screen() {

    sf::Event gameEvent;

    sf::RenderWindow window(sf::VideoMode(1350, 1350), "MATH WIZARDRY");

    // setting window position to the center of the screen
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width * 0.5 - window.getSize().x * 0.5, sf::VideoMode::getDesktopMode().height * 0.5 - window.getSize().y * 0.5));

    if(!texture.loadFromFile("/home/ece-student/Desktop/inclass/paper1.jpg")) {

      std::cout << "Load Failed" << "\n";

    }

    sf::Sprite sprite;
    sprite.setTexture(texture);





   // setting seed for random numbers

   srand (time(NULL)); 



    // Textbox creation for user input

    Textfield Textbox(50, sf::Color::White, true);
    Textbox.setFont(font);
    Textbox.setPosition({540, 500});



    Equation.setFont(font);
    Equation.setFillColor(sf::Color::White);
    Equation.setOutlineColor(sf::Color::Blue);
    Equation.setPosition(530, 200);
    Equation.setOutlineThickness(2);
    Equation.setCharacterSize(80);


    Score.setFont(font);
    Score.setFillColor(sf::Color::Blue);
    Score.setOutlineColor(sf::Color::White);
    Score.setOutlineThickness(2);
    Score.setCharacterSize(50);
    Score.setPosition({10, 200});


    vector<int> diff_nums = difficulty_numbers.at(difficulty); // getting difficulty numbers

    int user_input;
    bool correct_case = true;
    int score_value = 0;
    Score.setString("SCORE : " + to_string(score_value));
    char current_operation;


    // 3 seconds countdown settings

    int start_time_counter = 3;
    sf::Text start_countdown;
    start_countdown.setFont(font);
    start_countdown.setString(to_string(3));
    start_countdown.setCharacterSize(100);
    start_countdown.setPosition({600, 300});
    start_countdown.setFillColor(sf::Color::Blue);
    start_countdown.setOutlineColor(sf::Color::Cyan);

    sf::Time Start_Count = sf::seconds(4); // +1 seconds for delay
    sf::Time Game_Time = sf::seconds(64);
    sf::Time current_time;


    sf::Text Get_Ready;
    Get_Ready.setFont(font);
    Get_Ready.setString("Get Ready !");
    Get_Ready.setCharacterSize(100);
    Get_Ready.setPosition({400, 150});
    Get_Ready.setOutlineThickness(2);
    Get_Ready.setFillColor(sf::Color::Blue);
    Get_Ready.setOutlineColor(sf::Color::White);


    // 1 minute countdown settings

    int game_time_counter = 64; // +4 seconds for  starting and delay
    sf::Text Game_countdown;
    Game_countdown.setFont(font);
    Game_countdown.setString("TIME LEFT : " + to_string(3));
    Game_countdown.setCharacterSize(30);
    Game_countdown.setPosition({0, 300});
    Game_countdown.setOutlineThickness(2);
    Game_countdown.setFillColor(sf::Color::Blue);
    Game_countdown.setOutlineColor(sf::Color::White);

    sf::Clock clock;
    while(window.isOpen()) {

      while(start_time_counter > 0) { // 3 seconds count down



        sf::Time current_time = Start_Count - clock.getElapsedTime();

        start_countdown.setString(to_string( int(current_time.asSeconds())));
        start_time_counter = int(current_time.asSeconds());

        window.clear();
        window.draw(start_countdown);
        window.draw(Get_Ready);
        window.display();


      }

      while(game_time_counter > 0) {  // Game  and 60 seconds countdown starts

        if(correct_case == true) {
          current_operation = operations.at(rand() % 4);

          if(current_operation == '+') {


            number_1 = (rand() % diff_nums.at(0) + 1);
            number_2 = (rand() % number_1 + 1);


            result = number_1 + number_2 ;
          } else if(current_operation == '-') {
            number_1 = rand() % diff_nums.at(1) + 1;
            number_2 = rand() % number_1 + 1;

            result = number_1 - number_2;
          } else if(current_operation == '*') {
            number_1 = rand() % diff_nums.at(2) + 1;
            number_2 = rand() % diff_nums.at(2) + 1;

            result = number_1 * number_2;
          } else if (current_operation == '/') {
            number_1 = rand() % diff_nums.at(3) + 1;
            number_2 = rand() % number_1 + 1;
            while(number_1 % number_2 != 0)
              number_2 = rand() % number_1 + 2;

            result = number_1 / number_2;
          }
          correct_case = false;
        }
        Equation.setString(to_string(number_1) + " " + current_operation + " " + to_string(number_2) + " = ");


        sf::Time current_time = Game_Time - clock.getElapsedTime(); //countdown


        Game_countdown.setString("TIME LEFT : " + to_string( int(current_time.asSeconds())) + " SECONDS");
        game_time_counter = int(current_time.asSeconds());


        window.clear();
        window.draw(sprite);
        window.draw(Equation);
        window.draw(Score);
        window.draw(Game_countdown);
        Textbox.LetsDraw(window);
        window.display();


        std::stringstream(Textbox.getText()) >> user_input;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {


          if(result == user_input) {

            score_value++;
            correct_case = true;
            Score.setString("Score : " + to_string(score_value));
            Textbox.resetText();

          }



        }


        while (window.pollEvent(gameEvent)) {

          if(gameEvent.type == sf::Event::TextEntered) {

            Textbox.Read_and_Write_Input(gameEvent);
          }

          if(gameEvent.type == sf::Event::MouseButtonPressed) {


          }

          if(gameEvent.type == sf::Event::Closed) {
            window.close();
            return;
          }


        }

      }


      window.clear();
      window.close();
      Final_Screen(score_value, difficulty);

    }

  }
 
  void Final_Screen(int score_value, int difficulty) {

    sf::RenderWindow window(sf::VideoMode(1350, 1350), "MATH WIZARDRY");

    // setting window position to the center of the screen
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width * 0.5 - window.getSize().x * 0.5, sf::VideoMode::getDesktopMode().height * 0.5 - window.getSize().y * 0.5));


    if(!texture.loadFromFile("/home/ece-student/Desktop/inclass/paper3.png")) {

      std::cout << "Load Failed" << "\n";

    }

    sf::Sprite sprite;
    sprite.setTexture(texture);






    sf::Event gameEvent;

    sf::Text Well_Done;
    Well_Done.setFont(font);
    Well_Done.setString("Well Done !");
    Well_Done.setCharacterSize(80);
    Well_Done.setPosition({400, 50});
    Well_Done.setOutlineThickness(2);
    Well_Done.setFillColor(sf::Color::Blue);
    Well_Done.setOutlineColor(sf::Color::White);


    sf::Text run_Score;
    run_Score.setFont(font);
    run_Score.setString("Current Score : " + to_string(score_value));
    run_Score.setCharacterSize(60);
    run_Score.setPosition({400, 250});
    run_Score.setOutlineThickness(2);
    run_Score.setFillColor(sf::Color::Blue);
    run_Score.setOutlineColor(sf::Color::White);


    int personal_best_score = 100;  // <--- jon link it and remove the comment.

    sf::Text Personal_Best;
    Personal_Best.setFont(font);
    Personal_Best.setString("Personal Best : " + to_string(personal_best_score));
    Personal_Best.setCharacterSize(60);
    Personal_Best.setPosition({400, 450});
    Personal_Best.setOutlineThickness(2);
    Personal_Best.setFillColor(sf::Color::Blue);
    Personal_Best.setOutlineColor(sf::Color::White);


    Button return_2_menu_button("MAIN MENU", 30, {200, 100}, sf::Color::Cyan, sf::Color::Blue);
    return_2_menu_button.setFont(font);
    return_2_menu_button.setPosition({0,0});


    sf::Text Difficulty_mode;
    Difficulty_mode.setFont(font);
    Difficulty_mode.setCharacterSize(30);
    Difficulty_mode.setPosition({1000, 1000});
    Difficulty_mode.setOutlineThickness(2);

    if(difficulty == 0) {
      Difficulty_mode.setString("Muggles Mode");
      Difficulty_mode.setFillColor(sf::Color::Green);
      Difficulty_mode.setOutlineColor(sf::Color::White);


    } else if(difficulty == 1) {

      Difficulty_mode.setString("Baby Wizard Mode");
      Difficulty_mode.setFillColor(sf::Color::Blue);
      Difficulty_mode.setOutlineColor(sf::Color::White);


    } else {
      Difficulty_mode.setString("Master Wizard Mode");
      Difficulty_mode.setFillColor(sf::Color::Red);
      Difficulty_mode.setOutlineColor(sf::Color::White);

    }

    while(window.isOpen()) {


      window.clear();
      window.draw(sprite);
      window.draw(Difficulty_mode);
      window.draw(Personal_Best);
      window.draw(run_Score);
      window.draw(Well_Done);
      return_2_menu_button.LetsDraw(window);
      window.display();


      while (window.pollEvent(gameEvent)) {



        if(gameEvent.type == sf::Event::MouseButtonPressed) {
          if(return_2_menu_button.isMouseHover(window)) {
            window.close();
            First_Screen();


          }

        }

        if(gameEvent.type == sf::Event::Closed) {
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
