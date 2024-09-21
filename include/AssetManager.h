#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>
#include "Assets.h"

class AssetManager
{
public:
	AssetManager();

	sf::Texture&								GetTexture(TEXTURES::TEXTURE texture);
	sf::Sprite&									GetSprite(SPRITES::SPRITE sprite);

private:
	void										InitializeTextureSprites();
	std::vector<std::unique_ptr<sf::Texture>>	mTextures;
	std::vector<std::unique_ptr<sf::Sprite>>	mSprites;
};