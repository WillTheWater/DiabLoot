#pragma once
#include <SFML/System/Clock.hpp>


class TimeManager
{
public:
	void								Tick() { mDeltaTime = mClock.restart().asSeconds(); }
	float								GetDeltaTime() const { return mDeltaTime; }
	void								StartSpeedRunclock() { mSpeedRunClock.restart(); mSpeedRun = true; mHasTimeBeenLocked = false; }
	bool								IsSpeedrun() { return mSpeedRun; }
	float								GetSpeedRunTime() { return mSpeedRunTime; }
	void LockSpeedRunTime() 
	{ 
		if (!mHasTimeBeenLocked)
		{
			mSpeedRunTime = mSpeedRunClock.getElapsedTime().asMilliseconds();
			mHasTimeBeenLocked = true;
		}
	}

private:
	sf::Clock							mClock;
	bool								mSpeedRun = false;
	bool								mHasTimeBeenLocked = false;
	sf::Clock							mSpeedRunClock;
	float								mSpeedRunTime;
	float								mDeltaTime = 0;
};