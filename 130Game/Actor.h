#ifndef ACTOR_H
#define ACTOR_H

#include<SFML/Graphics.hpp>
#include<map>
#include"Animation.h"

class Actor
{
public:
	////////////
	Actor(int, int, std::string);
	void MoveOnGrid(int, int);
	void Move(float, float);
	enum Direction { None, L, R };
	static std::string anims[6];
	void SetCurrentDirection(Direction);
	Direction GetCurrentDirection();
	sf::Vector2i GetMovement();
	void SetMovement(sf::Vector2i);
	std::string GetName();

	//Animation//
	static float elapsedTime;
	typedef std::map<std::string, Animation*> AnimationMap;
	typedef std::pair<std::string, Animation*> AnimationPair;

	void LoopAnimation(Animation*, Animation::AnimDir);
	void PlayAnimation(Animation*, Animation::AnimDir);
	void PlayAnimation(Animation*, Animation::AnimDir, int, int);
	void PauseAnimation();
	void ResumeAnimation();

	Animation* currentAnimation;
	sf::Vector2i currentAnimationPos;
	AnimationMap animations;
	sf::Sprite animationSprite;
	virtual void Update(sf::RenderTexture* panel);

protected:
	bool UpdateAnimation();
	std::vector<sf::IntRect> animationSheets;
	Animation::AnimDir currentAnimationDir;
	void UpdateEntity();
	std::string name;
	Direction currentDirection;
	sf::Vector2i movement;
	bool SetRight();
	bool SetLeft();
	sf::Clock animationClock; 
	////////////////
	sf::Texture spriteSheetTexture;
	sf::Sprite sprite;
private:
	int frame;
	//////////
	sf::IntRect texturePart;
	bool isLooping;
	bool isPlaying;
	bool isPaused;
	void SetAnimation(Animation*, Animation::AnimDir);
	void AddAnimation(Animation*);
	void SetUpAnimation();
	int startFrame;
	int endFrame;
	static sf::Clock elapsedTimeClock;

};
#endif