#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <cmath>

class Animation
{
public:
	enum AnimDir { Up, Down, Left, Right };
	Animation(std::string name, float perFrame, int numFramesA, int width, int y, int id);
	int GetY();
	int numFrames;
	int y;
	sf::Time timePerFrame;
	std::string name;
	int width;
	int id;
private:

};

#endif