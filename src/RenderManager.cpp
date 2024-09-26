#include "RenderManager.h"
#include "SystemManager.h"
#include "Core.h"

RenderManager::RenderManager(System& system)
	: mGameWindow{ sf::VideoMode(1920u, 1080u), "DiabLoot", sf::Style::Close }
	, mSystem{ system }
	, mWindowCenter{ mGameWindow.getSize().x / 2.f, mGameWindow.getSize().y / 2.f }
{
	mGameWindow.setFramerateLimit(60);
}

sf::RenderWindow& RenderManager::GetWindow()
{
	return mGameWindow;
}

sf::Cursor& RenderManager::GetDefaultCursor()
{
	return mCursorOpen;
}

sf::Cursor& RenderManager::GetClosedCursor()
{
	return mCursorClosed;
}

void RenderManager::CustomizeGameWindow()
{
	// Cursor
	auto& defaultCursor = mSystem.AssetMgr.GetImage(IMAGES::DEFAULT_CURSOR);
	auto& closedCursor = mSystem.AssetMgr.GetImage(IMAGES::CLOSED_CURSOR);
	mCursorOpen.loadFromPixels(defaultCursor.getPixelsPtr(), defaultCursor.getSize(), { 0, 0 });
	mCursorClosed.loadFromPixels(closedCursor.getPixelsPtr(), closedCursor.getSize(), { 0, 0 });
	mGameWindow.setMouseCursor(mCursorOpen);

	// Window icon
	auto& widnowIcon = mSystem.AssetMgr.GetImage(IMAGES::ICON);
	mGameWindow.setIcon(widnowIcon.getSize().x, widnowIcon.getSize().y, widnowIcon.getPixelsPtr());
}

void RenderManager::MainMenuRender()
{
	Draw(mSystem.AssetMgr.GetSprite(SPRITES::MAINMENU));
	auto startButton = mSystem.GUIMgr.MakeButton(BUTTONS::WIDE, BUTTONS::START, mWindowCenter);
	auto exitButton = mSystem.GUIMgr.MakeButton(BUTTONS::WIDE, BUTTONS::EXIT, mWindowCenter + sf::Vector2f{0.f, 83.f});
	Draw(startButton->GetSprite());
	Draw(startButton->GetText());
	Draw(exitButton->GetSprite());
	Draw(exitButton->GetText());
}

void RenderManager::PlayStateRender()
{
	Draw(mSystem.AssetMgr.GetSprite(SPRITES::MAP_ONE));
	auto nextLevelButton = mSystem.GUIMgr.MakeButton(BUTTONS::WIDE, BUTTONS::NEXT_LEVEL, mWindowCenter + sf::Vector2f{ 0.f, 500.f });
	Draw(nextLevelButton->GetSprite());
	Draw(nextLevelButton->GetText());
}

void RenderManager::InventoryRender()
{
	Draw(mSystem.AssetMgr.GetSprite(SPRITES::INVENTORY));
	auto inventoryButton = mSystem.GUIMgr.MakeInventoryButton(BUTTONS::SQUARE, { 1263.f, 940.f });
	Draw(inventoryButton->GetSprite());
}
