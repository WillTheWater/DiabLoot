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
}

void GUIManager::MainMenuHUD()
{
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
