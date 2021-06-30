// Copyright Victoria Carlsten

#include <chrono>
#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
// #include <SFML/Audio.hpp>

using std::to_string;
using std::string;

double accuratetime() {
  auto now = std::chrono::high_resolution_clock::now();
  auto duration = now.time_since_epoch();
  return duration.count() / 1'000'000'000.0;
}

sf::RenderWindow window(sf::VideoMode(1350, 1350), "Work your Brain!", sf::Style::Close);
sf::Text word_pg;
sf::Text username;
sf::Text clocktext;
sf::Text back;
sf::Text login;
sf::Text choose;
sf::Text option;
sf::Text logintext;
sf::Text signup;
// sf::Music music;

void playgame();
void loginfunc();

class interface {
 public:

  void windowfunc() {
    sf::Event event;
    std::time_t time = std::time(NULL);
    time_t newtime = time;  // change this
    std::tm now = *std::localtime(&newtime);

    int hrang,
        minang,
        secang;

    std::string shour = to_string(int(now.tm_hour)),
                sminute = to_string(int(now.tm_min)),
                sseconds = to_string(int(now.tm_sec));

// Create background image
    sf::Image box_background;
    box_background.loadFromFile("galaxy.png");
    sf::Texture texture_background;
    texture_background.loadFromImage(box_background);
    sf::Sprite sprite_background;
    sprite_background.setTexture(texture_background);
    sprite_background.scale(sf::Vector2f(1.6, 1.5)); //1st wider 2nd higher
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
    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
    word_pg.setFont(font);
    word_pg.setString("Play Game");
    word_pg.setFillColor(sf::Color::White);
    word_pg.setOutlineColor(sf::Color::Blue);
    word_pg.setOutlineThickness(3);
    word_pg.setPosition(430, 300);
    word_pg.setCharacterSize(100);

// Create "Username"
    username.setFont(font);
    username.setString("Not Logged In");
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
    // clocktext.setStyle(sf::Text::Style::Bold | sf::Text::Style::Underlined);

// Create login/sign -up text
    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
    login.setFont(font);
    login.setString("Log in/Sign up");
    login.setFillColor(sf::Color::White);
    login.setPosition(100, 82);
    login.setStyle(sf::Text::Style::Bold | sf::Text::Style::Underlined);

// Music
    // music.openFromFile("wii.wav");
    // music.play();

    sf::Clock tracktime;
    double time_now = accuratetime();

    window.clear();
    // sf::Event event;
    window.draw(sprite_background);
    window.draw(first);
    window.draw(second);
    window.draw(word_pg);
    // window.draw(word_la);
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
          // std::cout << "dx: " << dx << "dy: " << dy << "\n";
          loginfunc();
          break;
        }

      }
    }

    window.display();
  }

};


void eventfunc() {
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
      // dx2 = 0;
      // dy2 = 0;
      dx2 = location2.x - event.mouseButton.x;
      dy2 = location2.y - event.mouseButton.y;


      if (dx2 > -200 && dy2 > -50) {
        std::cout << "Back button pressed" << "\n";
        // break;
        // while (window.isOpen()) {

        while(window.isOpen()) {
          interface.windowfunc();
          eventfunc();
        }
      
      }

    }
  }
}

void playgame() {

  interface interace;
  while (window.isOpen()) {
// show game options


    eventfunc();

// Background
    sf::Image box_gbackground;
    box_gbackground.loadFromFile("magic.png");
    sf::Texture texture_gbackground;
    texture_gbackground.loadFromImage(box_gbackground);
    sf::Sprite sprite_gbackground;
    sprite_gbackground.setTexture(texture_gbackground);
    sprite_gbackground.scale(sf::Vector2f(1.4, 1.3)); //1st wider 2nd higher
    sprite_gbackground.setPosition(1, 1);

// "Please Choose a Game" text
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
    choose.setFont(font);
    choose.setString("Are you ready to become a Math Wizard?");
    choose.setFillColor(sf::Color::White);
    // choose.setOutlineColor(sf::Color::Red);
    choose.setOutlineThickness(2);
    choose.setPosition(280, 80);
    choose.setCharacterSize(40);
    choose.setStyle(sf::Text::Style::Bold | sf::Text::Style::Underlined);

// Frame for math picture
    sf::RectangleShape math(sf::Vector2f(30, 4));
    math.setFillColor(sf::Color::White);
    math.setPosition(230, 280);
    math.setSize(sf::Vector2f(445, 249));

// Filler frame for math picture
    sf::RectangleShape math1(sf::Vector2f(30, 4));
    math1.setFillColor(sf::Color::Black);
    math1.setPosition(250, 290);
    math1.setSize(sf::Vector2f(400, 230));

// Math picture
    sf::Image box1;
    box1.loadFromFile("brain.png");
    sf::Texture texture1;
    texture1.loadFromImage(box1);
    sf::Sprite sprite1;
    sprite1.setTexture(texture1);
    sprite1.scale(sf::Vector2f(0.5, 0.475)); //1st wider 2nd higher
    sprite1.setPosition(275, 300);

// Option to go back. Pressing this should lead back to main screen
    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
    back.setFont(font);
    back.setString("Go Back");
    back.setFillColor(sf::Color::White);
    back.setPosition(60, 40);
    back.setCharacterSize(28);


    window.clear();
    window.draw(sprite_gbackground);
    window.draw(choose);
    window.draw(back);
    window.draw(math);
    window.draw(math1);
    window.draw(sprite1);
    window.display();
  }

}

void loginfunc() { // Option to log-in or sign-up

  interface interace;
  while (window.isOpen()) {

     eventfunc();
      sf::Font font;
      sf::Image box_gbackground;
    box_gbackground.loadFromFile("magic.png");
    sf::Texture texture_gbackground;
    texture_gbackground.loadFromImage(box_gbackground);
    sf::Sprite sprite_gbackground;
    sprite_gbackground.setTexture(texture_gbackground);
    sprite_gbackground.scale(sf::Vector2f(1.4, 1.3)); //1st wider 2nd higher
    sprite_gbackground.setPosition(1, 1);

    // Option to go back. Pressing this should lead back to main screen
    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
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
}


int main() {

  bool click;
  interface interface;


  while (window.isOpen()) {
    interface.windowfunc();

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
