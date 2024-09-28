#include "SoundManager.h"

SoundManager& SoundManager::GetInstance()
{
	static SoundManager instance;
	return instance;
}

void SoundManager::PlaySound(PLAYSOUND::PLAYSOUND sound, float volume, float pitch)
{
	auto& soundToPlay = mAssetMgr->GetSound(sound);
	mActiveSounds.push_back(std::make_pair(&soundToPlay, volume));
	soundToPlay.setVolume(volume);
	soundToPlay.setPitch(pitch);
	soundToPlay.play();
}

void SoundManager::PlayMusic(MUSIC::PLAYMUSIC music, float volume, bool loop)
{
	auto& musicToPlay = mAssetMgr->GetMusic(music);
	mActiveMusic.push_back(std::make_pair(&musicToPlay, volume));
	musicToPlay.setVolume(volume);
	musicToPlay.setLoop(loop);
	musicToPlay.play();
}

void SoundManager::StopMusic(MUSIC::PLAYMUSIC music)
{
	auto& musicToStop = mAssetMgr->GetMusic(music);
	musicToStop.stop();
}

void SoundManager::MuteAudio()
{
    mIsMuted = !mIsMuted;

    if (mIsMuted)
    {
        for (auto& soundPair : mActiveSounds)
        {
            soundPair.first->setVolume(0);
        }
        for (auto& musicPair : mActiveMusic)
        {
            musicPair.first->setVolume(0);
        }
    }
    else
    {
        for (auto& soundPair : mActiveSounds)
        {
            soundPair.first->setVolume(soundPair.second);
        }
        for (auto& musicPair : mActiveMusic)
        {
            musicPair.first->setVolume(musicPair.second);
        }
    }
}