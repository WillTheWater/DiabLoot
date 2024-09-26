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

std::unique_ptr<Button> GUIManager::MakeInventoryButton(const BUTTONS::BUTTON_TYPE& type, const sf::Vector2f& position)
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
    mButtons[BUTTONS::START_ID]->SetClickCB([this]() {LOG("Start Clicked");});
    mButtons[BUTTONS::EXIT_ID] = MakeButton(BUTTONS::WIDE, BUTTONS::EXIT, mWindowCenter + sf::Vector2f{ 0.f, 83.f });
    mButtons[BUTTONS::NEXT_LEVEL_ID] = MakeButton(BUTTONS::WIDE, BUTTONS::NEXT_LEVEL, mWindowCenter + sf::Vector2f{ 0.f, 500.f });
    mButtons[BUTTONS::INVENTORY_ID] = MakeInventoryButton(BUTTONS::SQUARE, { 1263.f, 940.f });
}

Button& GUIManager::GetButton(BUTTONS::BUTTON_ID buttonID)
{
    return *mButtons[buttonID];
}

void GUIManager::MainMenuUpdate(sf::Vector2f mousePos, bool isClicked)
{
    mButtons[BUTTONS::START_ID]->HandleEvent(mousePos, isClicked);
    mButtons[BUTTONS::EXIT_ID]->HandleEvent(mousePos, isClicked);
}

void GUIManager::PlayStateUpdate(sf::Vector2f mousePos, bool isClicked)
{
    mButtons[BUTTONS::NEXT_LEVEL_ID]->HandleEvent(mousePos, isClicked);
    mButtons[BUTTONS::INVENTORY_ID]->HandleEvent(mousePos, isClicked);
}
