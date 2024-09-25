#include "GUIManager.h"
#include "RenderManager.h"
#include "Core.h"
#include "PlayState.h"
#include "GameState.h"
#include "SystemManager.h"

GUIManager::GUIManager(System& system)
    : mSystem{ system }
    , mGetWindowCB{ nullptr }
    , IsButtonDown{ false }
{
    mButtons.reserve(10);
}

void GUIManager::InitButtons(std::function<std::unique_ptr<PlayState>()> createPlayStateCB, std::function<void(std::unique_ptr<GameState>)> changeStateCB)
{
    auto StartButton = AddButton({ mGetWindowCB().getSize().x / 2.f - 300.f, mGetWindowCB().getSize().y / 2.f }, "Start");
    auto ExitButton = AddButton({ mGetWindowCB().getSize().x / 2.f - 300.f, mGetWindowCB().getSize().y / 2.f + 83.f }, "Exit");

    StartButton->SetClickCB([createPlayStateCB, changeStateCB]() {auto newState = createPlayStateCB(); changeStateCB(std::move(newState)); });
    ExitButton->SetClickCB([this]() { mGetWindowCB().close(); });
}

void GUIManager::UpdateButtons()
{
    auto mousePos = sf::Mouse::getPosition(mGetWindowCB());
    bool isLeftButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    static bool wasButtonPressedLastFrame = false;

    for (const auto& button : GetButtons())
    {
        const auto bounds = button->GetButtonBounds(button->GetPosition());
        if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
        {
            if (isLeftButtonPressed)
            {
                if (!wasButtonPressedLastFrame)
                {
                    button->SetHoverState(true);
                    button->SetButtonState(Button::BUTTON_STATE::CLICK);
                    OnButtonDown();
                }
            }
            else
            {
                if (wasButtonPressedLastFrame && button->GetHoverState())
                {
                    button->SetButtonState(Button::BUTTON_STATE::HOVER);
                    OnButtonUp();
                    WasClicked(*button);
                }
                else
                {
                    button->SetButtonState(Button::BUTTON_STATE::HOVER);
                }
                button->SetHoverState(false);
            }
        }
        else
        {
            if (!isLeftButtonPressed)
            {
                button->SetHoverState(false);
            }
            button->SetButtonState(Button::BUTTON_STATE::IDLE);
            OnButtonUp();
        }
    }
    wasButtonPressedLastFrame = isLeftButtonPressed;
}

Button* GUIManager::AddButton(const sf::Vector2f& position, const std::string& buttonText)
{
    mButtons.emplace_back(std::make_unique<Button>(position, buttonText));
    return mButtons.back().get();
}

std::vector<std::unique_ptr<Button>>& GUIManager::GetButtons()
{
    return mButtons;
}

bool GUIManager::GetButtonCondition() const
{
    return IsButtonDown;
}

void GUIManager::OnButtonUp()
{
    IsButtonDown = false;
}

void GUIManager::OnButtonDown()
{
    IsButtonDown = true;
}

void GUIManager::WasClicked(Button& button)
{
    button.OnClick();
}

void GUIManager::SetWindowCB(std::function<sf::RenderWindow& ()> getWindowCB)
{
    mGetWindowCB = getWindowCB;
}