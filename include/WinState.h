#pragma once
#include "GameState.h"

class WinState : public GameState, public InputObserver
{
public:
	WinState(System& system, ChangeStateCallback changeStateCB, Level& level);

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
	Level& mLevel;
	bool									mMouseIsClicked;
	sf::Vector2f							mMousePosition;

};