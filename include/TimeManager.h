#pragma once
#include <SFML/System/Clock.hpp>
#include <iostream>


class TimeManager
{
public:
	void								Tick() { mDeltaTime = mClock.restart().asSeconds(); }
	float								GetDeltaTime() const { return mDeltaTime; }
	void								StartSpeedRunclock() { mSpeedRunClock.restart(); mSpeedRun = true; mHasTimeBeenLocked = false; }
	bool								IsSpeedrun() { return mSpeedRun; }
	float								GetSpeedRunTime() { return mSpeedRunTime; }
	int									GetFireAnimFrame() { return mFireAnimFrame; }
	int									GetFPS() { return (int)(1.f / mDeltaTime); }
	void								PrintTimeStats() { std::cout << "FPS: " << GetFPS() << " DeltaTime: " << GetDeltaTime() << '\n'; }
	void LockSpeedRunTime() 
	{ 
		if (!mHasTimeBeenLocked)
		{
			mSpeedRunTime = mSpeedRunClock.getElapsedTime().asMilliseconds();
			mHasTimeBeenLocked = true;
		}
	}
	void UpdateFireFrame()
	{
		mFireFrameTimer += mDeltaTime;
		if (mFireFrameTimer >= mFireFrameDuration)
		{
			mFireAnimFrame = (mFireAnimFrame + 1) % mFireAnimMaxFrames;
			mFireFrameTimer = 0.0f;
		}
	}

private:
	sf::Clock							mClock;
	bool								mSpeedRun = false;
	bool								mHasTimeBeenLocked = false;
	sf::Clock							mSpeedRunClock;
	float								mSpeedRunTime;
	float								mDeltaTime = 0;
	// Fire Animation
	float								mFireFrameTimer = 0.f;
	float								mFireFrameDuration = 0.03f;
	int									mFireAnimFrame = 0;
	int									mFireAnimMaxFrames = 20;
};