#ifndef BOARD_H
#define BOARD_H

#include<SFML/graphics.hpp>
#include"User.h"

class Board
{
public:
	Board();
	sf::Sprite getRender();
	void Update();
	void onDeath();
	void draw(sf::RenderTexture*);
protected:

private:
	void shake();
	void darken();
	void brighten();
	sf::RenderTexture boardTexture;
	sf::Sprite boardSprite;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Texture backgroundFadeTexture;
	sf::Texture backgroundBlackTexture;
	sf::Sprite backgroundFadeSprite;
	sf::Sprite backgroundBlackSprite;
	double brightness = 0;
	User* user;
};
#endif