#include "RenderManager.h"

RenderManager::RenderManager()
	: mGameWindow{ sf::VideoMode(1920u, 1080u), "DiabLoot", sf::Style::Close }
{
}

sf::RenderWindow& RenderManager::GetWindow()
{
	return mGameWindow;
}

AssetManager& RenderManager::GetAssetManager()
{
	return mAssetMgr;
}

void RenderManager::MainMenuRender()
{
	Draw(mAssetMgr.GetSprite(SPRITES::MAINMENU));
}

void RenderManager::PlayRender()
{
	Draw(mAssetMgr.GetSprite(SPRITES::MAP_ONE));
}

void RenderManager::RenderParticles(std::vector<std::unique_ptr<Particle>>& particles)
{
	for (auto& p : particles)
	{
		sf::Vector2f pos = p->getCurrentPos();
		// Change this to the correct sprite
		sf::Sprite particleSprite = mAssetMgr.GetSprite(SPRITES::BUTTON);
		// Are we setting the origin in the asset manager? If not, would make sense to... 
		particleSprite.setOrigin(particleSprite.getTextureRect().getSize().x / 2.f, particleSprite.getTextureRect().getSize().y / 2.f);
		mGameWindow.draw(particleSprite);
	}
}

void RenderManager::RenderChests(std::vector<std::unique_ptr<Chest>>& chests)
{
	for (auto& chest : chests)
	{
		sf::Vector2f position = chest->GetPosition();
		sf::Sprite chestSprite;
		// Get the opened or closed sprite
		if (chest->IsOpened())
		{
			// No open sprite yet.
			chestSprite = mAssetMgr.GetSprite(SPRITES::CHEST);
		}
		else
		{
			chestSprite = mAssetMgr.GetSprite(SPRITES::CHEST);
		}
		// Is this being done in the asset manager?
		chestSprite.setOrigin(chestSprite.getGlobalBounds().getSize().x / 2.f, chestSprite.getGlobalBounds().getSize().y / 2.f);
		chestSprite.setPosition(position);

		// If mirrored, flip the sprite on X axis
		if (chest->IsMirrored())
		{
			chestSprite.setScale({ -1,1 });
		}
		mGameWindow.draw(chestSprite);



	}
}