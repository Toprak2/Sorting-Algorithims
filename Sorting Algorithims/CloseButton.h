#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
class CloseButton :public Button
{
public:
	
	CloseButton(float button_size_x, float button_size_y, float button_position_x, float button_position_y, sf::Color button_color, std::string text,sf::Font* font);

	void turnOff(Button* button_);
private:
};

