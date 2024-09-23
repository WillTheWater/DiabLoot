#pragma once
#include "GameState.h"
#include "Particle.h"
#include "Chest.h"
#include "MathUtilities.h"
#include "MainMenuState.h"
#include "Core.h"
#include "Level.h"

class PlayState : public GameState, public InputObserver
{
public:
	PlayState(TimeManager& timeMgr, RenderManager& renderMgr, InputManager& inputMgr, ChangeStateCallback changeStateCB, LEVELS::LEVEL level);

	virtual void							Enter() override;
	virtual void							Exit() override;
	virtual void							Update() override;
	virtual void							Draw() override;

	void									OnMouseMove(int x, int y) override;
	void									OnKeyPress(sf::Keyboard::Key key) override;
	void									OnKeyRelease(sf::Keyboard::Key key) override;
	void									OnMouseClick(sf::Mouse::Button button) override;
	void									OnMouseRelease(sf::Mouse::Button button) override;
private:
	std::unique_ptr<Level>					mLevel;
};