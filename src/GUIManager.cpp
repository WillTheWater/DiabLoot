#include "GUIManager.h"
#include "RenderManager.h"
#include "Core.h"

GUIManager::GUIManager()
	: IsButtonDown{false}
{
	mButtons.reserve(10);
}

void GUIManager::OnMouseMove(int x, int y)
{
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
	IsButtonDown = false;
}