#pragma once
#include "SystemManager.h"

class GameState
{
public:

	GameState(System& system, ChangeStateCallback changeStateCB)
		:mSystem{ system }
		, mChangeStateCB{ changeStateCB }
	{}

	virtual									~GameState() = default;

	virtual void							Enter() = 0;
	virtual void							Exit() = 0;
	virtual void							Update() = 0;
	virtual void							Draw() = 0;

protected:
	System& mSystem;
	ChangeStateCallback						mChangeStateCB;
};