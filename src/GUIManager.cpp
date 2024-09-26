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

void GUIManager::UpdateButtons(sf::Vector2f mousePos, bool isClicked)
{
    for (auto& button : mButtons) 
    { 
        if (button == nullptr) { LOG("No Buttons") continue; }
        button->UpdateButtonState(mousePos, isClicked); 
    }
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
    mButtons[BUTTONS::EXIT_ID] = MakeButton(BUTTONS::WIDE, BUTTONS::EXIT, mWindowCenter + sf::Vector2f{ 0.f, 83.f });
}

Button& GUIManager::GetButton(BUTTONS::BUTTON_ID buttonID)
{
    return *mButtons[buttonID];
}

void GUIManager::MainMenuUpdate(sf::Vector2f mousePos, bool isClicked)
{
    mButtons[BUTTONS::START_ID]->UpdateButtonState(mousePos, isClicked);
    mButtons[BUTTONS::EXIT_ID]->UpdateButtonState(mousePos, isClicked);
}
