#include "Game.h"
#include "MainMenuState.h"
#include "PlayState.h"

Game::Game()
    : mTimeMgr{}
    , mGUIMgr{}
    , mRenderMgr{ mGUIMgr }
    , mInputMgr{}
{
    mRenderMgr.GetWindow().setFramerateLimit(60);
    mChangeStateCB = [this](std::unique_ptr<GameState> newState) { this->ChangeState(std::move(newState)); };
    mGUIMgr.SetWindowCB([this]() -> sf::RenderWindow& { return this->mRenderMgr.GetWindow(); });
    mInputMgr.AddObserver(&mGUIMgr);
    ChangeState(std::make_unique<MainMenuState>(mTimeMgr, mRenderMgr, mInputMgr, mChangeStateCB));
    GUISetup();
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
        mGUIMgr.UpdateButtons();
        if (mCurrentState) { mCurrentState->Update(); }
        mRenderMgr.GetWindow().clear(sf::Color::Black);
        if (mCurrentState) { mCurrentState->Draw(); }
        mRenderMgr.GetWindow().display();
    }
}

void Game::GUISetup()
{
    mGUIMgr.InitButtons([this]() { return CreatePlayState(); }, mChangeStateCB);
}

void Game::ChangeState(std::unique_ptr<GameState> newState)
{
    if (mCurrentState == newState) { return; }
    if (newState) { newState->Enter(); }
    if (mCurrentState) { mCurrentState->Exit(); }
    mCurrentState = std::move(newState);
}

std::unique_ptr<PlayState> Game::CreatePlayState()
{
    return std::make_unique<PlayState>(mTimeMgr, mRenderMgr, mInputMgr, mChangeStateCB, LEVELS::LEVEL_ONE);
}