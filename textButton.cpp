#include "textButton.h"

TextButton::TextButton(string txt, int charSize, sf::Color color) {
    text.setString(txt);
    text.setCharacterSize(charSize);
    text.setColor(color);
    text.setFont(FONT_1);
}

TextButton::~TextButton() {

}

void TextButton::update(float secondsPassed) {

}

void TextButton::draw(sf::RenderWindow& window) {
    window.draw(text);
}
