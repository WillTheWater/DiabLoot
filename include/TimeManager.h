#pragma once
#include <SFML/System/Clock.hpp>


class TimeManager
{
public:
	void								Tick() { mDeltaTime = mClock.restart().asSeconds(); }
	float								GetDeltaTime() const { return mDeltaTime; }
	void								StartSpeedRunclock() { mSpeedRunClock.restart(); mSpeedRun = true; }
	bool								IsSpeedrun() { return mSpeedRun; }
	float								GetSpeedRunTime() { return mSpeedRunClock.getElapsedTime().asSeconds(); }

private:
	sf::Clock							mClock;
	bool								mSpeedRun = false;
	sf::Clock							mSpeedRunClock;
	float								mDeltaTime = 0;
};