#include "SoundManager.h"

SoundManager& SoundManager::GetInstance()
{
	static SoundManager instance;
	return instance;
}

void SoundManager::PlaySound(PLAYSOUND::PLAYSOUND sound, float volume, float pitch)
{
	auto& soundToPlay = mAssetMgr->GetSound(sound);
	soundToPlay.setVolume(volume);
	soundToPlay.setPitch(pitch);
	soundToPlay.play();
}

void SoundManager::PlayMusic(MUSIC::PLAYMUSIC music, float volume, bool loop)
{
	
	auto& musicToPlay = mAssetMgr->GetMusic(music);
	musicToPlay.setVolume(volume);
	musicToPlay.setLoop(loop);
	if (music != mCurrentlyPlaying)
	{
		musicToPlay.play();
	}
	mCurrentlyPlaying = music;
}

void SoundManager::StopMusic(MUSIC::PLAYMUSIC music)
{
	auto& musicToStop = mAssetMgr->GetMusic(music);
	musicToStop.stop();
	mCurrentlyPlaying = MUSIC::MAX_MUSIC_FILES;
}
