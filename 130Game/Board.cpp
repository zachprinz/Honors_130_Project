#include "Board.h"

Board::Board(){
	backgroundTexture.loadFromFile("images/title.png");
	backgroundBlackTexture.loadFromFile("images/black.png");
	backgroundFadeTexture.loadFromFile("images/fade.png");
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setPosition(sf::Vector2f(0, 0));
	boardTexture.create(1380, 297);
	boardSprite.setTexture(boardTexture.getTexture());
	backgroundBlackSprite.setTexture(backgroundBlackTexture);
	backgroundFadeSprite.setTexture(backgroundFadeTexture);
	user = new User();
	int test2 = 0;
}
void Board::Update(){
	boardTexture.clear();
	backgroundFadeSprite.setColor(sf::Color(255, 255, 255, brightness));
	backgroundBlackSprite.setColor(sf::Color(255, 255, 255, (int)brightness % 255));
	boardTexture.draw(backgroundSprite);
	user->Update(&boardTexture);
	boardTexture.draw(backgroundFadeSprite);
	boardTexture.draw(backgroundBlackSprite);
	boardTexture.display();
}
sf::Sprite Board::getRender(){
	boardSprite.setTexture(boardTexture.getTexture());
	return boardSprite;
}
void Board::onDeath(){

}
void Board::darken(){
	if (brightness < 505)
		brightness += 0.1;
}
void Board::brighten(){

}
void Board::shake(){

}
void Board::draw(sf::RenderTexture* panel){
	panel->draw(boardSprite);
};