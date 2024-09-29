#include "Level.h"
#include "SystemManager.h"

Level::Level(LEVELS::LEVEL id, System& system)
	:mLevelID{id}
	,mSystem{system}
	,mParticleUniqueId{0}
	,mUpgradeLevel{LEVELS::UPGRADE::ONE_CHEST}
{
	mChests.reserve(10);
}

Level::~Level()
{
	ExitLevel();
}

LEVELS::LEVEL Level::GetLevelId() const
{
	return mLevelID;
}

void Level::EnterLevel()
{
	ActivateChests();
}

void Level::ExitLevel()
{
	RemoveAllItemObservers();
	RemoveAllChestObservers();
	DeactiveChests();
	mItems.clear();
	mParticles.clear();
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
	UpdateItems();
}

void Level::UpdateItems()
{
	if (mItems.size() > 0)
	{
		SortItemsByVerticalSpace();
		StackItemlabels();
	}
}

int Level::GetUniqueParticleId()
{
	mParticleUniqueId++;
	return mParticleUniqueId;
}

void Level::SpawnChest(sf::Vector2f pos, bool mirrored)
{
	std::function<void(Chest&)> callback = [this](Chest& chest) {this->SpawnParticles(chest); };
	mChests.push_back(std::make_unique<Chest>(pos, mirrored, callback));
}

void Level::SpawnParticles(Chest& chest)
{
	int numOfParticles = MathU::Random(8, 16);
	// Need to solve the function bind problem below
	std::function<void(Particle&)> callback = [this](Particle& particle) {this->SpawnItem(particle); };
	float animStep = MathU::Random(PARTICLE::ANIMSTEP - 0.08f, PARTICLE::ANIMSTEP + 0.08f);
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
	mSystem.InputMgr.RemoveObserver(&chest);
}

void Level::CreateBounceParticle(Item& item)
{
	std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> itemId = { ITEMID::GOLD, ITEMRARITY::GOLD };
	Vec2 startPos = item.getPosition();
	Vec2 endPos = startPos;
	int id = GetUniqueParticleId();
	float randAnchorheight = MathU::Random(60.f, 120.f) * -1;
	float animStep = PARTICLE::ANIMSTEP;
	std::function<void(Particle&)> callback = [this](Particle& particle) {this->TurnItemToGold(particle); };
	mParticles.push_back(std::make_unique<Particle>(id, startPos, endPos, randAnchorheight, animStep, callback, itemId));
}

void Level::UpdateParticles()
{
	for (auto& particle : mParticles)
	{
		if (particle == nullptr)
		{
			continue;
		}
		particle->stepParticle(mSystem.TimeMgr.GetDeltaTime());
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

void Level::PickUpItem(Item& item)
{
	bool couldAdd = mSystem.InventoryMgr.addItem(item);
	
	bool success = false;
	for (int i{ 0 }; i < mItems.size(); i++)
	{
		if (mItems[i]->getUniqueId() == item.getUniqueId())
		{
			if (!couldAdd)
			{
				CreateBounceParticle(item);
				auto pitchShifter = MathU::Random(0.8f, 1.2f);
				auto modulator = MathU::Random(20.f, 40.f);
				SoundManager::GetInstance().PlaySound(PLAYSOUND::ITEM_FLIP, modulator, pitchShifter);
			}
			RemoveAllItemObservers();
			mItems.erase(mItems.begin() + i);
			AddAllItemObservers();
			success = true;
		}
	}

	assert(success && "PlayState::RemoveItem failed to remove the item");
	
	
}

void Level::SpawnItem(Particle& particle)
{
	sf::Vector2f position = particle.getEndPos();
	std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> itemId = particle.getItemID();
	sf::Text& text = mSystem.AssetMgr.GetTextForItemID(itemId.first);
	std::function<void(Item&)> callback = [this](Item& item) {this->PickUpItem(item); };
	int uniqueId = particle.getId();
	RemoveAllItemObservers();
	int quantity = 1;
	if (itemId.first == ITEMID::GOLD)
	{
		quantity = ITEMGEN::getRandomGoldAmount();
	}
	mItems.push_back(std::make_unique<Item>(itemId, uniqueId, position, text, callback, quantity));
	AddAllItemObservers();		// TESTING
	RemoveParticle(particle);
	// Play the sounds 
	PLAYSOUND::PLAYSOUND sound = mSystem.AssetMgr.GetSoundForItem(itemId);
	auto pitchShifter = MathU::Random(0.8f, 1.2f);
	auto modulator = MathU::Random(20.f, 40.f);
	SoundManager::GetInstance().PlaySound(sound, modulator, pitchShifter);
}

void Level::TurnItemToGold(Particle& particle)
{
	sf::Vector2f position = particle.getEndPos();
	std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> itemId = particle.getItemID();
	sf::Text& text = mSystem.AssetMgr.GetTextForItemID(itemId.first);
	std::function<void(Item&)> callback = [this](Item& item) {this->PickUpItem(item); };
	int uniqueId = particle.getId();
	RemoveAllItemObservers();
	int quantity = 100;		// Goes here when it's ready - > ITEMGEN::getValueForItem()
	mItems.push_back(std::make_unique<Item>(itemId, uniqueId, position, text, callback, quantity));
	AddAllItemObservers();
	RemoveParticle(particle);
	auto pitchShifter = MathU::Random(0.8f, 1.2f);
	auto modulator = MathU::Random(20.f, 40.f);
	SoundManager::GetInstance().PlaySound(PLAYSOUND::GOLD_DROP, modulator, pitchShifter);
}

void Level::SortItemsByVerticalSpace()

{	auto sortingLambda = [](std::unique_ptr<Item>& a, std::unique_ptr<Item>& b)
		{
			// > than because of y-down coord
			return a->getPosition().y > b->getPosition().y;
		};
	std::sort(mItems.begin(), mItems.end(), sortingLambda);
}

void Level::StackItemlabels()
{
	std::vector<sf::RectangleShape> placedRects;
	for (auto& item : mItems)
	{
		sf::RectangleShape textBox = item->getTextRect();
		textBox.setPosition(item->getPosition() + sf::Vector2f{ 0.f, -30.f });
		if (placedRects.size() != 0)
		{
			for (auto& rect : placedRects)
			{
				if (rect.getGlobalBounds().intersects(textBox.getGlobalBounds()))
				{
					textBox.setPosition(textBox.getPosition().x, rect.getGlobalBounds().top - textBox.getLocalBounds().getSize().y /2 - 5.f );
				}
			}
		}
		placedRects.push_back(textBox);
		item->setTextRect(textBox);
	}
}

void Level::RemoveAllItemObservers()
{
	for (auto& item : mItems)
	{
		mSystem.InputMgr.RemoveObserver(item.get());
	}
}

void Level::AddAllItemObservers()
{
	for (auto& item : mItems)
	{
		mSystem.InputMgr.AddObserver(item.get());
	}
}

void Level::RemoveAllChestObservers()
{
	for (auto& chest : mChests)
	{
		mSystem.InputMgr.RemoveObserver(chest.get());
	}
}

void Level::UpgradeLevel()
{
	if (mUpgradeLevel == LEVELS::UPGRADE::MAX_UPGRADES - 1)
	{
		std::cout << "Attempted to upgrade level that is already at max level. Level ID:";
		std::cout << mLevelID << '\n';
		return;
	}
	mUpgradeLevel = (LEVELS::UPGRADE)(mUpgradeLevel + 1);
	RemoveAllChestObservers();
	ActivateChests();
}

LEVELS::UPGRADE Level::GetUpgradeLevel()
{
	return mUpgradeLevel;
}

void Level::SetUpgradeLevel(LEVELS::UPGRADE upgrade)
{
	mUpgradeLevel = upgrade;
}

void Level::ActivateChests()
{
	switch (mUpgradeLevel)
	{
	case LEVELS::ONE_CHEST: 
	{ 
		mChests[0]->setActive(true); 
		mChests[0]->ResetChest();
		mSystem.InputMgr.AddObserver(mChests[0].get()); 
	}; break;
	case LEVELS::TWO_CHEST: 
	{
		mChests[0]->setActive(true);
		mChests[1]->setActive(true);
		mChests[0]->ResetChest();
		mChests[1]->ResetChest();
		mSystem.InputMgr.AddObserver(mChests[0].get());
		mSystem.InputMgr.AddObserver(mChests[1].get());
	}; break;
	case LEVELS::THREE_CHEST: 
	{
		mChests[0]->setActive(true);
		mChests[1]->setActive(true);
		mChests[2]->setActive(true);
		mChests[0]->ResetChest();
		mChests[1]->ResetChest();
		mChests[2]->ResetChest();
		mSystem.InputMgr.AddObserver(mChests[0].get());
		mSystem.InputMgr.AddObserver(mChests[1].get());
		mSystem.InputMgr.AddObserver(mChests[2].get());
	}; break;
	case LEVELS::FOUR_CHEST: 
	{
		mChests[0]->setActive(true);
		mChests[1]->setActive(true);
		mChests[2]->setActive(true);
		mChests[3]->setActive(true);
		mChests[0]->ResetChest();
		mChests[1]->ResetChest();
		mChests[2]->ResetChest();
		mChests[3]->ResetChest();
		mSystem.InputMgr.AddObserver(mChests[0].get());
		mSystem.InputMgr.AddObserver(mChests[1].get());
		mSystem.InputMgr.AddObserver(mChests[2].get());
		mSystem.InputMgr.AddObserver(mChests[3].get());
	}; break;
	}
}

void Level::DeactiveChests()
{
	for (auto& chest : mChests)
	{
		chest->setActive(false);
	}
}
