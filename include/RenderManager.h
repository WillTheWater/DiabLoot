#pragma once
#include <SFML/Graphics.hpp>

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
	void										InventoryRender();

	template <typename T>
	void										Draw(const T& drawObject) { mGameWindow.draw(drawObject); }

private:
	sf::RenderWindow							mGameWindow;
	sf::Vector2f								mWindowCenter;
	sf::Cursor									mCursorOpen;
	sf::Cursor									mCursorClosed;
	System& mSystem;
};