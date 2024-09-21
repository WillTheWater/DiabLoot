#pragma once
#include "GameState.h"

class Game
{
public:
	Game();

	void									Run();
	void									ChangeState(std::unique_ptr<GameState> newState);

private:
	using ChangeStateCallback = std::function<void(std::unique_ptr<GameState>)>;
	TimeManager								mTimeMgr;
	RenderManager							mRenderMgr;
	InputManager							mInputMgr;
	EventManager							mEventMgr;
	ChangeStateCallback						mChangeStateCB;
	std::unique_ptr<GameState>				mCurrentState;
};