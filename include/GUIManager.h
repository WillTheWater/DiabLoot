#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "RenderManager.h"
#include "Button.h"

class GUIManager
{
public:
	GUIManager(RenderManager& renderMgr);
	void										Draw();
	void										Update();


private:
	RenderManager& mRenderMgr;
	std::vector<std::unique_ptr<Button>>		mButtons;
};