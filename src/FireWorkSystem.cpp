#include "FireWorkSystem.h"

FireWorkSystem::FireWorkSystem()
{
	mFireWorks.reserve(12);
	mSparks.reserve(120);

	mColors[0] = sf::Color::Blue;
	mColors[1] = sf::Color::Red;
	mColors[2] = sf::Color::Green;
	mColors[3] = sf::Color::Cyan;
	mColors[4] = sf::Color::Yellow;
	mColors[5] = sf::Color::Magenta;
}

void FireWorkSystem::StartFireworks()
{
	if (mPlaying)
	{
		return;
	}
	mPlaying = true;
	for (int i{ 0 }; i < 12; i++)
	{
		CreateFireWork();
	}
}

void FireWorkSystem::EndFireWorks()
{
	mPlaying = false;
	mFireWorks.clear();
	mSparks.clear();
}

void FireWorkSystem::RenderFireWorks()
{
}

void FireWorkSystem::CreateSparks(FireWork& fireWork)
{
	Vec2 startPos{ fireWork.GetEndPos() };
	std::function<void(FireWork&)> callback = [this](FireWork& spark) {this->RemoveSpark(spark); };
	for (int i{ 0 }; i < 10; i++)
	{
		float randDist = MathU::Random(30.f, 50.f);
		Vec2 endPos{ -randDist, 0 };
		endPos = endPos.getRotatedVector(360.f / i);
		endPos = startPos + endPos;
		float randomHeight = MathU::Random(5.f, 10.f);
		float stepIncrement = MathU::Random(0.05f, 0.1f);
		int id = GetUniqueId();
		mSparks.emplace_back(std::make_unique<FireWork>(id, startPos, endPos, randomHeight, stepIncrement, fireWork.GetColor(), callback));
	}

	RemoveFireWork(fireWork);
	CreateFireWork();
}

sf::Color FireWorkSystem::GetRandomColor()
{
	int randomIndex = MathU::Random(0, (int)(mColors.size() - 1));
	return mColors[randomIndex];
}

void FireWorkSystem::CreateFireWork()
{
	Vec2 startPos{ 600.f, 600.f };
	Vec2 endPos{ GetRandomPointInCircle(startPos, 50.f, 200.f, 180.f) };
	float randomHeight = MathU::Random(50.f, 100.f);
	float stepIncrement = MathU::Random(0.01f, 0.05f);
	int id = GetUniqueId();
	sf::Color color = GetRandomColor();
	std::function<void(FireWork&)> callback = [this](FireWork& fireWork) {this->CreateSparks(fireWork); };
	mFireWorks.emplace_back(std::make_unique<FireWork>(id, startPos, endPos, randomHeight, stepIncrement, color, callback));
}

void FireWorkSystem::RemoveFireWork(FireWork& fireWork)
{
	for (int i{ 0 }; i < mFireWorks.size(); i++)
	{
		if (mFireWorks[i] == nullptr)
		{
			continue;
		}
		if (mFireWorks[i]->GetId() == fireWork.GetId())
		{
			mFireWorks.erase(mFireWorks.begin() + i);
			break;
		}
	}
}

void FireWorkSystem::RemoveSpark(FireWork& spark)
{
	for (int i{ 0 }; i < mSparks.size(); i++)
	{
		if (mSparks[i] == nullptr)
		{
			continue;
		}
		if (mSparks[i]->GetId() == spark.GetId())
		{
			mFireWorks.erase(mSparks.begin() + i);
			break;
		}
	}
}

Vec2 FireWorkSystem::GetRandomPointInCircle(Vec2 startPos, float minRadius, float maxRadius, float maxAngle)
{
	float randDist = MathU::Random(minRadius, maxRadius);
	float randAngle = MathU::Random(0.f, maxAngle);
	Vec2 endPos{ -randDist, 0 };
	endPos = endPos.getRotatedVector(randAngle);
	endPos = startPos + endPos;
}

int FireWorkSystem::GetUniqueId()
{
	int id = mUniqueId;
	mUniqueId++;
	return id;
}
