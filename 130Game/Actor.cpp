=====================================================================================================
-----------The features that this code provided had to be cut from the game due to time.-------------
=====================================================================================================



#include "Actor.h"
#include <iostream>

sf::Clock Actor::elapsedTimeClock;
float Actor::elapsedTime;
std::string Actor::anims[] = {"Cast",  "Walk", "Die" };


Actor::Actor(int x, int y, std::string name){
	spriteSheetTexture.loadFromFile("images/acto2r.png");
	sprite.setTexture(spriteSheetTexture);
	sprite.setPosition(x, y);
	currentAnimationPos.x = 0;
	this->name = name;
	currentAnimationPos.y = Animation::Down;
	movement = sf::Vector2i(0, 0);
	SetUpAnimation();
	texturePart.height = 64;
	texturePart.width = 64;
	sprite.setTextureRect(texturePart);
	animationClock = sf::Clock();
	animationClock.restart();
	currentDirection = Direction::None;
	isPlaying = true;
	SetRight();
	int test = 0;
};
void Actor::MoveOnGrid(int x, int y){
	//Drawn::MoveOnGrid(x, y);
};
void Actor::Move(float x, float y){
	//Drawn::Move(x, y);
};
void Actor::SetCurrentDirection(Direction a){
	currentDirection = a;
};
Actor::Direction Actor::GetCurrentDirection(){
	return currentDirection;
};
void Actor::SetMovement(sf::Vector2i a){
	movement = a;
};
bool Actor::SetRight(){
	if (currentDirection == None){
		LoopAnimation(animations["Walk"], Animation::Right);
		movement.x = 1;
		movement.y = 0;
		if(true){
			currentDirection = R;
			return true;
		}
		else
			return false;
	}
};
bool Actor::SetLeft(){
	if (currentDirection == None){
		LoopAnimation(animations["Walk"], Animation::Left);
		movement.x = -1;
		movement.y = 0;
		if(true){
			currentDirection = L;
			return true;
		}
		else
			return false;
	}
};
void Actor::Update(sf::RenderTexture* panel){
	elapsedTime = elapsedTimeClock.restart().asSeconds();
	UpdateEntity();
	UpdateAnimation();
};
void Actor::UpdateEntity(){
	sprite.setPosition(sprite.getPosition().x + (movement.x * 80 * elapsedTime), sprite.getPosition().y);
};
std::string Actor::GetName(){
	return name;
};
void Actor::SetUpAnimation(){
	AddAnimation(new Animation("Walk", 0.075, 8, 64, 3, 2));
	AddAnimation(new Animation("a9j3", 0.05, 16, 64, 0, 0));
	AddAnimation(new Animation("D209i", 0.05, 8, 64, 1, 1));
	AddAnimation(new Animation("s93", 0.025, 8, 64, 2, 3));
	AddAnimation(new Animation("Idle", 0.04, 1, 64, 7, 4));
};
bool Actor::UpdateAnimation(){
	if (isPlaying){
		if (((float)animationClock.getElapsedTime().asSeconds()) > currentAnimation->timePerFrame.asSeconds()){
			animationClock.restart();
			sprite.setColor(sf::Color(255, 255, 255, 255));
			sprite.setTextureRect(sf::IntRect(currentAnimationPos.x * currentAnimation->width, currentAnimationPos.y * currentAnimation->width, currentAnimation->width, currentAnimation->width));
			if (currentDirection != None){
				if (!isPaused)
					currentAnimationPos.x++;
			}
			if (currentAnimationPos.x == endFrame){
				if (isLooping)
					currentAnimationPos.x = startFrame;
				else{
					currentAnimationPos.x = 0;
					isPlaying = false;
				}
			}
			return true;
		}
	}
	else
		return false;
};
void Actor::LoopAnimation(Animation* anim, Animation::AnimDir dir){
	isPlaying = true;
	isLooping = true;
	this->startFrame = 0;
	if (anim->name == "Walk")
		this->startFrame = 1;
	this->endFrame = anim->numFrames;
	SetAnimation(anim, dir);
};
void Actor::PlayAnimation(Animation* anim, Animation::AnimDir dir){
	isPlaying = true;
	isLooping = false;
	this->startFrame = 0;
	if (anim->name == "Walk")
		this->startFrame = 1;
	this->endFrame = anim->numFrames;
	SetAnimation(anim, dir);
};
void Actor::PlayAnimation(Animation* anim, Animation::AnimDir dir, int startFrame, int endFrame){
	isPlaying = true;
	isLooping = false;
	this->startFrame = startFrame;
	this->endFrame = endFrame;
	SetAnimation(anim, dir);
};
void Actor::PauseAnimation(){
	isPaused = true;
};
void Actor::ResumeAnimation(){
	isPaused = false;
	currentAnimationPos.x++;
	animationClock.restart();
};
void Actor::SetAnimation(Animation* anim, Animation::AnimDir dir){
	animationClock.restart();
	if (currentAnimation == NULL || currentAnimation->name != anim->name || currentAnimationDir != dir){
		currentAnimation = anim;
		currentAnimationDir = dir;
		if (anim->name == "Walk")
			currentAnimationPos.x = 0;
		currentAnimationPos.y = currentAnimation->GetY();
	}
}
void Actor::AddAnimation(Animation* anim){
	animations.insert(AnimationPair(anim->name, anim));
};
