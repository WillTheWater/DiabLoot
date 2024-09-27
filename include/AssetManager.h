#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>
#include "Assets.h"
#include <cassert>

class AssetManager
{
public:
	AssetManager();

	sf::Texture&									GetTexture(TEXTURES::TEXTURE texture);
	sf::Sprite&										GetSprite(SPRITES::SPRITE sprite);
	sf::Image&										GetImage(IMAGES::IMAGE image);
	sf::SoundBuffer&								GetSoundBuffer(SOUNDBUFFERS::SOUNDBUFFER soundbuffer);
	sf::Sound&										GetSound(PLAYSOUND::PLAYSOUND sound);
	sf::Music&										GetMusic(MUSIC::PLAYMUSIC music);
	sf::Sprite&										GetLevelMap(LEVELS::LEVEL level);
	sf::Text&										GetTextForItemID(ITEMID::ITEM item);
	sf::Text&										GetTextForButtons(BUTTONS::BUTTON_TEXT text);
	sf::Sprite&										GetSpriteForItem(ITEMID::ITEM item);
	sf::Color										GetColorForRarity(ITEMRARITY::RARITY rarity);
	sf::Color										GetTextboxColor();
	sf::Sprite&										GetSpriteForButton(BUTTONS::BUTTON_TYPE button);
	sf::Sprite&										GetSpriteForGoldQuantity(int quantity);

private:
	void											InitializeTextureSprites();
	void											InitializeFontsAndTexts();
	void											InitializeSounds();
	void											InitializeMusic();
	void											InitializeImages();
	std::vector<std::unique_ptr<sf::Texture>>		mTextures;
	std::vector<std::unique_ptr<sf::Sprite>>		mSprites;
	std::vector<std::unique_ptr<sf::Image>>			mImages;
	std::vector<std::unique_ptr<sf::SoundBuffer>>	mSoundBuffers;
	std::vector<std::unique_ptr<sf::Sound>>			mSounds;
	std::vector<std::unique_ptr<sf::Music>>			mMusic;
	std::vector<std::unique_ptr<sf::Font>>			mFonts;
	std::vector<std::unique_ptr<sf::Text>>			mItemTexts;
	sf::Color										mTextboxColor;
	std::vector<std::unique_ptr<sf::Text>>			mButtonTexts;
};