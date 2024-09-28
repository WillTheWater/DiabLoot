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

	void MuteAudio();

private:
	SoundManager() = default;
	SoundManager(const SoundManager&) = delete;
	SoundManager& operator = (const SoundManager&) = delete;

	MUSIC::PLAYMUSIC mCurrentlyPlaying = MUSIC::MAX_MUSIC_FILES;
	AssetManager* mAssetMgr = nullptr;
	std::vector<std::pair<sf::Sound*, float>> mActiveSounds;
	std::vector<std::pair<sf::Music*, float>> mActiveMusic;
	bool mIsMuted = false;
};