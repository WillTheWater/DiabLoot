#include "Level.h"
#include "SystemManager.h"

Level::Level(LEVELS::LEVEL id, System& system)
	:mLevelID{id}
	,mSystem{system}
	,mParticleUniqueId{0}
	,mUpgradeLevel{LEVELS::UPGRADE::ONE_CHEST}
	,mChests{ nullptr, nullptr, nullptr, nullptr}
	,mParticlesToRemove{}
{
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
	RemoveAllChestObservers();
	DeactiveChests();
	mItems.clear();
	mParticles.clear();
}

std::list<std::unique_ptr<Item>>& Level::GetItems()
{
	return mItems;
}

std::array<std::unique_ptr<Chest>, 4>& Level::GetChests()
{
	return mChests;
}

std::list<std::unique_ptr<Particle>>& Level::GetParticles()
{
	return mParticles;
}

void Level::UpdateLevel()
{
	RemoveOldParticles();
	RemoveOldItems();
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

void Level::SpawnChest(sf::Vector2f pos, bool mirrored, size_t index)
{
	std::function<void(Chest&)> callback = [this](Chest& chest) {this->SpawnParticles(chest); };
	mChests[index - 1] = (std::make_unique<Chest>(pos, mirrored, callback));
}

void Level::SpawnParticles(Chest& chest)
{
	int numOfParticles = MathU::Random(8, 16);
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
		std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> itemId = ITEMGEN::GetRandomItem();
		mParticles.push_back(std::make_unique<Particle>(id, startPos, endPos, randAnchorheight, animStep, callback, itemId));
	}
	mSystem.InputMgr.RemoveObserver(&chest);
}

void Level::CreateBounceParticle(Item& item)
{
	std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> itemId = { ITEMID::GOLD, item.GetItemID().second};
	Vec2 startPos = item.GetPosition();
	Vec2 endPos = startPos;
	int id = GetUniqueParticleId();
	float randAnchorheight = MathU::Random(60.f, 120.f) * -1;
	float animStep = PARTICLE::ANIMSTEP;
	std::function<void(Particle&)> callback = [this](Particle& particle) {this->TurnItemToGold(particle); };
	mParticles.push_back(std::make_unique<Particle>(id, startPos, endPos, randAnchorheight, animStep, callback, itemId));
}

void Level::RemoveOldParticles()
{
	bool success = false;
	for (auto& i : mParticlesToRemove)
	{
		for (std::list<std::unique_ptr<Particle>>::iterator it = mParticles.begin(); it != mParticles.end(); it++)
		{
			if (it->get()->GetId() == i)
			{
				success = true;
			}
			if (success)
			{
				mParticles.erase(it);
				break;
			}
		}
	}
	mParticlesToRemove.clear();
}

void Level::RemoveOldItems()
{
	bool success = false;
	for (auto& i : mItemsToRemove)
	{
		for (std::list<std::unique_ptr<Item>>::iterator it = mItems.begin(); it != mItems.end(); it++)
		{
			if (it->get()->GetUniqueId() == i)
			{
				success = true;
			}
			if (success)
			{
				mItems.erase(it);
				break;
			}
		}
	}
	mItemsToRemove.clear();
}

void Level::UpdateParticles()
{
	for (std::list<std::unique_ptr<Particle>>::iterator it = mParticles.begin(); it != mParticles.end(); it++)
	{
		it->get()->StepParticle(mSystem.TimeMgr.GetDeltaTime());
	}
}

void Level::SetParticleForRemoval(Particle& particle)
{
	bool success = false;

	for (std::list<std::unique_ptr<Particle>>::iterator it = mParticles.begin(); it != mParticles.end(); it++)
	{
		if (it->get()->GetId() == particle.GetId())
		{
			success = true;
		}
		if (success)
		{
			mParticlesToRemove.push_back(it->get()->GetId());
			break;
		}
	}
	assert(success && "PlayState::RemoveParticle failed to remove the particle");
}

void Level::SetItemForRemoval(Item& item)
{
	bool success = false;

	for (std::list<std::unique_ptr<Item>>::iterator it = mItems.begin(); it != mItems.end(); it++)
	{
		if (it->get()->GetUniqueId() == item.GetUniqueId())
		{
			success = true;
		}
		if (success)
		{
			mItemsToRemove.push_back(it->get()->GetUniqueId());
			break;
		}
	}
	assert(success && "PlayState::RemoveParticle failed to remove the particle");
}

void Level::PickUpItem(Item& item)
{
	bool couldAdd = mSystem.InventoryMgr.AddItem(item);
	
	bool success = false;
	for (std::list<std::unique_ptr<Item>>::iterator it = mItems.begin(); it != mItems.end(); it++)
	{
		if (it->get()->GetUniqueId() == item.GetUniqueId())
		{
			if (!couldAdd)
			{
				CreateBounceParticle(item);
				AUDIO_MUTE::AUDIOSTATE currentAudioState = SoundManager::GetInstance().GetAudioState();
				auto pitchShifter = MathU::Random(0.8f, 1.2f);
				auto modulator = MathU::Random(20.f, 40.f);
				if (currentAudioState == AUDIO_MUTE::AUDIOSTATE::UNMUTED ||
					currentAudioState == AUDIO_MUTE::AUDIOSTATE::MUTE_MUSIC)
				{
					SoundManager::GetInstance().PlaySound(PLAYSOUND::ITEM_FLIP, modulator, pitchShifter);
				}
			}
			SetItemForRemoval(*it->get());
			mSystem.InputMgr.RemoveObserver(it->get());
			success = true;
		}
	}
	assert(success && "PlayState::RemoveItem failed to remove the item");
}

void Level::SpawnItem(Particle& particle)
{
	sf::Vector2f position = particle.GetEndPos();
	std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> itemId = particle.GetItemID();
	sf::Text& text = mSystem.AssetMgr.GetTextForItemID(itemId.first);
	std::function<void(Item&)> callback = [this](Item& item) {this->PickUpItem(item); };
	int uniqueId = particle.GetId();
	int quantity = 1;
	if (itemId.first == ITEMID::GOLD)
	{
		quantity = ITEMGEN::GetRandomGoldAmount();
	}
	mItems.push_back(std::make_unique<Item>(itemId, uniqueId, position, text, callback, quantity));
	mSystem.InputMgr.AddObserver(mItems.back().get());
	SetParticleForRemoval(particle);
	// Play the sounds 
	AUDIO_MUTE::AUDIOSTATE currentAudioState = SoundManager::GetInstance().GetAudioState();
	PLAYSOUND::PLAYSOUND sound = mSystem.AssetMgr.GetSoundForItem(itemId);
	auto pitchShifter = MathU::Random(0.8f, 1.2f);
	auto modulator = MathU::Random(20.f, 40.f);
	if (currentAudioState == AUDIO_MUTE::AUDIOSTATE::UNMUTED ||
		currentAudioState == AUDIO_MUTE::AUDIOSTATE::MUTE_MUSIC)
	{
		SoundManager::GetInstance().PlaySound(sound, modulator, pitchShifter);
	}
}

void Level::TurnItemToGold(Particle& particle)
{
	sf::Vector2f position = particle.GetEndPos();
	std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> itemId = particle.GetItemID();
	sf::Text& text = mSystem.AssetMgr.GetTextForItemID(itemId.first);
	std::function<void(Item&)> callback = [this](Item& item) {this->PickUpItem(item); };
	int uniqueId = particle.GetId();
	int quantity = ITEMGEN::GetValueForItem(itemId);
	mItems.push_back(std::make_unique<Item>(std::pair{ itemId.first, ITEMRARITY::GOLD }, uniqueId, position, text, callback, quantity));
	mSystem.InputMgr.AddObserver(mItems.back().get());
	SetParticleForRemoval(particle);

	auto pitchShifter = MathU::Random(0.8f, 1.2f);
	auto modulator = MathU::Random(20.f, 40.f);
	AUDIO_MUTE::AUDIOSTATE currentAudioState = SoundManager::GetInstance().GetAudioState();
	if (currentAudioState == AUDIO_MUTE::AUDIOSTATE::UNMUTED ||
		currentAudioState == AUDIO_MUTE::AUDIOSTATE::MUTE_MUSIC)
	{
		SoundManager::GetInstance().PlaySound(PLAYSOUND::GOLD_DROP, modulator, pitchShifter);
	}
}

void Level::SortItemsByVerticalSpace()

{	auto sortingLambda = [](std::unique_ptr<Item>& a, std::unique_ptr<Item>& b)
		{
			// > than because of y-down coord
			return a->GetPosition().y > b->GetPosition().y;
		};
	mItems.sort(sortingLambda);
}

void Level::StackItemlabels()
{
	std::vector<sf::RectangleShape> placedRects;
	for (auto& item : mItems)
	{
		sf::RectangleShape textBox = item->GetTextRect();
		textBox.setPosition(item->GetPosition() + sf::Vector2f{ 0.f, -30.f });
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
		item->SetTextRect(textBox);
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
		for (int i{ 0 }; i <= LEVELS::ONE_CHEST; i++)
		{
			mChests[i]->SetActive(true);
			mChests[i]->ResetChest();
			mSystem.InputMgr.AddObserver(mChests[i].get());
		}
		
	}; break;
	case LEVELS::TWO_CHEST: 
	{
		for (int i{ 0 }; i <= LEVELS::TWO_CHEST; i++)
		{
			mChests[i]->SetActive(true);
			mChests[i]->ResetChest();
			mSystem.InputMgr.AddObserver(mChests[i].get());
		}
	}; break;
	case LEVELS::THREE_CHEST: 
	{
		for (int i{ 0 }; i <= LEVELS::THREE_CHEST; i++)
		{
			mChests[i]->SetActive(true);
			mChests[i]->ResetChest();
			mSystem.InputMgr.AddObserver(mChests[i].get());
		}
	}; break;
	case LEVELS::FOUR_CHEST: 
	{
		for (int i{ 0 }; i <= LEVELS::FOUR_CHEST; i++)
		{
			mChests[i]->SetActive(true);
			mChests[i]->ResetChest();
			mSystem.InputMgr.AddObserver(mChests[i].get());
		}
	}; break;
	}
}

void Level::DeactiveChests()
{
	for (auto& chest : mChests)
	{
		chest->SetActive(false);
	}
}

void Level::ResetLevelUpgrades()
{
	mUpgradeLevel = LEVELS::UPGRADE::ONE_CHEST;
}
