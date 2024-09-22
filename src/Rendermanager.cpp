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