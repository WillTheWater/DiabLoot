#pragma once
#include "GameState.h"

class PlayState;

class Game
{
public:
	Game();

	void										Run();
	void										GUISetup();
	void										ChangeState(std::unique_ptr<GameState> newState);
	std::unique_ptr<PlayState>					CreatePlayState();

private:
	using ChangeStateCallback = std::function<void(std::unique_ptr<GameState>)>;
	TimeManager									mTimeMgr;
	RenderManager								mRenderMgr;
	InputManager								mInputMgr;
	GUIManager									mGUIMgr;
	ChangeStateCallback							mChangeStateCB;
	std::unique_ptr<GameState>					mCurrentState;
};