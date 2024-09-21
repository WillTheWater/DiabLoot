#include "PlayState.h"
#include "MainMenuState.h"
#include "Core.h"

PlayState::PlayState(TimeManager& timeMgr, RenderManager& renderMgr, InputManager& inputMgr, EventManager& eventMgr, ChangeStateCallback changeStateCB)
	: GameState{ timeMgr, renderMgr, inputMgr, eventMgr, changeStateCB }
{
}

void PlayState::Enter()
{
	mInputManager.AddObserver(this);
}

void PlayState::Exit()
{
	mInputManager.RemoveObserver(this);
}

void PlayState::Update()
{
	float dt = mTimeManager.GetDeltaTime();

}

void PlayState::Draw()
{
	mRenderManager.PlayRender();
}

void PlayState::OnMouseMove(int x, int y)
{
}

void PlayState::OnKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::I)
	{
		LOG("Open Inventory")
	}
}
void PlayState::OnKeyRelease(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Escape)
	{
		auto newState = std::make_unique<MainMenuState>(mTimeManager, mRenderManager, mInputManager, mEventManager, mChangeStateCB);
		mChangeStateCB(std::move(newState));
	}
}
void PlayState::OnMouseClick(sf::Mouse::Button button)
{
	LOG("Observer: Mouse clicked")
}
void PlayState::OnMouseRelease(sf::Mouse::Button button)
{
	LOG("Observer: Mouse released")
}