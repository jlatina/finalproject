#include <chrono>
#include <fstream>
#include "account.h"
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <sstream>
#include <cstdio>


using std::fstream;
using std::ifstream;
using std::ofstream;
using std::stoi;
using std::vector;
using std::cout;
using std::to_string;
using std::string;

#define BACKSPACE_KEY 8
#define ESCAPE_KEY 27

double accuratetime() {
  auto now = std::chrono::high_resolution_clock::now();
  auto duration = now.time_since_epoch();
  return duration.count() / 1'000'000'000.0;
}

sf::Text word_pg;
sf::Text username;
sf::Text clocktext;
sf::Text back;
sf::Text login;
sf::Text choose;
sf::Text option;
sf::Text logintext;
sf::Text signup;
sf::Text yestext;
string logged_in_username;

sf::RenderWindow window(sf::VideoMode(1350, 1350), "Work your Brain!", sf::Style::Close);

void playgame();
void loginfunc();




class interface {
 public:

  account_manager account;
  bool account_exists;

  void windowfunc(sf::RenderWindow &window) {  // Main Menu
    sf::Event event;
    std::time_t time = std::time(NULL);
    time_t newtime = time;
    std::tm now = *std::localtime(&newtime);

    int hrang,
        minang,
        secang;

    std::string shour = to_string(int(now.tm_hour)),
                sminute = to_string(int(now.tm_min)),
                sseconds = to_string(int(now.tm_sec));

// Create background image
    sf::Image box_background;
    box_background.loadFromFile("External Files/galaxy.png");
    sf::Texture texture_background;
    texture_background.loadFromImage(box_background);
    sf::Sprite sprite_background;
    sprite_background.setTexture(texture_background);
    sprite_background.scale(sf::Vector2f(1.6, 1.6)); 
    sprite_background.setPosition(1, 1);

// create the first rectangle
    sf::RectangleShape first(sf::Vector2f(30, 4));
    first.setFillColor(sf::Color::White);
    first.setPosition(410, 295);
    first.setSize(sf::Vector2f(550, 150));

// create the second rectangle
    sf::RectangleShape second(sf::Vector2f(30, 4));
    second.setFillColor(sf::Color::Black);
    second.setPosition(430, 315);
    second.setSize(sf::Vector2f(510, 112));

// create "Play Game"
    sf::Font font;
    font.loadFromFile("External Files/Ubuntu-BI.ttf");
    word_pg.setFont(font);
    word_pg.setString("Play Game");
    word_pg.setFillColor(sf::Color::White);
    word_pg.setOutlineColor(sf::Color::Blue);
    word_pg.setOutlineThickness(3);
    word_pg.setPosition(430, 300);
    word_pg.setCharacterSize(100);

// Create "Username"
    username.setFont(font);
    if (logged_in_username == "") {
      username.setString("Not Logged In");
    } else {
      username.setString(logged_in_username);
    }
    username.setFillColor(sf::Color::White);
    username.setPosition(1090, 80);
    username.setStyle(sf::Text::Style::Bold | sf::Text::Style::Underlined);

// The clocktext
    clocktext.setFont(font);
    clocktext.setString(shour + ":" + sminute + ":" + sseconds);
    clocktext.setFillColor(sf::Color::White);
    clocktext.setCharacterSize(24);
    clocktext.setPosition(610, 650);
    clocktext.setCharacterSize(30);


// Create login/sign -up text
    font.loadFromFile("External Files/Ubuntu-BI.ttf");
    login.setFont(font);
    login.setString("Log in/Sign up");
    login.setFillColor(sf::Color::White);
    login.setPosition(100, 82);
    login.setStyle(sf::Text::Style::Bold | sf::Text::Style::Underlined);

    sf::Clock tracktime;
    double time_now = accuratetime();

    window.clear();
    window.draw(sprite_background);
    window.draw(first);
    window.draw(second);
    window.draw(word_pg);
    window.draw(username);
    window.draw(login);

    time = std::time(NULL);
    clocktext.setString(shour + ":" + sminute + ":" + sseconds);
    sf::Time elapsedsec = tracktime.getElapsedTime();

    if (now.tm_hour < 10)
      shour = "0" + to_string(int(now.tm_hour));
    else
      shour = to_string(int(now.tm_hour));

    if (now.tm_min < 10)
      sminute = "0" + to_string(int(now.tm_min));
    else
      sminute = to_string(int(now.tm_min));

    if (now.tm_sec < 10)
      sseconds = "0" + to_string(int(now.tm_sec));
    else
      sseconds = to_string(int(now.tm_sec));

    clocktext.setString(shour + ":" + sminute + ":" + sseconds);

    hrang = (float(now.tm_hour) * 30) - 90;
    minang = (float(now.tm_min) * 6) - 90;
    secang = (float(now.tm_sec) * 6) - 90;

    window.draw(clocktext);

    bool click;

    while (window.pollEvent(event)) {

      if (event.type == sf::Event::Closed)
        window.close();

      if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
        window.close();

      if (event.type == sf::Event::MouseButtonPressed) {

        auto location = word_pg.getPosition();
        double dx = location.x - event.mouseButton.x;
        double dy = location.y - event.mouseButton.y;

        if (dx < 50 && dy < 50) {
          std::cout << "Play button pressed" << "\n";
          click = true;
          playgame();
          break;
        }

        auto location2 = back.getPosition();
        double dx2 = location2.x - event.mouseButton.x;
        double dy2 = location2.y - event.mouseButton.y;

        auto location3 = login.getPosition();
        double dx3 = location3.x - event.mouseButton.x;
        double dy3 = location3.y - event.mouseButton.y;

        if (dx3 < 200 && dy3 < 170) {
          std::cout << "Login button pressed" << "\n";
          loginfunc();
          break;
        }

      }
    }

    window.display();
  }

};

//   Title: Button class source code
//   Author: TermSpar YouTube channel
//   Date: 2019
// Availability: https://www.youtube.com/watch?v=T31MoLJws4U&t=570s
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

//   Title: Textfield class source code
//   Author: TermSpar YouTube channel
//   Date: 2019
// Availability: https://www.youtube.com/watch?v=T31MoLJws4U&t=570s

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
  int number_1, number_2, result, difficulty, random_op_number;
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

    if(!texture.loadFromFile("External Files/paper1.jpg")) {

      std::cout << "Load Failed" << "\n";

    }

    sf::Sprite sprite;
    sprite.setTexture(texture);

    font.loadFromFile("External Files/Ubuntu-BI.ttf");


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
            // window.close();
            Game_Screen();
            return;


          }


          if(go_back_button.isMouseHover(window)){

            window.clear();
            interface interface;
            while (window.isOpen()){
            interface.windowfunc(window);
            
            }


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

    if(!texture.loadFromFile("External Files/paper1.jpg")) {

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
    sf::Time Game_Time = sf::seconds(64); // +4 seconds for  starting and delay
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

    int game_time_counter = 64; 
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
      
      Final_Screen(score_value, difficulty);

    }

  }

  void Final_Screen(int score_value, int difficulty) {

    if(!texture.loadFromFile("External Files/paper3.png")) {

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

    account_manager account;    
    string personal_best_score;
    string *score_pointer = &personal_best_score;

    if (logged_in_username != ""){

      string highscore;
      int highscore_int;

      ifstream highscores;
      ifstream accountinfo;            

      accountinfo.open("accountinfo.txt");
      int usercount = account.return_count(logged_in_username, &accountinfo);
      accountinfo.close();
      highscores.open("highscores.txt");
      highscore = account.return_line_count(usercount, &highscores);
      highscores.close();

      highscore_int = stoi(highscore);
      string scorestring = to_string(score_value);
      *score_pointer = highscore;

      if (score_value > highscore_int){

          highscores.open("highscores.txt");
          account.modifyscore(usercount, &highscores, highscore, scorestring);
          highscores.close();
          highscores.open("highscores.txt");
          *score_pointer = account.return_line_count(usercount, &highscores);
          highscores.close();

      }

      highscores.close();
    } else {

      *score_pointer = to_string(score_value);
        }


    sf::Text Personal_Best;
    Personal_Best.setFont(font);
    Personal_Best.setString("Personal Best : " + personal_best_score);
    Personal_Best.setCharacterSize(60);
    Personal_Best.setPosition({400, 450});
    Personal_Best.setOutlineThickness(2);
    Personal_Best.setFillColor(sf::Color::Blue);
    Personal_Best.setOutlineColor(sf::Color::White);


    Button return_2_menu_button("MAIN MENU", 30, {200, 100}, sf::Color::Cyan, sf::Color::Blue);
    return_2_menu_button.setFont(font);
    return_2_menu_button.setPosition({0, 0});


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




void eventfunc() { // Close window + Back Button
  sf::Event event;
  interface interface;
  auto location2 = back.getPosition();
  double dx2 = location2.x - event.mouseButton.x;
  double dy2 = location2.y - event.mouseButton.y;


  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      window.close();



    if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
      window.close();

    if (event.type == sf::Event::MouseButtonPressed) {
      dx2 = location2.x - event.mouseButton.x;
      dy2 = location2.y - event.mouseButton.y;
      std::cout << "dx2: " << dx2 << " dy2: " << dy2 << "\n";


      if (dx2 > -200 && dy2 > -50) {
        std::cout << "Back button pressed" << "\n";

        while(window.isOpen()) {
          interface.windowfunc(window);
          eventfunc();
        }


      }

    }
  }
}

void playgame() { // Ready to play game text

  interface interface;
  while (window.isOpen()) {

    eventfunc();

// Background
    sf::Image box_gbackground;
    box_gbackground.loadFromFile("External Files/magic.png");
    sf::Texture texture_gbackground;
    texture_gbackground.loadFromImage(box_gbackground);
    sf::Sprite sprite_gbackground;
    sprite_gbackground.setTexture(texture_gbackground);
    sprite_gbackground.scale(sf::Vector2f(1.4, 1.4)); //1st wider 2nd higher
    sprite_gbackground.setPosition(1, 1);

// "Are you ready to become a Math Wizard?" text
    sf::Font font;
    font.loadFromFile("External Files/Ubuntu-BI.ttf");
    choose.setFont(font);
    choose.setString("Are you ready to become a Math Wizard?");
    choose.setFillColor(sf::Color::White);
    choose.setOutlineThickness(2);
    choose.setPosition(140, 200);
    choose.setCharacterSize(55);
    choose.setStyle(sf::Text::Style::Bold);

    // Rectangle for yes text
    sf::RectangleShape rec(sf::Vector2f(30, 4));
    rec.setFillColor(sf::Color::Blue);
    rec.setPosition(410, 350);
    rec.setSize(sf::Vector2f(520, 60));

    // Yes text
    yestext.setFont(font);
    yestext.setString("Yes, let the magic begin!");
    yestext.setFillColor(sf::Color::White);
    yestext.setPosition(410, 350);
    yestext.setCharacterSize(45);


// Option to go back. Pressing this should lead back to main screen
    font.loadFromFile("External Files/Ubuntu-BI.ttf");
    back.setFont(font);
    back.setString("Go Back");
    back.setFillColor(sf::Color::White);
    back.setPosition(60, 40);
    back.setCharacterSize(28);


    window.clear();
    window.draw(sprite_gbackground);
    window.draw(choose);
    window.draw(back);
    window.draw(rec);
    window.draw(yestext);
    window.display();


    sf::Event event;
    auto location2 = back.getPosition();
    double dx2 = location2.x - event.mouseButton.x;
    double dy2 = location2.y - event.mouseButton.y;

    while (window.pollEvent(event)) {



      if (event.type == sf::Event::Closed)
        window.close();

      if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
        window.close();

      if (event.type == sf::Event::MouseButtonPressed) {
        dx2 = location2.x - event.mouseButton.x;
        dy2 = location2.y - event.mouseButton.y;

        if (dx2 > -200 && dy2 > -50) {
          std::cout << "Back button pressed" << "\n";

          while(window.isOpen()) {
            interface.windowfunc(window);
            eventfunc();
          }


        }

        if (dx2 > -860 && dx2 < -350 && dy2 > -350 && dy2 < -320) {
          Mental_Math Mental_Math_Game;
          Mental_Math_Game.First_Screen();
        }


      }

    }

  }
}


void loginfunc() { // Option to log-in or sign-up

  sf::Event event;
  account_manager account;
  interface interface;

  ifstream ifs;

  ifs.open("accountinfo.txt");

  if (!ifs) {
    ofstream create_file("accountinfo.txt");
    ifs.open("accountinfo.txt");
  }


  while (window.isOpen()) {



    
    auto location2 = back.getPosition();
    double dx2 = location2.x - event.mouseButton.x;
    double dy2 = location2.y - event.mouseButton.y;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
        window.close();

      if (event.type == sf::Event::MouseButtonPressed) {
        dx2 = location2.x - event.mouseButton.x;
        dy2 = location2.y - event.mouseButton.y;

        std::cout << "dx2: " << dy2 << " dy2: " << dy2 << "\n";

        // login button press event



        if (dx2 < -330 & dy2 < -330) {

          string new_username = account.account_register(&ifs);
          bool *account_bool = &interface.account_exists;
          string *ptr = &logged_in_username;

          if (new_username != "") {
            *account_bool = true;
            *ptr = new_username;
            interface.windowfunc(window);
            break;
          }

          break;
        }



        if (dx2 < -230 && dy2 < -230) {

          string login_username = account.login(&ifs);
          bool *account_bool = &interface.account_exists;
          string *ptr = &logged_in_username;

          if (login_username != "") {
            *account_bool = true;
            *ptr = login_username;
            interface.windowfunc(window);
            break;
          }
          break;
        }






        if (dx2 > -200 && dy2 > -50) {
          std::cout << "Back button pressed" << "\n";

          while(window.isOpen()) {
            interface.windowfunc(window);
            eventfunc();
          }

        }

      }
    }
    sf::Font font;
    sf::Image box_gbackground;
    box_gbackground.loadFromFile("External Files/magic.png");
    sf::Texture texture_gbackground;
    texture_gbackground.loadFromImage(box_gbackground);
    sf::Sprite sprite_gbackground;
    sprite_gbackground.setTexture(texture_gbackground);
    sprite_gbackground.scale(sf::Vector2f(1.4, 1.4)); //1st wider 2nd higher
    sprite_gbackground.setPosition(1, 1);

    // Option to go back. Pressing this should lead back to main screen
    font.loadFromFile("External Files/Ubuntu-BI.ttf");
    back.setFont(font);
    back.setString("Go Back");
    back.setFillColor(sf::Color::White);
    back.setPosition(60, 40);
    back.setCharacterSize(28);

    // Rectangle for login text
    sf::RectangleShape first(sf::Vector2f(30, 4));
    first.setFillColor(sf::Color::Blue);
    first.setPosition(430, 275);
    first.setSize(sf::Vector2f(450, 80));

    // Text login
    logintext.setFont(font);
    logintext.setString("Log In");
    logintext.setFillColor(sf::Color::White);
    logintext.setPosition(570, 270);
    logintext.setCharacterSize(60);

    // Rectangle for signup text
    sf::RectangleShape first2(sf::Vector2f(30, 4));
    first2.setFillColor(sf::Color::Blue);
    first2.setPosition(430, 370);
    first2.setSize(sf::Vector2f(450, 80));

    // Text signup
    signup.setFont(font);
    signup.setString("Sign-up");
    signup.setFillColor(sf::Color::White);
    signup.setPosition(550, 370);
    signup.setCharacterSize(60);

    window.clear();
    window.draw(sprite_gbackground);
    window.draw(back);
    window.draw(first);
    window.draw(logintext);
    window.draw(first2);
    window.draw(signup);
    window.display();
  }
  ifs.close();
}


int main() {

  Mental_Math Mental_Math;

  bool click;
  interface interface;


  while (window.isOpen()) {
    interface.windowfunc(window);




    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
        window.close();

    }

  }
  return 0;
}
