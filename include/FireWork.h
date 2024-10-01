#pragma once
#include "Bezier.h"
#include "Vec2.h"
#include "sfml/Graphics.hpp"
#include <functional>
#include "assets.h"
#include <utility>

class FireWork
{
public:
	FireWork() = delete;
	FireWork(int id, Vec2 pathStart, Vec2 pathEnd, float anchorHeight, float stepIncrement, sf::Color color, std::function<void(FireWork&)> callback);

	void											StepParticle(float deltaTime);
	int												GetId();
	sf::Vector2f									GetCurrentPos();
	sf::Vector2f									GetEndPos();
	float											GetProgress();
	sf::Color										GetColor();



private:
	int mId;
	Bezier mPath;
	Vec2 mCurrentPos;
	Vec2 mPreviousPos;
	float mIncrement;
	float mStepProgress;
	std::function<void(FireWork&)> mCallback;
	bool mFinished;
	sf::Color mColor;
};