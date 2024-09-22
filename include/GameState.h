#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <functional>
#include "TimeManager.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "EventManager.h"

class GameState
{
public:

	using ChangeStateCallback = std::function<void(std::unique_ptr<GameState>)>;

	GameState(TimeManager& timeMgr, RenderManager& renderMgr, InputManager& inputMgr, EventManager& eventMgr, ChangeStateCallback changeStateCB)
		: mTimeManager{timeMgr}
		, mRenderManager{renderMgr}
		, mInputManager{inputMgr}
		, mEventManager{eventMgr}
		, mChangeStateCB{std::move(changeStateCB)}
	{}

	virtual									~GameState() = default;

	virtual void							Enter() = 0;
	virtual void							Exit() = 0;
	virtual void							Update() = 0;
	virtual void							Draw() = 0;


protected:
	TimeManager&							mTimeManager;
	RenderManager&							mRenderManager;
	InputManager&							mInputManager;
	EventManager&							mEventManager;
	ChangeStateCallback						mChangeStateCB;

};