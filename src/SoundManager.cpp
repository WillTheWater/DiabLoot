#include "SoundManager.h"

SoundManager& SoundManager::GetInstance()
{
	static SoundManager instance;
	return instance;
}

void SoundManager::PlayASound(PLAYSOUND::PLAYSOUND sound, float volume, float pitch, bool loop)
{
    float finalVolume = mIsMuted ? 0 : volume;
    auto& soundToPlay = mAssetMgr->GetSound(sound);

    if (std::find_if(mActiveSounds.begin(), mActiveSounds.end(),
        [&soundToPlay](const std::pair<sf::Sound*, float>& activeSound) { return activeSound.first == &soundToPlay; }) == mActiveSounds.end())
    {
        mActiveSounds.push_back(std::make_pair(&soundToPlay, volume));
    }

    soundToPlay.setVolume(finalVolume);
    soundToPlay.setPitch(pitch);
    soundToPlay.setLoop(loop);
    soundToPlay.play();
}

void SoundManager::StopPlayingSound(PLAYSOUND::PLAYSOUND sound)
{
    auto& soundToStop = mAssetMgr->GetSound(sound);
    soundToStop.stop();
}

void SoundManager::ForceStopAllSounds()
{
    for (int i{ 0 }; i < PLAYSOUND::MAX_SOUNDS; i++)
    {
        StopPlayingSound(static_cast<PLAYSOUND::PLAYSOUND>(i));
    }
}

void SoundManager::PlayMusic(MUSIC::PLAYMUSIC music, float volume, bool loop)
{
    if (music == mCurrentlyPlaying && mAssetMgr->GetMusic(mCurrentlyPlaying).getStatus() == sf::SoundSource::Playing)
        return;

    auto& musicToPlay = mAssetMgr->GetMusic(music);
    float finalVolume = mIsMuted ? 0 : volume;

    if (mCurrentlyPlaying != MUSIC::MAX_MUSIC_FILES)
    {
        mAssetMgr->GetMusic(mCurrentlyPlaying).stop();
    }

    if (std::find_if(mActiveMusic.begin(), mActiveMusic.end(),
        [&musicToPlay](const std::pair<sf::Music*, float>& activeMusic) { return activeMusic.first == &musicToPlay; }) == mActiveMusic.end())
    {
        mActiveMusic.push_back(std::make_pair(&musicToPlay, volume));
    }

    musicToPlay.setVolume(finalVolume);
    musicToPlay.setLoop(loop);
    musicToPlay.play();

    mCurrentlyPlaying = music;
}

void SoundManager::StopMusic(MUSIC::PLAYMUSIC music)
{
	auto& musicToStop = mAssetMgr->GetMusic(music);
	musicToStop.stop();
	mCurrentlyPlaying = MUSIC::MAX_MUSIC_FILES;
}

AUDIO_MUTE::AUDIOSTATE SoundManager::GetAudioState() const
{
    return mAudioState;
}

void SoundManager::AudioControl()
{
    switch (mAudioState)
    {
    case AUDIO_MUTE::AUDIOSTATE::MUTE_ALL:
        // Mute both sound effects and music
        for (auto& soundPair : mActiveSounds)
        {
            soundPair.first->setVolume(0);
        }
        for (auto& musicPair : mActiveMusic)
        {
            musicPair.first->setVolume(0);
        }
        break;

    case AUDIO_MUTE::AUDIOSTATE::MUTE_MUSIC:
        // Enable sound effects, mute music
        for (auto& soundPair : mActiveSounds)
        {
            soundPair.first->setVolume(soundPair.second);
        }
        for (auto& musicPair : mActiveMusic)
        {
            musicPair.first->setVolume(0);
        }
        break;

    case AUDIO_MUTE::AUDIOSTATE::UNMUTED:
        // Enable both sound effects and music
        for (auto& soundPair : mActiveSounds)
        {
            soundPair.first->setVolume(soundPair.second);
        }
        for (auto& musicPair : mActiveMusic)
        {
            musicPair.first->setVolume(musicPair.second);
        }
        break;
    }
}

void SoundManager::MuteToggle()
{
    // Cycle through the 3 states of AUDIO_MUTE::AUDIOSTATE
    switch (mAudioState)
    {
    case AUDIO_MUTE::AUDIOSTATE::UNMUTED:
        // If currently unmuted
        mAudioState = AUDIO_MUTE::AUDIOSTATE::MUTE_MUSIC;
        break;

    case AUDIO_MUTE::AUDIOSTATE::MUTE_MUSIC:
        // If music is muted
        mAudioState = AUDIO_MUTE::AUDIOSTATE::MUTE_ALL;
        break;

    case AUDIO_MUTE::AUDIOSTATE::MUTE_ALL:
        // If everything is muted
        mAudioState = AUDIO_MUTE::AUDIOSTATE::UNMUTED;
        break;
    }
    AudioControl();
}

void SoundManager::FillMusicQueue()
{
    std::queue<MUSIC::PLAYMUSIC> empty;
    std::swap(mMusicQueue, empty);

    std::vector<MUSIC::PLAYMUSIC> songs = { MUSIC::TRISTRAM, MUSIC::CRYPT, MUSIC::DIABLO, MUSIC::KURAST, MUSIC::LUTGHOLEIN, MUSIC::HAREM };
    
    std::shuffle(songs.begin(), songs.end(), std::default_random_engine(static_cast<unsigned>(std::time(nullptr))));

    for (const auto& song : songs) {
        mMusicQueue.push(song);
    }
}

void SoundManager::StartMusicSequence()
{
    FillMusicQueue();

    if (!mMusicQueue.empty()) {
        mCurrentlyPlaying = mMusicQueue.front();
        PlayMusic(mCurrentlyPlaying, mDefaultVolume, true);
    }
}

void SoundManager::PlayItemSound(std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> itemid)
{
    AUDIO_MUTE::AUDIOSTATE currentAudioState = GetAudioState();
    PLAYSOUND::PLAYSOUND sound = mAssetMgr->GetSoundForItem(itemid);
    auto pitchShifter = MathU::Random(0.8f, 1.2f);
    auto modulator = MathU::Random(20.f, 40.f);
    if (currentAudioState == AUDIO_MUTE::AUDIOSTATE::UNMUTED ||
        currentAudioState == AUDIO_MUTE::AUDIOSTATE::MUTE_MUSIC)
    {
        SoundManager::GetInstance().PlayASound(sound, modulator, pitchShifter);
    }
}
