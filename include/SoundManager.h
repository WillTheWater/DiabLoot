#pragma once
#include "AssetManager.h"
#include "Assets.h"

class SoundManager
{
public:
	static SoundManager& GetInstance();
	void SetAssetMgr(AssetManager* assetMgr) { mAssetMgr = assetMgr; }

	void PlaySound(PLAYSOUND::PLAYSOUND sound, float volume = 100.f, float pitch = 1.f);
	void PlayMusic(MUSIC::PLAYMUSIC music, float volume = 100.f, bool loop = true);
	void StopMusic(MUSIC::PLAYMUSIC music);

private:
	SoundManager() = default;
	SoundManager(const SoundManager&) = delete;
	SoundManager& operator = (const SoundManager&) = delete;

	AssetManager* mAssetMgr = nullptr;
};