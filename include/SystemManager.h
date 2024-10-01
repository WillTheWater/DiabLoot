#pragma once
#include "TimeManager.h"
#include "AssetManager.h"
#include "RenderManager.h"
#include "GUIManager.h"
#include "InputManager.h"
#include "Inventory.h"
#include "LevelManager.h"
#include "FireWorkSystem.h"

#include <functional>

class GameState;
using ChangeStateCallback = std::function<void(std::unique_ptr<GameState>)>;

class System
{
public:
    System() = delete;
    System(TimeManager& timeMgr, RenderManager& renderMgr, AssetManager& assetMgr, GUIManager& guiMgr, InputManager& inputMgr, Inventory& inventory, LevelManager& levelmgr)
        : TimeMgr{ timeMgr }, RenderMgr{ renderMgr }, AssetMgr{ assetMgr }, GUIMgr{ guiMgr }, InputMgr{ inputMgr }, InventoryMgr{ inventory }, LevelMgr{ levelmgr }
    {}

    TimeManager& TimeMgr;
    RenderManager& RenderMgr;
    AssetManager& AssetMgr;
    GUIManager& GUIMgr;
    InputManager& InputMgr;
    Inventory& InventoryMgr;
    LevelManager& LevelMgr;
};