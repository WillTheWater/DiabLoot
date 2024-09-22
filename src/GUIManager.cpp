#include "GUIManager.h"
#include "RenderManager.h"

GUIManager::GUIManager()
{
}

void GUIManager::AddButton(const sf::Vector2f& position)
{
	mButtons.emplace_back(position);
}

void GUIManager::UpdateButtons(const sf::Vector2f& mousePos, bool isClicked)
{
	for (auto& button : mButtons) { button.UpdateButtonState(mousePos, isClicked); }
}

std::vector<Button>& GUIManager::GetButtons()
{
	return mButtons;
}