#pragma once
#include "Bezier.h"
#include "Vec2.h"
#include "sfml/Graphics.hpp"
#include <functional>

class Particle
{
public:
	// Constructors
	Particle() = delete;
	// anchorHeight sets how hight the partile travels, stepIncrement is used to go between 0 to 1 each step for the animation, 
	// callback is the function called when the particle lands
	Particle(int id, Vec2 pathStart, Vec2 pathEnd, float anchorHeight, float stepIncrement, std::function<void(Particle&)> callback);

	void						stepParticle(float deltaTime);
	int							getId();
	sf::Vector2f				getCurrentPos();
	sf::Vector2f				getEndPos();



private:
	int mId;
	Bezier mPath;
	Vec2 mCurrentPos;
	Vec2 mPreviousPos;
	float mIncrement;
	float mStepProgress;
	std::function<void(Particle&)> mCallback;
	bool mFinished;
	
};