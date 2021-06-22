// Copyright 2021 Victoria Carlsten
#include <chrono>
#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>

using std::to_string;
using std::string;

double accuratetime() {
  auto now = std::chrono::high_resolution_clock::now();
  auto duration = now.time_since_epoch();
  return duration.count() / 1'000'000'000.0;
}

sf::RenderWindow window(sf::VideoMode(1350, 1350), "Work your Brain!", sf::Style::Close);
sf::Text word_pg;
sf::Text word_la;
sf::Text clocktext;
sf::Text back;
sf::Text login;
sf::Text choose;
sf::Text option;

void windowfunc() {
  std::time_t time = std::time(NULL);
  time_t newtime = time;  // change this
  std::tm now = *std::localtime(&newtime);

  int hrang,
      minang,
      secang;

  std::string shour = to_string(int(now.tm_hour)),
              sminute = to_string(int(now.tm_min)),
              sseconds = to_string(int(now.tm_sec));

// create the first rectangle
  sf::RectangleShape first(sf::Vector2f(30, 4));
  first.setFillColor(sf::Color::Red);
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
  word_pg.setOutlineThickness(5);
  word_pg.setPosition(430, 300);
  word_pg.setCharacterSize(100);

// create "Language"
  word_la.setFont(font);
  word_la.setString("Language Options");
  word_la.setFillColor(sf::Color::White);
  word_la.setPosition(1000, 80);
  word_la.setStyle(sf::Text::Style::Bold | sf::Text::Style::Underlined);

// The clocktext
  clocktext.setFont(font);
  clocktext.setString(shour + ":" + sminute + ":" + sseconds);
  clocktext.setFillColor(sf::Color::White);
  clocktext.setCharacterSize(24);
  clocktext.setPosition(1080, 650);
  clocktext.setCharacterSize(30);
  // clocktext.setStyle(sf::Text::Style::Bold | sf::Text::Style::Underlined);

// Create login/sign -up text
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  login.setFont(font);
  login.setString("Log in/Sign up");
  login.setFillColor(sf::Color::White);
  login.setPosition(100, 82);
  login.setStyle(sf::Text::Style::Bold | sf::Text::Style::Underlined);

  sf::Clock tracktime;
  double time_now = accuratetime();

  window.clear();
  // sf::Event event;
  window.draw(first);
  window.draw(second);
  window.draw(word_pg);
  window.draw(word_la);
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
  window.display();
}


void playgame() {
  while (window.isOpen()) {
// should show game options
    window.clear();

// "Please Choose a Game" text
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
    choose.setFont(font);
    choose.setString("Please Choose a Game");
    choose.setFillColor(sf::Color::White);
    choose.setOutlineColor(sf::Color::Blue);
    choose.setOutlineThickness(2);
    choose.setPosition(450, 80);
    choose.setCharacterSize(40);

// Option to go back. Pressing this should lead back to main screen
    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
    back.setFont(font);
    back.setString("Go Back");
    back.setFillColor(sf::Color::White);
    back.setPosition(60, 40);
    back.setCharacterSize(28);

    window.draw(choose);
    window.draw(back);
    window.display();
  }
}

void lanuagefunc() {
  while (window.isOpen()) {
    window.clear();
    sf::Font font;
    sf::RectangleShape rectangle1(sf::Vector2f(30, 4));
    rectangle1.setFillColor(sf::Color::Red);
    rectangle1.setPosition(100, 100);

    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
    option.setFont(font);
    option.setString("Go Back");
    option.setFillColor(sf::Color::White);
    option.setPosition(60, 40);
    option.setCharacterSize(28);

    window.draw(option);
    window.draw(rectangle1);
    window.display();

    // Language Options
  }
}

int main() {
  while (window.isOpen()) {
    windowfunc();

    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
        window.close();

      // opening a new window if mouse is pressed
      if (event.type == sf::Event::MouseButtonPressed) {

        auto location = word_pg.getPosition();
        double dx = location.x - event.mouseButton.x;
        double dy = location.y - event.mouseButton.y;

        if (dx < 50 && dy < 50) {
          playgame();
          break;
        }
      }

        auto location2 = back.getPosition();
        double dx2 = location2.x - event.mouseButton.x;
        double dy2 = location2.y - event.mouseButton.y;

        if (dx2 < 35 && dy2 < 35) {
          window.clear();
          break;
        }

      auto location1 = word_la.getPosition();
      double dx1 = location1.x - event.mouseButton.x;
      double dy1 = location1.y - event.mouseButton.y;

      if (dx1 < 50 && dy1 < 50) {
        lanuagefunc();
        break;
      }

    }
  }
  return 0;
}

