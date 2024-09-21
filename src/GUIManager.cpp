#include "GUIManager.h"
#include "RenderManager.h"

GUIManager::GUIManager(RenderManager& renderMgr)
	: mRenderMgr{renderMgr}
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

void GUIManager::RenderButtons()
{
	for (const auto& button : mButtons)
	{
		auto& buttonSprite = mRenderMgr.GetAssetManager().GetSprite(SPRITES::MAINMENU);
		buttonSprite.setPosition(button.GetPosition());
		switch (button.GetButtonState())
		{
		case Button::BUTTON_STATE::HOVER:
			buttonSprite.setColor(sf::Color{ 200, 200, 200, 255 });
			break;
		case Button::BUTTON_STATE::CLICK:
			buttonSprite.setColor(sf::Color{ 100, 100, 100, 255 });
			break;
		default:
			buttonSprite.setColor(sf::Color{ 255, 255, 255, 255 });
			break;
		}
		mRenderMgr.Draw(buttonSprite);
	}
}