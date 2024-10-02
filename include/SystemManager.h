#pragma once
#include "TimeManager.h"
#include "AssetManager.h"
#include "RenderManager.h"
#include "GUIManager.h"
#include "InputManager.h"
#include "Inventory.h"
#include "LevelManager.h"

#include <functional>

class GameState;
using ChangeStateCallback = std::function<void(std::unique_ptr<GameState>)>;

class System
{
public:
    System() = delete;
    System(TimeManager& timeMgr, RenderManager& renderMgr, AssetManager& assetMgr, GUIManager& guiMgr, InputManager& inputMgr, Inventory& inventory, LevelManager& levelmgr, FireWorkSystem& fireworks)
        : TimeMgr{ timeMgr }, RenderMgr{ renderMgr }, AssetMgr{ assetMgr }, GUIMgr{ guiMgr }, InputMgr{ inputMgr }, InventoryMgr{ inventory }, LevelMgr{ levelmgr }, FireWorks{ fireworks }
    {}

    void Save() { InventoryMgr.SaveInventory(); LevelMgr.SaveLevels(); }
    void Load() { InventoryMgr.LoadInventory(); LevelMgr.LoadLevels(); }

    TimeManager& TimeMgr;
    RenderManager& RenderMgr;
    AssetManager& AssetMgr;
    GUIManager& GUIMgr;
    InputManager& InputMgr;
    Inventory& InventoryMgr;
    LevelManager& LevelMgr;
    FireWorkSystem& FireWorks;
};