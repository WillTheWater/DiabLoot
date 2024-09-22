#include "Particle.h"

Particle::Particle(int id, sf::Vector2f pathStart, sf::Vector2f pathEnd, float anchorHeight, float stepIncrement, std::function<void(Particle&)> callback)
	:mId{id}
	,mPath(Vec2(pathStart), Vec2(pathEnd), anchorHeight)
	,mStepProgress(0)
	,mIncrement(stepIncrement)
	,mCallback(callback)
	,mPreviousPos(pathStart)
	,mCurrentPos(pathStart)
	,mFinished{false}
{
}

void Particle::stepParticle()
{
	if (mFinished)
	{
		mCallback(*this);
		return;
		
	}
	mStepProgress += mIncrement;
	if (mStepProgress > 1.0)
	{
		mStepProgress = 1.0;
		mFinished = true;
	}
	mPreviousPos = mCurrentPos;
	mCurrentPos = mPath.resultPoint(mStepProgress);	
}

int Particle::getId()
{
	return mId;
}

sf::Vector2f Particle::getCurrentPos()
{
	return mCurrentPos.getAsSFVec2F();
}

sf::Vector2f Particle::getEndPos()
{
	return mPath.getEndPos().getAsSFVec2F();
}

