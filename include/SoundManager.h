#pragma once
#include "AssetManager.h"
#include <queue>
#include <random> 
#include <memory>
#include <vector> 
#include <utility> 
#include <cassert> 
#include <iostream>
#include "MathUtilities.h"

class SoundManager
{
public:
	static SoundManager& GetInstance();
	void											SetAssetMgr(AssetManager* assetMgr) { mAssetMgr = assetMgr; }

	void											PlaySound(PLAYSOUND::PLAYSOUND sound, float volume = 100.f, float pitch = 1.f);
	void											PlayMusic(MUSIC::PLAYMUSIC music, float volume = 100.f, bool loop = true);
	void											StopMusic(MUSIC::PLAYMUSIC music);
	AUDIO_MUTE::AUDIOSTATE							GetAudioState() const;

	void											AudioControl();
	void											MuteToggle();
	void											FillMusicQueue();
	void											StartMusicSequence();
	void											PlayItemSound(std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> itemid);

private:
	SoundManager() = default;
	SoundManager(const SoundManager&) = delete;
	SoundManager&									operator = (const SoundManager&) = delete;

	MUSIC::PLAYMUSIC								mCurrentlyPlaying = MUSIC::MAX_MUSIC_FILES;
	AssetManager*									mAssetMgr = nullptr;
	std::vector<std::pair<sf::Sound*, float>>		mActiveSounds;
	std::vector<std::pair<sf::Music*, float>>		mActiveMusic;
	bool											mIsMuted = false;
	std::queue<MUSIC::PLAYMUSIC>					mMusicQueue;
	float											mDefaultVolume = 10.f;
	AUDIO_MUTE::AUDIOSTATE							mAudioState = AUDIO_MUTE::AUDIOSTATE::UNMUTED;
};