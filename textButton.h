#pragma once
#include "chap_header.h"

class TextButton {
public:
    TextButton(string txt, int charSize, sf::Color color);
    ~TextButton();

    void update(float secondsPassed);
    void draw(sf::RenderWindow& window);
    void setBaseColor(sf::Color c) { baseColor = c; }
    void setSelectedColor(sf::Color c) { selectedColor = c; }
    bool mouseWithin();

    sf::Text text; //Oh Noes, it's public! D:

private:
    sf::Color baseColor;
    sf::Color selectedColor;
    bool selected;
};
