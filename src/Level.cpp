#include "Level.h"
#include "SystemManager.h"

Level::Level(LEVELS::LEVEL id, System& system)
	:mLevelID{id}
	,mSystem{system}
	,mParticleUniqueId{0}
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
	for (auto& chest : mChests)
	{
		mSystem.InputMgr.AddObserver(chest.get());
		chest->ResetChest();
	}
}

void Level::ExitLevel()
{
	for (auto& chest : mChests)
	{
		mSystem.InputMgr.RemoveObserver(chest.get());
	}
	for (auto& item : mItems)
	{
		mSystem.InputMgr.RemoveObserver(item.get());
	}
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
	// Update this to have actual chest positions
	std::function<void(Chest&)> callback = [this](Chest& chest) {this->SpawnParticles(chest); };
	mChests.push_back(std::make_unique<Chest>(pos, mirrored, callback));
	//mSystem.InputMgr.AddObserver(mChests.back().get());
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
	mSystem.InputMgr.RemoveObserver(&chest);
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
	mSystem.InventoryMgr.addItem(item);
	bool success = false;
	for (int i{ 0 }; i < mItems.size(); i++)
	{
		if (mItems[i]->getUniqueId() == item.getUniqueId())
		{
			mSystem.InputMgr.RemoveObserver(mItems[i].get());
			mItems.erase(mItems.begin() + i);
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
	mItems.push_back(std::make_unique<Item>(itemId, uniqueId, position, text, callback, 1));
	mSystem.InputMgr.AddObserver(mItems.back().get());
	RemoveParticle(particle);
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