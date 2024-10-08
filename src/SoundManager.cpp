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

void SoundManager::PlayThunder()
{
    PLAYSOUND::PLAYSOUND randomThunder = (PLAYSOUND::PLAYSOUND)MathU::Random((int)PLAYSOUND::THUNDER_1, (int)PLAYSOUND::THUNDER_3);
    PlayASound(randomThunder, 40.f, 1.0f, false);
}

void SoundManager::StopThunder()
{
    StopPlayingSound(PLAYSOUND::THUNDER_1);
    StopPlayingSound(PLAYSOUND::THUNDER_2);
    StopPlayingSound(PLAYSOUND::THUNDER_3);
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

    for (const auto& song : songs) 
    {
        mMusicQueue.push(song);
    }
}

void SoundManager::PlayNextSong()
{
    if (!mMusicQueue.empty()) {
        mCurrentlyPlaying = mMusicQueue.front();  // Get the next song in the queue
        mMusicQueue.pop();  // Remove the current song from the queue

        // Retrieve the corresponding sf::Music* from the asset manager
        auto music = &mAssetMgr->GetMusic(mCurrentlyPlaying);
        if (music) {  // Check if the music pointer is valid
            mActiveMusic.push_back({ music, mDefaultVolume });  // Store it as the active music
            PlayMusic(mCurrentlyPlaying, mDefaultVolume, false);  // Play the song without looping
        }
    }
    else {
        // If the queue is empty, refill it
        FillMusicQueue();
    }
}

void SoundManager::StartMusicSequence()
{
    // Check if the currently playing music has stopped
    if (!mActiveMusic.empty() && mActiveMusic.front().first->getStatus() == sf::SoundSource::Stopped) {
        mActiveMusic.clear();  // Clear the currently playing music
    }

    // If there's no active music, play the next song
    if (mActiveMusic.empty()) {
        PlayNextSong();
    }
}

void SoundManager::UpdateMusicQueue()
{
    // Check if there's currently active music
    if (!mActiveMusic.empty()) {
        // Check if the currently playing music has stopped
        if (mActiveMusic.front().first->getStatus() == sf::SoundSource::Stopped) {
            mActiveMusic.clear();  // Clear the currently playing music
            PlayNextSong();  // Play the next song in the queue
        }
    }
    else {
        // If there is no active music, start from the queue
        PlayNextSong();
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
        PlayASound(sound, modulator, pitchShifter);
    }
}

void SoundManager::AddFireworkSound()
{
    AUDIO_MUTE::AUDIOSTATE currentAudioState = GetAudioState();
    sf::Sound firework = mAssetMgr->GetSound(PLAYSOUND::FIREWORKS);
    auto pitchShifter = MathU::Random(0.8f, 1.2f);
    auto modulator = MathU::Random(8.f, 10.f);
    firework.setVolume(modulator);
    firework.setPitch(pitchShifter);
    mFireWorkSounds.push_back(firework);
    mFireWorkSounds.back().play();
}

void SoundManager::UpdateFireworkSounds()
{
    for (auto& firework : mFireWorkSounds)
    {
        if (firework.getStatus() == sf::SoundSource::Playing)
        {
            if (mAudioState == AUDIO_MUTE::AUDIOSTATE::MUTE_ALL)
            {
                firework.stop();
            }
        }
        else if(firework.getStatus() == sf::SoundSource::Stopped)
        {
            mFireWorkSounds.pop_front();
        }
    }
}

void SoundManager::StopFireWorkSounds()
{
    for (auto& sound : mFireWorkSounds)
    {
        sound.stop();
    }
    mFireWorkSounds.clear();
}


