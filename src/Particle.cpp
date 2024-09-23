#include "Particle.h"

Particle::Particle(int id, Vec2 pathStart, Vec2 pathEnd, float anchorHeight, float stepIncrement, std::function<void(Particle&)> callback, std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> itemId)
	:mId{id}
	,mPath{ pathStart, pathEnd, anchorHeight }
	,mStepProgress(0)
	,mIncrement(stepIncrement)
	,mCallback(callback)
	,mPreviousPos(pathStart)
	,mCurrentPos(pathStart)
	,mFinished{false}
	,mItemID{itemId}
{
}

void Particle::stepParticle(float deltaTime)
{
	if (mFinished)
	{
		mCallback(*this);
		return;
		
	}
	mStepProgress += mIncrement * deltaTime;
	if (mStepProgress >= 1.2)
	{
		mStepProgress = 1.0;
		mFinished = true;
	}
	mPreviousPos = mCurrentPos;
	mCurrentPos = mPath.resultPoint(std::clamp<float>(mStepProgress, 0.f, 1.f));
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

std::pair<ITEMID::ITEM, ITEMRARITY::RARITY>	Particle::getItemID()
{
	return mItemID;
}
