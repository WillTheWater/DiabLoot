#include "GUIManager.h"

GUIManager::GUIManager(RenderManager& renderMgr)
	:mRenderMgr{renderMgr}
{
}

void GUIManager::Draw()
{
	for (const auto& button : mButtons)
	{
		mRenderMgr.Draw(*button);
	}
}