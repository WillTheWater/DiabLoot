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
}