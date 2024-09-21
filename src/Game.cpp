#include "Game.h"
#include "MainMenuState.h"

Game::Game()
    : mTimeMgr{}
    , mRenderMgr{}
    , mInputMgr{}
    , mEventMgr{}
{
    mRenderMgr.GetWindow().setFramerateLimit(60);
    mChangeStateCB = [this](std::unique_ptr<GameState> newState) {this->ChangeState(std::move(newState)); };
    ChangeState(std::make_unique<MainMenuState>(mTimeMgr, mRenderMgr, mInputMgr, mEventMgr, mChangeStateCB));
}

void Game::Run()
{
    while (mRenderMgr.GetWindow().isOpen())
    {
        mTimeMgr.Tick();
        sf::Event event;
        while (mRenderMgr.GetWindow().pollEvent(event))
        {
            mInputMgr.ProcessInput(event);
        }
        if (mCurrentState) { mCurrentState->Update(); }
        mRenderMgr.GetWindow().clear(sf::Color::Black);
        if (mCurrentState) { mCurrentState->Draw(); }
        mRenderMgr.GetWindow().display();
    }
}

void Game::ChangeState(std::unique_ptr<GameState> newState)
{
    if (mCurrentState == newState) { return; }
    if (newState) { newState->Enter(); }
    if (mCurrentState) { mCurrentState->Exit(); }
    mCurrentState = std::move(newState);
}
