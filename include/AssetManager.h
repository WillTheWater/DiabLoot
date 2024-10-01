#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>
#include <array>
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
	sf::Color										GetColorForItemText(std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> item);
	sf::Color										GetTextboxColor() const;
	sf::Sprite&										GetSpriteForButton(BUTTONS::BUTTON_TYPE button);
	sf::Sprite&										GetSpriteForGoldQuantity(int quantity);
	sf::Font& GetFont(FONTS::FONT font);
	PLAYSOUND::PLAYSOUND							GetSoundForItem(std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> item);
	int												GetCostForNextLevelUpgrade(LEVELS::UPGRADE levelUpgrade);

private:
	void																			InitializeTextureSprites();
	void																			InitializeFontsAndTexts();
	void																			InitializeSounds();
	void																			InitializeMusic();
	void																			InitializeImages();
	std::array<std::unique_ptr<sf::Texture>, TEXTURES::MAX_TEXTURES>				mTextures;
	std::array<std::unique_ptr<sf::Sprite>, SPRITES::MAX_SPRITES>					mSprites;
	std::array<std::unique_ptr<sf::Image>, IMAGES::MAX_IMAGES>						mImages;
	std::array<std::unique_ptr<sf::SoundBuffer>, SOUNDBUFFERS::MAX_SOUNDSBUFFERS>	mSoundBuffers;
	std::array<std::unique_ptr<sf::Sound>, PLAYSOUND::MAX_SOUNDS>					mSounds;
	std::array<std::unique_ptr<sf::Music>, MUSIC::MAX_MUSIC_FILES>					mMusic;
	std::array<std::unique_ptr<sf::Font>, FONTS::MAX_FONTS>							mFonts;
	std::array<std::unique_ptr<sf::Text>, ITEMID::MAX_ITEMS>						mItemTexts;
	sf::Color																		mTextboxColor;
	std::array<std::unique_ptr<sf::Text>, BUTTONS::MAX_BUTTONS>						mButtonTexts;
};