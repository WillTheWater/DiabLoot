#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <functional>
#include "Button.h"

class PlayState;
class GameState;
class System;

class GUIManager
{
public:

	GUIManager(System& system);

private:
	std::vector<std::unique_ptr<Button>>	mButtons;
	System& mSystem;
};