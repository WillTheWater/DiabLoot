#pragma once
#include "GameState.h"

class Game
{
public:
	Game();

	void										Run();
	void										ChangeState(std::unique_ptr<GameState> newState);

private:
	System										mSystem;
	TimeManager									mTimeMgr;
	RenderManager								mRenderMgr;
	AssetManager								mAssetMgr;
	GUIManager									mGUIMgr;
	InputManager								mInputMgr;
	Inventory									mInventoryMgr;
	std::unique_ptr<GameState>					mCurrentState;
	ChangeStateCallback							mChangeStateCB;
};