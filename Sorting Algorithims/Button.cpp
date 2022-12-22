#include "Button.h"

Button::Button(sf::Vector2f button_size, sf::Vector2f button_position, sf::Color button_color)
{
	//initalize the buttons size,position,color
	this->button.setSize(button_size);
	this->button.setPosition(button_position);
	this->button.setFillColor(button_color);
	//set the bool to the false
	this->is_active = false;
}

Button::Button(float button_size_x, float button_size_y, float button_position_x, float button_position_y, sf::Color button_color,std::string text,sf::Font* font)
{
	//initalize the buttons size,position,color
	this->button.setSize(sf::Vector2f(button_size_x, button_size_y));
	this->button.setPosition(button_position_x, button_position_y);
	this->button.setFillColor(button_color);
	this->button.setOutlineColor(sf::Color::Black);
	this->button.setOutlineThickness(1);
	//set the bool to the false
	this->is_active = false;
	//Initialize the text

	
	button_text.setFont(*font);
	button_text.setCharacterSize(25);
	button_text.setFillColor(sf::Color::Black);
	button_text.setString(text);
	button_text.setOrigin((button_text.getLocalBounds().left + button_text.getLocalBounds().width) / 2.f, (button_text.getLocalBounds().top + button_text.getLocalBounds().height) / 2.f);
	button_text.setPosition(button_position_x + button_size_x / 2, button_position_y + button_size_y / 2);

	//scale the text to fit to the button
	if (button_text.getLocalBounds().width > button.getLocalBounds().width)
	{
		double scale_percent = ((button.getLocalBounds().width*100)/ button_text.getLocalBounds().width)/100;
		button_text.setScale(scale_percent, scale_percent);
	}

}

Button::~Button()
{
}

bool Button::isClicked(sf::Event* event)
{
	if (event->mouseButton.x > button.getGlobalBounds().left &&
		event->mouseButton.x < button.getGlobalBounds().left + button.getGlobalBounds().width &&
		event->mouseButton.y>button.getGlobalBounds().top &&
		event->mouseButton.y < button.getGlobalBounds().top + button.getGlobalBounds().height)
	{
		return true;
	}
	return false;
}

void Button::setIsActive(bool value)
{
	this->is_active = value;
}

bool Button::getIsActive()
{
	return is_active;
}

void Button::draw(sf::RenderTarget* render_target)
{
	
	render_target->draw(button);
	render_target->draw(button_text);
}

sf::RectangleShape Button::getButton()
{
	return button;
}