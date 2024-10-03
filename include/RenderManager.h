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
	sf::Sprite&									AnimatedFire(ANIMATE::FIRE fireSize, const sf::Vector2f& position, const float scale = 1.f);
	void										FireRenderer(LEVELS::LEVEL level);
	void										RainRender();
	void										ScreenFlash();



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
	void										ParticlesRender(std::list<std::unique_ptr<Particle>>& particles);
	void										ChestsRender(std::array<std::unique_ptr<Chest>, 4>& chests);
	void										ItemsRender(std::list<std::unique_ptr<Item>>& items);
	void										ItemCollectionRender();
};