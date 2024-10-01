#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Inventory.h"
#include "FireWorkSystem.h"
#include <iomanip>

class System;

class RenderManager
{
public:
	RenderManager(System& system);

	sf::RenderWindow&							GetWindow();
	sf::Cursor&									GetDefaultCursor();
	sf::Cursor&									GetClosedCursor();
	void										CustomizeGameWindow();

	void										MainMenuRender();
	void										PlayStateRender();
	void										WinStateRender();
	void										InventoryRender();
	void										SpeedRunTimeRender();
	void										FireWorksRender();
	sf::Sprite&							AnimatedFire(ANIMATE::FIRE fireSize, const sf::Vector2f& position, const float scale = 1.f);
	void										FireRenderer(LEVELS::LEVEL level);



	template <typename T>
	void										Draw(const T& drawObject) { mGameWindow.draw(drawObject); }
	void										LevelRender(Level& level);
	void										DrawToolTip(sf::Vector2f mousePos);
	void										DrawToolTipWarning(sf::Vector2f mousePos);

	void										ItemsMissingListRender();
private:
	sf::RenderWindow							mGameWindow;
	sf::Vector2f								mWindowCenter;
	sf::Cursor									mCursorOpen;
	sf::Cursor									mCursorClosed;
	System& mSystem;
	void										ParticlesRender(std::vector<std::unique_ptr<Particle>>& particles);
	void										ChestsRender(std::vector<std::unique_ptr<Chest>>& chests);
	void										ItemsRender(std::vector<std::unique_ptr<Item>>& items);
	void										ItemCollectionRender();
};