#include "GUIManager.h"
#include "RenderManager.h"
#include "Core.h"

GUIManager::GUIManager()
	: mGetWindowCB{nullptr}
	, IsButtonDown{false}
{
	mButtons.reserve(10);
}

void GUIManager::InitButtons()
{
	AddButton({ mGetWindowCB().getSize().x / 2.f - 300.f, mGetWindowCB().getSize().y / 2.f});
	AddButton({ mGetWindowCB().getSize().x / 2.f - 300.f, mGetWindowCB().getSize().y / 2.f + 83.f });
}

void GUIManager::OnMouseMove(int x, int y)
{
	LOG("moving mouse")
}

void GUIManager::OnKeyPress(sf::Keyboard::Key key)
{
}

void GUIManager::OnKeyRelease(sf::Keyboard::Key key)
{
}

void GUIManager::OnMouseClick(sf::Mouse::Button button)
{
}

void GUIManager::OnMouseRelease(sf::Mouse::Button button)
{
}

void GUIManager::UpdateButtons()
{
	auto mousePos = sf::Mouse::getPosition(mGetWindowCB());
	bool isLeftButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

	for (const auto& button : GetButtons())
	{
		const auto bounds = button->GetButtonBounds(button->GetPosition());

		if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
		{
			if (isLeftButtonPressed)
			{
				button->SetButtonState(Button::BUTTON_STATE::CLICK);
				OnButtonDown();
			}
			else
			{
				button->SetButtonState(Button::BUTTON_STATE::HOVER);
				OnButtonUp();
			}
		}
		else
		{
			button->SetButtonState(Button::BUTTON_STATE::IDLE);
			OnButtonUp();
		}
	}
}

void GUIManager::AddButton(const sf::Vector2f& position)
{
	mButtons.emplace_back(std::make_unique<Button>(position));
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

void GUIManager::SetWindowCB(std::function<sf::RenderWindow& ()> getWindowCB)
{
	mGetWindowCB = getWindowCB;
}