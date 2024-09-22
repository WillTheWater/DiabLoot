#include "PlayState.h"
#include "MainMenuState.h"
#include "Core.h"
#include <cassert>

PlayState::PlayState(TimeManager& timeMgr, RenderManager& renderMgr, InputManager& inputMgr, EventManager& eventMgr, ChangeStateCallback changeStateCB)
	: GameState{ timeMgr, renderMgr, inputMgr, eventMgr, changeStateCB }
	, mParticleUniqueId{0}
{
	mChests.reserve(10);
	mParticles.reserve(20);
}

void PlayState::Enter()
{
	mInputManager.AddObserver(this);
}

void PlayState::Exit()
{
	mInputManager.RemoveObserver(this);
}

void PlayState::Update()
{
	float dt = mTimeManager.GetDeltaTime();

}

void PlayState::Draw()
{
	mRenderManager.PlayRender();
}

void PlayState::OnMouseMove(int x, int y)
{
}

void PlayState::OnKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::I)
	{
		LOG("Open Inventory")
	}
}
void PlayState::OnKeyRelease(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Escape)
	{
		auto newState = std::make_unique<MainMenuState>(mTimeManager, mRenderManager, mInputManager, mEventManager, mChangeStateCB);
		mChangeStateCB(std::move(newState));
	}
}
void PlayState::OnMouseClick(sf::Mouse::Button button)
{
	LOG("Observer: Mouse clicked")
}
void PlayState::OnMouseRelease(sf::Mouse::Button button)
{
	LOG("Observer: Mouse released")
}

void PlayState::SpawnChests()
{
	// Update this to have actual chest positions
	mChests.push_back(std::make_unique<Chest>(sf::Vector2f{ 600.f,600.f }));
}

int PlayState::GetUniqueParticleId()
{
	mParticleUniqueId++;
	return mParticleUniqueId;
}

void PlayState::SpawnParticles(sf::Vector2f position) 
{
	int numOfParticles = MathU::Random(5, 10);
	// Need to solve the function bind problem below
	std::function<void(sf::Vector2f, Particle&)> callback = [this](sf::Vector2f pos, Particle& particle) {this->SpawnItem(pos, particle); };
	float animStep = 0.1f;
	for (int i{ 0 }; i < numOfParticles; i++)
	{
		float randDist = MathU::Random(10.f, 20.f);
		float randAngle = MathU::Random(0.f, 360.f);
		float randAnchorheight = MathU::Random(200.f, 500.f) * -1;
		Vec2 endPos{ randDist, 0 };
		endPos = endPos + Vec2{ position };
		endPos = endPos.getRotatedVector(randAngle);
		Vec2 startPos{ position };
		int id = GetUniqueParticleId();
		mParticles.push_back(std::make_unique<Particle>(id, startPos, endPos, randAnchorheight, animStep, callback));
	}
}

void PlayState::UpdateParticles()
{
	for (auto& particle : mParticles)
	{
		particle->stepParticle();
	}
}

void PlayState::RemoveParticle(Particle& particle)
{
	// Check that this works
	bool success = false;
	for (std::vector<std::unique_ptr<Particle>>::iterator it = mParticles.begin(); it != mParticles.end();)
	{
		if (it->get()->getId() == particle.getId())
		{
			mParticles.erase(it);
			success = true;
		}
	}
	// Can remove this later
	assert(success && "PlayState::RemoveParticle failed to remove the particle");
}

void PlayState::SpawnItem(sf::Vector2f, Particle& particle)
{
	RemoveParticle(particle);
}