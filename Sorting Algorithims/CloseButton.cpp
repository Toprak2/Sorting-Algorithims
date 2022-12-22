#include "CloseButton.h"

CloseButton::CloseButton(float button_size_x, float button_size_y, float button_position_x, float button_position_y, sf::Color button_color,std::string text,sf::Font* font)
	:Button(button_size_x,button_size_y,button_position_x,button_position_y,button_color,text,font)
	
{
}

void CloseButton::turnOff(Button* button_)
{
	button_->setIsActive(false);
}
