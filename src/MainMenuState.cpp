#include "MainMenuState.h"
#include "PlayState.h"
#include "Core.h"
#include "MathUtilities.h"

MainMenuState::MainMenuState(TimeManager& timeMgr, RenderManager& renderMgr, InputManager& inputMgr, EventManager& eventMgr, ChangeStateCallback changeStateCB)
	: GameState{timeMgr, renderMgr, inputMgr, eventMgr, changeStateCB}
{

}

void MainMenuState::Enter()
{
	mInputManager.AddObserver(this);
}

void MainMenuState::Exit()
{
	mInputManager.RemoveObserver(this);
}

void MainMenuState::Update()
{
	float dt = mTimeManager.GetDeltaTime();

}

void MainMenuState::Draw()
{
	mRenderManager.MainMenuRender();
}

void MainMenuState::OnMouseMove(int x, int y)
{
	
}

void MainMenuState::OnKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Escape) { mRenderManager.GetWindow().close(); }
}
void MainMenuState::OnKeyRelease(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::P)
	{ 
		auto newState = std::make_unique<PlayState>(mTimeManager, mRenderManager, mInputManager, mEventManager, mChangeStateCB);
		mChangeStateCB(std::move(newState));
	}
}
void MainMenuState::OnMouseClick(sf::Mouse::Button button)
{
	
}
void MainMenuState::OnMouseRelease(sf::Mouse::Button button)
{
	
}