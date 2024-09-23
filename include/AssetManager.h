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

	sf::Texture&								GetTexture(TEXTURES::TEXTURE texture);
	sf::Sprite&									GetSprite(SPRITES::SPRITE sprite);
	sf::Sprite&									GetLevelMap(LEVELS::LEVEL level);
	sf::Text&									GetTextForItemID(ITEMID::ITEM item);
	sf::Sprite&									GetSpriteForItem(ITEMID::ITEM item);

private:
	void										InitializeTextureSprites();
	void										InitializeFontsAndTexts();
	std::vector<std::unique_ptr<sf::Texture>>	mTextures;
	std::vector<std::unique_ptr<sf::Sprite>>	mSprites;
	std::vector<std::unique_ptr<sf::Font>>		mFonts;
	std::vector<std::unique_ptr<sf::Text>>		mItemTexts;
};