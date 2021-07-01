
# Math Wizardy Final Project App

## Description 
The Math Wizardry app serves to encourage and motivate children ages 8 and up in challenging their brain outside of school. Due to Covid-19 and the vast, even detrimental  repercussions it has had on society, the group decided to focus their attention on how children's educational lives have been affected. While Zoom has provided a great platform for education to still continue, students especially those enrolled in preliminary school have shown little to no progress in retaining the information that has been taught to them. It has become rather difficult for these children to maintain focus and many dread logging onto their computer to learn. In addition, the group was influenced by already existing mental math games and math competitions that they once participated in as children that challenged them to generate quick and correct solutions. This app brings back the fun in learning math as the user is able to keep track of their progress whenever they log in. This app is a great alternative for parents who do not feel comfortable with their children becoming obsessed with technology. Math Wizardry  can be used as an incentive and a healthier way to view technology. 

### Features
A series of windows created by SMFL are joined together with the use of sf::Event:: *insert button name*. By just the click of the mouse button, the user is able to transition to eventually get to playing the game. 

Background images served to bring asethetic to the application itself by mainting the galaxy and magical theme of the app. 

The Math Wizardy Game consists of three levels that increase in difficulty: Level 1 *muggle* (no magic skills at all) Level 2 *baby wizard* (wizard in training) and Level 3 *master wizard* (all wizard powers). During each level there is a constant 60 second countdown when every equation is displayed. This pushes the user to have not only a quicker response, but to generate their correcet answer faster. 


## Installation

Download SFML version correlated to your version of Visual C++ (https://www.sfml-dev.org/download/sfml/2.5.1/).

## Usage

```c++
#include <SFML/Graphics.hpp>

// Basic example to draw a rectangle
int main() {

sf::RenderWindow window(sf::VideoMode(200, 200), "Rectangle");

// Create  Rectangle 
  sf::RectangleShape rectangle(sf::Vector2f(100, 80));
  rectangle.setFillColor(sf::Color::Red);
  
    while (window.isOpen())
    {
         sf::Event event;     
        while (window.pollEvent(event))
        { 
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(rectangle);
        window.display();
    }
    return 0;
}
```
 ### Running Program 
 1. Navigate through terminal where the file is 
 2. Compile file
 3. Run executable

 
```c++
$ cd /Desktop
$/Desktop g++ main.cpp -o game -lsfml-window -lsfml-graphics -lsfml-system
$/Desktop game
```

## Further Support 
For issues dealing with SFML implementation visit (https://www.sfml-dev.org/tutorials/2.5/).

## Authors
Victoria Carlsten: Interface Lead

Ahmet Caliskan: Specification Lead

Jonathan Mikalov: Technical Lead

Jeanette Villanueva: Project Lead
