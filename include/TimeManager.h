#pragma once
#include <SFML/System/Clock.hpp>


class TimeManager
{
public:
	void								Tick() { mDeltaTime = mClock.restart().asSeconds(); }
	float								GetDeltaTime() const { return mDeltaTime; }

private:
	sf::Clock							mClock;
	float								mDeltaTime = 0;
};