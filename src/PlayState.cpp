#include "PlayState.h"

PlayState::PlayState(TimeManager& timeMgr, RenderManager& renderMgr, InputManager& inputMgr, ChangeStateCallback changeStateCB, LEVELS::LEVEL level)
	: GameState{ timeMgr, renderMgr, inputMgr, changeStateCB }
{
	mLevel = std::make_unique<Level>(level, timeMgr, inputMgr);
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
	mLevel->UpdateLevel();
}

void PlayState::Draw()
{
	mRenderManager.RenderLevel(*mLevel);
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
		auto newState = std::make_unique<MainMenuState>(mTimeManager, mRenderManager, mInputManager, mChangeStateCB);
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

