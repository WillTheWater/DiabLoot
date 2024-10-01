#pragma once
#include "FireWork.h"
#include <Vector>
#include <Array>
#include "MathUtilities.h"
#include <iostream>

class FireWorkSystem
{
public:
	FireWorkSystem();
	void				Update(float deltaTime);
	void				StartFireworks();
	void				EndFireWorks();
	void				RenderFireWorks();
	void				CreateSparks(FireWork& fireWork);
	void				RemoveSpark(FireWork& spark);

	const std::vector<std::unique_ptr<FireWork>>& GetFireWorks() const;
	const std::vector<std::unique_ptr<FireWork>>&	GetSparks() const;


private:
	bool mPlaying = false;
	std::vector<std::unique_ptr<FireWork>>	mFireWorks;
	std::vector<std::unique_ptr<FireWork>>	mSparks;
	std::array<sf::Color, 6>				mColors;

	sf::Color			GetRandomColor();
	void				CreateFireWork();
	void				RemoveFireWork(FireWork& fireWork);
	Vec2				GetRandomPointInCircle(Vec2 startPos, float minRadius, float maxRadius, float maxAngle);
	int					GetUniqueId();
	int					mUniqueId = 0;

};