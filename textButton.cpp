#include "textButton.h"

TextButton::TextButton(string txt, int charSize, sf::Color color) {
    text.setString(txt);
    text.setCharacterSize(charSize);
    text.setColor(color);
    baseColor = selectedColor = color;
    text.setFont(FONT_1);
    selected = false;
}

TextButton::~TextButton() {

}

void TextButton::update(float secondsPassed) {
    bool prevSelected = selected;
    if (mouseWithin())
        selected = true;
    else
        selected = false;
    //Just became selected?
    if (!prevSelected && selected)
    {
        text.setColor(selectedColor);
    }
    //Just became unselected?
    if (prevSelected && !selected)
    {
        text.setColor(baseColor);
    }

}

void TextButton::draw(sf::RenderWindow& window) {
    window.draw(text);
}

bool TextButton::mouseWithin() {
    int x = sf::Mouse::getPosition(mainWindow).x;
	int y = sf::Mouse::getPosition(mainWindow).y;
	return x > text.getPosition().x && x < text.getPosition().x + text.getGlobalBounds().width
		&& y > text.getPosition().y && y < text.getPosition().y + text.getGlobalBounds().height;
}
