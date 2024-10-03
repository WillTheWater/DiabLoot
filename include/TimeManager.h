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
	int									GetGheedAnimFrame() { return mGheedAnimFrame; }
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

	void UpdateGheedAnimFrame()
	{
		mGheedTimer += mDeltaTime;
		if (mGheedTimer >= mGheedFrameDuration)
		{
			mGheedAnimFrame = (mGheedAnimFrame + 1) % mGheedAnimMaxFrames;
			mGheedTimer = 0.0f;
		}
	}

	void UpdateRainProgress() 
	{ 
		mRainProgressFG.first += ((mRainIncrementFG / 3.f) * mDeltaTime); 
		mRainProgressFG.second += (mRainIncrementFG * mDeltaTime); 
		mRainProgressBG.first += ((mRainIncrementBG / 3.5f) * mDeltaTime);
		mRainProgressBG.second += ((mRainIncrementBG / 1.2f) * mDeltaTime);
		if (mRainProgressFG.first > 1.0) 
		{ 
			mRainProgressFG.first = (mRainProgressFG.first - 1.0f); 
		} 
		if (mRainProgressFG.second > 1.0)
		{
			mRainProgressFG.second = (mRainProgressFG.second - 1.0f);
		}
		if (mRainProgressBG.first > 1.0)
		{
			mRainProgressBG.first = (mRainProgressBG.first - 1.0f);
		}
		if (mRainProgressBG.second > 1.0)
		{
			mRainProgressBG.second = (mRainProgressBG.second - 1.0f);
		}
	}

	void UpdateThunderProgress()
	{
		mThunderProgress += mThunderIncrement * mDeltaTime;
		if (mThunderProgress > 1.0)
		{
			mThunderProgress = 0.f;
		}
	}

	const std::pair<float, float>	GetRainProgressFG()		{ return mRainProgressFG; }
	const std::pair<float, float>	GetRainProgressBG()		{ return mRainProgressBG; }

	const float						GetThunderProgress()	{ return mThunderProgress; }

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
	// Gheed Animation
	float								mGheedTimer = 0.f;
	float								mGheedFrameDuration = 0.1f;
	int									mGheedAnimFrame = 0;
	int									mGheedAnimMaxFrames = 8;
	// Rain Animation
	std::pair<float, float>				mRainProgressFG = { 0.f, 0.f };
	std::pair<float, float>				mRainProgressBG = { 0.f, 0.f };
	float								mRainIncrementFG = 0.3f;
	float								mRainIncrementBG = 0.5f;
	float								mThunderProgress = 0.f;
	float								mThunderIncrement = 2.5f;
};