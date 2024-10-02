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

	sf::Texture&									GetTexture(TEXTURES::TEXTURE texture) const;
	const sf::Sprite&								GetSprite(SPRITES::SPRITE sprite) const;
	const sf::Image&								GetImage(IMAGES::IMAGE image) const;
	sf::SoundBuffer&								GetSoundBuffer(SOUNDBUFFERS::SOUNDBUFFER soundbuffer) const;
	sf::Sound&										GetSound(PLAYSOUND::PLAYSOUND sound) const;
	sf::Music&										GetMusic(MUSIC::PLAYMUSIC music) const;
	const sf::Sprite&								GetLevelMap(LEVELS::LEVEL level) const;
	const sf::Text&									GetTextForItemID(ITEMID::ITEM item) const;
	const sf::Text&									GetTextForButtons(BUTTONS::BUTTON_TEXT text) const;
	const sf::Sprite&								GetSpriteForItem(ITEMID::ITEM item) const;
	const sf::Color									GetColorForItemText(std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> item) const;
	const sf::Color									GetTextboxColor() const;
	const sf::Sprite&								GetSpriteForButton(BUTTONS::BUTTON_TYPE button) const;
	const sf::Sprite&								GetSpriteForGoldQuantity(int quantity) const;
	const sf::Font&									GetFont(FONTS::FONT font) const;
	const PLAYSOUND::PLAYSOUND						GetSoundForItem(std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> item) const;
	const int										GetCostForNextLevelUpgrade(LEVELS::UPGRADE levelUpgrade) const;
	const std::string&								GetRarityAsString(ITEMRARITY::RARITY rarity) const;

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
	const sf::Color																	mTextboxColor;
	std::array<std::unique_ptr<sf::Text>, BUTTONS::MAX_BUTTONS>						mButtonTexts;
	std::array<std::string, ITEMRARITY::MAX_RARITIES>								mRarityStrings;
};