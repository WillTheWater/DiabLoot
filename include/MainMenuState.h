#pragma once
#include "GameState.h"

class MainMenuState : public GameState, public InputObserver
{
public:
	MainMenuState(System& system, ChangeStateCallback changeStateCB);

	virtual void							Enter() override;
	virtual void							Exit() override;
	virtual void							Update() override;
	virtual void							Draw() override;

	void									OnMouseMove(int x, int y) override;
	void									OnKeyPress(sf::Keyboard::Key key) override;
	void									OnKeyRelease(sf::Keyboard::Key key) override;
	void									OnMouseClick(sf::Mouse::Button button) override;
	void									OnMouseRelease(sf::Mouse::Button button) override;
};