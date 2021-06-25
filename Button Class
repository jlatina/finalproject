class Button{ 

public:
      
        Button(){}
        sf::RectangleShape shape_Button;
        sf::Text text;

        void setFont(sf::Font &font){
            text.setFont(font);
        }


        Button(string text_s,int charsize,sf::Vector2f size,sf::Color textColor,sf::Color BackgColor){


            shape_Button.setSize(size);
            shape_Button.setFillColor(BackgColor);

            text.setString(text_s);
            text.setCharacterSize(charsize);
            text.setFillColor(textColor);



        }

       

        void setPosition(sf::Vector2f position){
            shape_Button.setPosition(position);         // Setting Position for Text

            float x = (position.x + shape_Button.getGlobalBounds().width / 2) - (text.getGlobalBounds().width / 2);
            float y = (position.y + shape_Button.getGlobalBounds().height / 2) - (text.getGlobalBounds().height / 2);
            text.setPosition({x,y});

        }

        

        bool isMouseHover(sf::RenderWindow &window){

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

        void setTextColor(sf::Color color){ // setting text color

            text.setColor(color);
        }

        void setBackgColor(sf::Color color){ // setting button back ground color

            shape_Button.setFillColor(color);
        }     


        void LetsDraw(sf::RenderWindow &window){
                                            // Drawing button and text
            window.draw(shape_Button);
            window.draw(text);
        }
};


// EXAMPLE
//
        Button easy_button("Easy",50,{200,100},sf::Color::Cyan,sf::Color::Blue);
        easy_button.setFont(font);
        easy_button.setPosition({600,250});
        
//


