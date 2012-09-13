#pragma once
#include "chap_header.h"

class TextButton {
public:
    TextButton(string txt, int charSize, sf::Color color);
    ~TextButton();

    void update(float secondsPassed);
    void draw(sf::RenderWindow& window);

    sf::Text text; //Oh Noes, it's public! D:

private:

};
