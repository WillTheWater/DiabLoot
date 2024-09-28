#include "GUIManager.h"
#include "RenderManager.h"
#include "Core.h"
#include "PlayState.h"
#include "GameState.h"
#include "SystemManager.h"

GUIManager::GUIManager(System& system)
    : mSystem{ system }
{
    mButtons.reserve(10);
    mWindowCenter = {mSystem.RenderMgr.GetWindow().getSize().x/2.f, mSystem.RenderMgr.GetWindow().getSize().y / 2.f };
    ButtonInit();
}

std::unique_ptr<Button> GUIManager::MakeButton(const BUTTONS::BUTTON_TYPE& type, const BUTTONS::BUTTON_TEXT& text, const sf::Vector2f& position)
{
    auto& buttonSprite = mSystem.AssetMgr.GetSpriteForButton(type);
    auto& buttonText = mSystem.AssetMgr.GetTextForButtons(text);
    auto button = std::make_unique<Button>(buttonSprite, buttonText, position);
    mButtons.emplace_back(std::move(button));
    return std::move(mButtons.back()); 
}

std::unique_ptr<Button> GUIManager::MakeSquareButton(const BUTTONS::BUTTON_TYPE& type, const sf::Vector2f& position)
{
    auto& buttonSprite = mSystem.AssetMgr.GetSpriteForButton(type);
    auto button = std::make_unique<Button>(buttonSprite, position);
    mButtons.emplace_back(std::move(button));
    return std::move(mButtons.back());
}

std::vector<std::unique_ptr<Button>>& GUIManager::GetButtons()
{
    return mButtons;
}

void GUIManager::ButtonInit()
{
    for (int i = 0; i < BUTTONS::BUTTON_ID::MAX_BUTTONS_ID; i++)
    {
        mButtons.push_back(nullptr);
    }
    mButtons[BUTTONS::START_ID] = MakeButton(BUTTONS::WIDE, BUTTONS::START, mWindowCenter);
    mButtons[BUTTONS::LOAD_GAME_ID] = MakeButton(BUTTONS::WIDE, BUTTONS::LOAD_GAME, mWindowCenter - sf::Vector2f{0.f, 83.f});
    mButtons[BUTTONS::EXIT_ID] = MakeButton(BUTTONS::WIDE, BUTTONS::EXIT, mWindowCenter + sf::Vector2f{ 0.f, 83.f });
    mButtons[BUTTONS::EXIT_PLAY_ID] = MakeButton(BUTTONS::WIDE, BUTTONS::EXIT_PLAY, sf::Vector2f{ 300.f, 1040.f });
    mButtons[BUTTONS::NEXT_LEVEL_ID] = MakeButton(BUTTONS::WIDE, BUTTONS::NEXT_LEVEL, mWindowCenter + sf::Vector2f{ 0.f, 500.f });
    mButtons[BUTTONS::INVENTORY_ID] = MakeSquareButton(BUTTONS::SQUARE, { 1263.f, 940.f });
    mButtons[BUTTONS::SORT_BUTTON_ID] = MakeSquareButton(BUTTONS::SORT, { 1700.f, 940.f });
    mButtons[BUTTONS::OPEN_INVENTORY_ID] = MakeButton(BUTTONS::WIDE, BUTTONS::OPEN_INVENTORY, mWindowCenter + sf::Vector2f{ 660.f, 500.f });
    mButtons[BUTTONS::MUTE_BUTTON_ID] = MakeSquareButton(BUTTONS::MUTE, {100.f,100.f});
    mButtons[BUTTONS::UPGRADE_BUTTON_ID] = MakeSquareButton(BUTTONS::UPGRADE, { 192.f, 100.f }); 
}

Button& GUIManager::GetButton(BUTTONS::BUTTON_ID buttonID)
{
    return *mButtons[buttonID];
}

void GUIManager::MainMenuUpdate(sf::Vector2f mousePos, bool isClicked)
{
    mButtons[BUTTONS::START_ID]->HandleEvent(mousePos, isClicked);
    mButtons[BUTTONS::LOAD_GAME_ID]->HandleEvent(mousePos, isClicked);
    mButtons[BUTTONS::EXIT_ID]->HandleEvent(mousePos, isClicked);
    mButtons[BUTTONS::MUTE_BUTTON_ID]->HandleEvent(mousePos, isClicked);
}

void GUIManager::PlayStateUpdate(sf::Vector2f mousePos, bool isClicked)
{
    mButtons[BUTTONS::NEXT_LEVEL_ID]->HandleEvent(mousePos, isClicked);
    mButtons[BUTTONS::INVENTORY_ID]->HandleEvent(mousePos, isClicked);
    mButtons[BUTTONS::OPEN_INVENTORY_ID]->HandleEvent(mousePos, isClicked);
    mButtons[BUTTONS::EXIT_PLAY_ID]->HandleEvent(mousePos, isClicked);
    mButtons[BUTTONS::MUTE_BUTTON_ID]->HandleEvent(mousePos, isClicked);
    mButtons[BUTTONS::UPGRADE_BUTTON_ID]->HandleEvent(mousePos, isClicked);
    mButtons[BUTTONS::SORT_BUTTON_ID]->HandleEvent(mousePos, isClicked);
}
