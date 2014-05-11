#include"Animation.h"

Animation::Animation(std::string name, float perFrame, int numFramesA, int width, int y, int id){
	this->name = name;
	timePerFrame = sf::seconds(perFrame);
	numFrames = numFramesA;
	this->y = y;
	this->width = width;
	this->id = id;
};
int Animation::GetY(){
	return y;
}