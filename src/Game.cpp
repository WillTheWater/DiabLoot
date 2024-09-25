#include "Game.h"
#include "MainMenuState.h"
#include "Core.h"

Game::Game()
    : mSystem{ mTimeMgr, mRenderMgr, mAssetMgr, mGUIMgr, mInputMgr, mInventoryMgr, mLevelManager }
    , mRenderMgr{ mSystem }
    , mGUIMgr{ mSystem }
    , mLevelManager{mSystem}
{
    mRenderMgr.GetWindow().setFramerateLimit(60);
    mChangeStateCB = [this](std::unique_ptr<GameState> newState) { this->ChangeState(std::move(newState)); };
    ChangeState(std::make_unique<MainMenuState>(mSystem, mChangeStateCB));
}

void Game::Run()
{
    while (mRenderMgr.GetWindow().isOpen())
    {
        mTimeMgr.Tick();
        sf::Event event;
        while (mRenderMgr.GetWindow().pollEvent(event))
        {
            if (event.type == sf::Event::Closed) { mRenderMgr.GetWindow().close(); }
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