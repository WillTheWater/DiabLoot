#include "Level.h"

Level::Level(LEVELS::LEVEL id, TimeManager& timemgr, InputManager& inputmgr, std::function<sf::Text&(ITEMID::ITEM)> itemTextCB)
	:mLevelID{id}
	,mTimeManager{timemgr}
	,mInputManager{inputmgr} 
	,mParticleUniqueId{ 0 }
	,mItemTextCB(itemTextCB)
{
	mChests.reserve(10);
	mParticles.reserve(20);
	CreateLevelChests();
}

Level::~Level()
{
	for (auto& chest : mChests)
	{
		mInputManager.RemoveObserver(chest.get());
	}
}

LEVELS::LEVEL Level::GetLevelId() const
{
	return mLevelID;
}

std::vector<std::unique_ptr<Item>>& Level::GetItems()
{
	return mItems;
}

std::vector<std::unique_ptr<Chest>>& Level::GetChests()
{
	return mChests;
}

std::vector<std::unique_ptr<Particle>>& Level::GetParticles()
{
	return mParticles;
}

void Level::UpdateLevel()
{
	UpdateParticles();
}

void Level::CreateLevelChests()
{
	switch (mLevelID)
	{
	case LEVELS::LEVEL_ONE : 
		SpawnChest({ 500.f, 600.f }, true);
		SpawnChest({ 1000.f, 800.f }, false);
	}
}

int Level::GetUniqueParticleId()
{
	mParticleUniqueId++;
	return mParticleUniqueId;
}

void Level::SpawnChest(sf::Vector2f pos, bool mirrored)
{
	// Update this to have actual chest positions
	std::function<void(Chest&)> callback = [this](Chest& chest) {this->SpawnParticles(chest); };
	mChests.push_back(std::make_unique<Chest>(pos, mirrored, callback));
	mInputManager.AddObserver(mChests.back().get());
}

void Level::SpawnParticles(Chest& chest)
{
	int numOfParticles = MathU::Random(8, 16);
	// Need to solve the function bind problem below
	std::function<void(Particle&)> callback = [this](Particle& particle) {this->SpawnItem(particle); };
	float animStep = 2.0f;
	for (int i{ 0 }; i < numOfParticles; i++)
	{
		float randDist = MathU::Random(30.f, 60.f);
		float randAngle = MathU::Random(0.f, 360.f);
		float randAnchorheight = MathU::Random(60.f, 120.f) * -1;
		Vec2 endPos{ randDist, 0 };
		Vec2 startPos{ chest.GetPosition() };
		endPos = endPos.getRotatedVector(randAngle);
		endPos = startPos + endPos;
		int id = GetUniqueParticleId();
		std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> itemId = ITEMGEN::getRandomItem();
		mParticles.push_back(std::make_unique<Particle>(id, startPos, endPos, randAnchorheight, animStep, callback, itemId));
	}
	mInputManager.RemoveObserver(&chest);
}

void Level::UpdateParticles()
{
	for (auto& particle : mParticles)
	{
		if (particle == nullptr)
		{
			continue;
		}
		particle->stepParticle(mTimeManager.GetDeltaTime());
	}
}

void Level::RemoveParticle(Particle& particle)
{
	bool success = false;

	for (int i{ 0 }; i < mParticles.size(); i++)
	{
		if (mParticles[i]->getId() == particle.getId())
		{
			mParticles.erase(mParticles.begin() + i);
			success = true;
		}
	}
	assert(success && "PlayState::RemoveParticle failed to remove the particle");
}

void Level::SpawnItem(Particle& particle)
{
	sf::Vector2f position = particle.getEndPos();
	std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> itemId = particle.getItemID();
	sf::Text& text = mItemTextCB(itemId.first);
	mItems.push_back(std::make_unique<Item>(itemId, position, text, 1));
	RemoveParticle(particle);
}

void Level::SortItemsByVerticalSpace()
{

}