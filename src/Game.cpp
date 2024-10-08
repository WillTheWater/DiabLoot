#include "Game.h"
#include "SoundManager.h"
#include "MainMenuState.h"
#include "Core.h"

Game::Game()
    : mSystem{ mTimeMgr, mRenderMgr, mAssetMgr, mGUIMgr, mInputMgr, mInventoryMgr, mLevelManager, mFireWorks }
    , mRenderMgr{ mSystem }
    , mGUIMgr{ mSystem }
    , mLevelManager{mSystem}
{
    SoundManager::GetInstance().SetAssetMgr(&mAssetMgr);
    mRenderMgr.CustomizeGameWindow();
    mChangeStateCB = [this](std::unique_ptr<GameState> newState) { this->ChangeState(std::move(newState)); };
    ChangeState(std::make_unique<MainMenuState>(mSystem, mChangeStateCB));
    mInputMgr.AddObserver(&mInventoryMgr);
}

void Game::Run()
{
    while (mRenderMgr.GetWindow().isOpen())
    {
        mTimeMgr.Tick();
        SoundManager::GetInstance().AudioControl();
        sf::Event event;
        while (mRenderMgr.GetWindow().pollEvent(event))
        {
            if (event.type == sf::Event::Closed) { mRenderMgr.GetWindow().close(); }
            ChangeCursor();
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

void Game::ChangeCursor()
{
    switch (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
    case true:
        mRenderMgr.GetWindow().setMouseCursor(mRenderMgr.GetClosedCursor());
        break;

    case false:
        mRenderMgr.GetWindow().setMouseCursor(mRenderMgr.GetDefaultCursor());
        break;
    }
}
