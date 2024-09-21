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