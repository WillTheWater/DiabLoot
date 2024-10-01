#include "FireWork.h"

FireWork::FireWork(int id, Vec2 pathStart, Vec2 pathEnd, float anchorHeight, float stepIncrement, sf::Color color, std::function<void(FireWork&)> callback)
	:mId{ id }
	, mPath{ pathStart, pathEnd, anchorHeight }
	, mStepProgress(0)
	, mIncrement(stepIncrement)
	, mCallback(callback)
	, mPreviousPos(pathStart)
	, mCurrentPos(pathStart)
	, mFinished{ false }
	, mColor{color}
{
}

void FireWork::StepParticle(float deltaTime)
{
	if (mFinished)
	{
		mCallback(*this);
		return;

	}
	mStepProgress += mIncrement * deltaTime;
	if (mStepProgress >= 1.0)
	{
		mStepProgress = 1.0;
		mFinished = true;
	}
	mPreviousPos = mCurrentPos;
	mCurrentPos = mPath.ResultPoint(std::clamp<float>(mStepProgress, 0.f, 1.f));
}

int FireWork::GetId()
{
	return mId;
}

sf::Vector2f FireWork::GetCurrentPos()
{
	return mCurrentPos.getAsSFVec2F();
}

sf::Vector2f FireWork::GetEndPos()
{
	return mPath.GetEndPos().getAsSFVec2F();
}

float FireWork::GetProgress()
{
	return mStepProgress;
}

sf::Color FireWork::GetColor()
{
	return mColor;
}


