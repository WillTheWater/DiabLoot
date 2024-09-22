#pragma once
#include "GameState.h"
#include "Particle.h"
#include "Chest.h"
#include "MathUtilities.h"

class PlayState : public GameState, public InputObserver
{
public:
	PlayState(TimeManager& timeMgr, RenderManager& renderMgr, InputManager& inputMgr, EventManager& eventMgr, ChangeStateCallback changeStateCB);

	virtual void							Enter() override;
	virtual void							Exit() override;
	virtual void							Update() override;
	virtual void							Draw() override;

	void									OnMouseMove(int x, int y) override;
	void									OnKeyPress(sf::Keyboard::Key key) override;
	void									OnKeyRelease(sf::Keyboard::Key key) override;
	void									OnMouseClick(sf::Mouse::Button button) override;
	void									OnMouseRelease(sf::Mouse::Button button) override;
	void									DrawParticles();
	int										GetUniqueParticleId();
	void									SpawnChests();
	void									SpawnParticles(Chest& chest);
	void									UpdateParticles();
	void									RemoveParticle(Particle& particle);
	void									SpawnItem(Particle& particle);
private:
	int										mParticleUniqueId;
	std::vector<std::unique_ptr<Chest>>		mChests;
	std::vector<std::unique_ptr<Particle>>	mParticles;
};