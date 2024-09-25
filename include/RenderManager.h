#pragma once
#include <SFML/Graphics.hpp>

class System;

class RenderManager
{
public:
	RenderManager(System& system);

	sf::RenderWindow& GetWindow();

	void										MainMenuRender();

	template <typename T>
	void										Draw(const T& drawObject) { mGameWindow.draw(drawObject); }

private:
	sf::RenderWindow							mGameWindow;
	System& mSystem;
};