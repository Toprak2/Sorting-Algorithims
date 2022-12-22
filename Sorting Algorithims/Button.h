#pragma once
#include<SFML/Graphics.hpp> 


class Button
{
private:
	sf::RectangleShape button;
	bool is_active;
	
	sf::Text button_text;
public:
	Button(sf::Vector2f button_size, sf::Vector2f button_position, sf::Color button_color);
	Button(float button_size_x, float button_size_y, float button_position_x, float button_position_y, sf::Color button_color, std::string text, sf::Font* font);
	~Button();
	bool isClicked(sf::Event* event);
	void setIsActive(bool value);
	bool getIsActive();
	void draw(sf::RenderTarget* render_target);
	sf::RectangleShape getButton();
};

