#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

class Menu : public sf::RectangleShape{
public:
    Menu(int number_buttons);
protected:
    int number_of_buttons_;
};

#endif // MENU_H
