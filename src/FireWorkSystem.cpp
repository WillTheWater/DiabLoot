#include "FireWorkSystem.h"

FireWorkSystem::FireWorkSystem()
	:mUniqueId{0}
{
	mFireWorks.reserve(12);
	mSparks.reserve(120);

	mColors[0] = sf::Color{ 51, 102, 255 };
	mColors[1] = sf::Color{ 253, 216, 53 };
	mColors[2] = sf::Color{ 44 , 190, 52 };
	mColors[3] = sf::Color{ 153, 102, 51 };
	mColors[4] = sf::Color{ 198, 140, 89 };
	mColors[5] = sf::Color::Red;
}

void FireWorkSystem::Update(float deltaTime)
{
	if (mFireWorks.size() > 0)
	{
		for (auto& firework : mFireWorks)
		{
			firework->StepParticle(deltaTime);
		}
	}
	if (mSparks.size() > 0)
	{
		for (auto& spark : mSparks)
		{
			spark->StepParticle(deltaTime);
		}
	}
	RemoveOldSparks();
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


void FireWorkSystem::CreateSparks(FireWork& fireWork)
{
	Vec2 startPos{ fireWork.GetEndPos() };
	std::function<void(FireWork&)> callback = [this](FireWork& spark) {this->QueueSparkForDeletion(spark); };
	for (int i{ 0 }; i < 10; i++)
	{
		float randDist = MathU::Random(100.f, 200.f);
		Vec2 endPos{ randDist, 0 };
		endPos = endPos.getRotatedVector((360.f / 10.f) * i);
		endPos = startPos + endPos;
		float randomHeight = -MathU::Random(150.f, 200.f);
		float stepIncrement = MathU::Random(0.5f, 0.6f);
		int id = GetUniqueId();
		mSparks.push_back(std::make_unique<FireWork>(id, startPos, endPos, randomHeight, stepIncrement, fireWork.GetColor(), callback));
	}
	RemoveFireWork(fireWork);
	CreateFireWork();
}

void FireWorkSystem::QueueSparkForDeletion(FireWork& spark)
{
	mSparksToDelete.push_back(spark.GetId());
}

sf::Color FireWorkSystem::GetRandomColor()
{
	int randomIndex = MathU::Random(0, (int)(mColors.size() - 1));
	return mColors[randomIndex];
}

void FireWorkSystem::CreateFireWork()
{
	Vec2 startPos{ 1920.f /2.f, 980.f };
	Vec2 endPos{ GetRandomPointInCircle(startPos, 500.f, 800.f, 180.f) };
	float randomHeight = -MathU::Random(200.f, 200.f);
	float stepIncrement = MathU::Random(0.3f, 0.5f);
	int id = GetUniqueId();
	sf::Color color = GetRandomColor();
	std::function<void(FireWork&)> callback = [this](FireWork& fireWork) {this->CreateSparks(fireWork); };
	mFireWorks.push_back(std::make_unique<FireWork>(id, startPos, endPos, randomHeight, stepIncrement, color, callback));
}

void FireWorkSystem::RemoveFireWork(FireWork& fireWork)
{
	for (int i{ 0 }; i < mFireWorks.size(); i++)
	{
		if (mFireWorks[i]->GetId() == fireWork.GetId())
		{
			mFireWorks.erase(mFireWorks.begin() + i);
			return;
		}
	}
}

void FireWorkSystem::RemoveSparkWithID(int id)
{
	for (int i{ 0 }; i < mSparks.size(); i++)
	{
		if (mSparks[i]->GetId() == id)
		{
			mSparks.erase(mSparks.begin() + i);
			break;
		}
	}
		
}

void FireWorkSystem::RemoveOldSparks()
{
	for (auto& id : mSparksToDelete)
	{
		RemoveSparkWithID(id);
	}
	mSparksToDelete.clear();
	mSparksToDelete.reserve(10);
}

const std::vector<std::unique_ptr<FireWork>>& FireWorkSystem::GetFireWorks() const
{
	return mFireWorks;
}

const std::vector<std::unique_ptr<FireWork>>& FireWorkSystem::GetSparks() const
{
	return mSparks;
}

Vec2 FireWorkSystem::GetRandomPointInCircle(Vec2 startPos, float minRadius, float maxRadius, float maxAngle)
{
	float randDist = MathU::Random(minRadius, maxRadius);
	float randAngle = MathU::Random(0.f, maxAngle);
	Vec2 endPos{ -randDist, 0 };
	endPos = endPos.getRotatedVector(randAngle);
	endPos = startPos + endPos;
	return endPos;
}

int FireWorkSystem::GetUniqueId()
{
	mUniqueId++;
	return mUniqueId;
}
