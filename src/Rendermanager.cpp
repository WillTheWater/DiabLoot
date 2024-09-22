#include "RenderManager.h"

RenderManager::RenderManager()
	: mAssetMgr{}
	, mGUIMgr{}
	, mGameWindow{ sf::VideoMode(1920u, 1080u), "DiabLoot", sf::Style::Default }
{
}

sf::RenderWindow& RenderManager::GetWindow()
{
	return mGameWindow;
}

void RenderManager::MainMenuRender()
{
	Draw(mAssetMgr.GetSprite(SPRITES::MAINMENU));
	mGUIMgr.AddButton({ 0.f,0.f });
	DrawButtons();
}

void RenderManager::PlayRender()
{
	Draw(mAssetMgr.GetSprite(SPRITES::MAP_ONE));
}

void RenderManager::DrawButtons()
{
	for (const auto& button : mGUIMgr.GetButtons())
	{
		auto& buttonSprite = mAssetMgr.GetSprite(SPRITES::BUTTON);
		buttonSprite.setPosition(button.GetPosition());
		switch (button.GetButtonState())
		{
		case Button::BUTTON_STATE::HOVER:
			buttonSprite.setColor(sf::Color{ 200, 200, 200, 255 });
			break;
		case Button::BUTTON_STATE::CLICK:
			buttonSprite.setColor(sf::Color{ 100, 100, 100, 255 });
			break;
		default:
			buttonSprite.setColor(sf::Color{ 255, 255, 255, 255 });
			break;
		}
		Draw(buttonSprite);
	}
}

void RenderManager::RenderLevel(Level& level)
{
	Draw(mAssetMgr.GetLevelMap(level.GetLevelId()));
	RenderChests(level.GetChests());
	RenderParticles(level.GetParticles());
}

void RenderManager::RenderParticles(std::vector<std::unique_ptr<Particle>>& particles)
{
	for (auto& p : particles)
	{
		sf::Vector2f pos = p->getCurrentPos();
		// Change this to the correct sprite
		sf::Sprite particleSprite = mAssetMgr.GetSprite(SPRITES::PARTICLE);
		particleSprite.setOrigin(particleSprite.getTextureRect().getSize().x / 2.f, particleSprite.getTextureRect().getSize().y / 2.f);
		particleSprite.setPosition(pos);
		Draw(particleSprite);
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
			chestSprite = mAssetMgr.GetSprite(SPRITES::CHESTOPENED);
		}
		else
		{
			chestSprite = mAssetMgr.GetSprite(SPRITES::CHESTCLOSED);
		}
		chestSprite.setOrigin(chestSprite.getGlobalBounds().getSize().x / 2.f, chestSprite.getGlobalBounds().getSize().y / 2.f);
		chestSprite.setPosition(position);
		// Mirror it if needed
		if (chest->IsMirrored())
		{
			chestSprite.setScale({ -1,1 });
		}

		Draw(chestSprite);
	}
}