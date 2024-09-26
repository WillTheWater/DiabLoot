#include "AssetManager.h"


AssetManager::AssetManager()
    :mTextboxColor{ sf::Color({ 0, 0, 0, 200 }) }
{
    InitializeTextureSprites();
    InitializeFontsAndTexts();
}

void AssetManager::InitializeTextureSprites()
{
    for (int i{ 0 }; i < TEXTURES::MAX_TEXTURES; i++)
    {
        mTextures.push_back(std::make_unique<sf::Texture>());
    }
    assert(std::ssize(mTextures) == TEXTURES::MAX_TEXTURES && "AssetManager failed to initialize correct number of textures\n");

    for (int i{ 0 }; i < SPRITES::MAX_SPRITES; i++)
    {
        mSprites.push_back(std::make_unique<sf::Sprite>());
    }
    assert(std::ssize(mSprites) == SPRITES::MAX_SPRITES && "AssetManager failed to initialize correct number of sprites\n");

    mTextures[TEXTURES::MAINMENU]->loadFromFile("assets/graphics/mainmenu.png");
    mTextures[TEXTURES::BUTTON]->loadFromFile("assets/graphics/button.png");
    mTextures[TEXTURES::INVENTORY]->loadFromFile("assets/graphics/inventory.png");
    mTextures[TEXTURES::CHESTCLOSED]->loadFromFile("assets/graphics/chestclosed.png");
    mTextures[TEXTURES::CHESTOPENED]->loadFromFile("assets/graphics/chestopened.png");
    mTextures[TEXTURES::MAP_ONE]->loadFromFile("assets/graphics/map1.png");
    mTextures[TEXTURES::MAP_TWO]->loadFromFile("assets/graphics/map2.png");
    mTextures[TEXTURES::MAP_THREE]->loadFromFile("assets/graphics/map3.png");
    mTextures[TEXTURES::PARTICLE]->loadFromFile("assets/graphics/particle.png");
    mTextures[TEXTURES::AMULET]->loadFromFile("assets/graphics/items/amulet.png");
    mTextures[TEXTURES::CHARM]->loadFromFile("assets/graphics/items/charm.png");
    mTextures[TEXTURES::REJUV]->loadFromFile("assets/graphics/items/rejuv.png");
    mTextures[TEXTURES::RING]->loadFromFile("assets/graphics/items/ring.png");
    mTextures[TEXTURES::RUNE1]->loadFromFile("assets/graphics/items/rune1.png");
    mTextures[TEXTURES::TPSCROLL]->loadFromFile("assets/graphics/items/tpscroll.png");

    mSprites[SPRITES::MAINMENU]->setTexture(GetTexture(TEXTURES::MAINMENU));
    mSprites[SPRITES::MAP_ONE]->setTexture(GetTexture(TEXTURES::MAP_ONE));
    mSprites[SPRITES::MAP_TWO]->setTexture(GetTexture(TEXTURES::MAP_TWO));
    mSprites[SPRITES::MAP_THREE]->setTexture(GetTexture(TEXTURES::MAP_THREE));
    mSprites[SPRITES::BUTTON]->setTexture(GetTexture(TEXTURES::BUTTON));
    mSprites[SPRITES::INVENTORY]->setTexture(GetTexture(TEXTURES::INVENTORY));
    mSprites[SPRITES::CHESTCLOSED]->setTexture(GetTexture(TEXTURES::CHESTCLOSED));
    mSprites[SPRITES::CHESTOPENED]->setTexture(GetTexture(TEXTURES::CHESTOPENED));
    mSprites[SPRITES::PARTICLE]->setTexture(GetTexture(TEXTURES::PARTICLE));
    mSprites[SPRITES::AMULET]->setTexture(GetTexture(TEXTURES::AMULET));
    mSprites[SPRITES::CHARM]->setTexture(GetTexture(TEXTURES::CHARM));
    mSprites[SPRITES::REJUV]->setTexture(GetTexture(TEXTURES::REJUV));
    mSprites[SPRITES::RING]->setTexture(GetTexture(TEXTURES::RING));
    mSprites[SPRITES::RUNE1]->setTexture(GetTexture(TEXTURES::RUNE1));
    mSprites[SPRITES::TPSCROLL]->setTexture(GetTexture(TEXTURES::TPSCROLL));
}

void AssetManager::InitializeFontsAndTexts()
{
    for (int i{ 0 }; i < FONTS::MAX_FONTS; i++)
    {
        mFonts.push_back(std::make_unique<sf::Font>());
    }
    assert(std::ssize(mFonts) == FONTS::MAX_FONTS && "AssetManager failed to initialize correct number of fonts\n");

    for (int i{ 0 }; i < ITEMID::MAX_ITEMS; i++)
    {
        mItemTexts.push_back(std::make_unique<sf::Text>());
    }
    assert(std::ssize(mItemTexts) == ITEMID::MAX_ITEMS && "AssetManager failed to initialize correct number of item texts\n");

    // Load fonts
    mFonts[FONTS::LIGHT]->loadFromFile("assets/font/lightdiablo.ttf");
    mFonts[FONTS::BOLD]->loadFromFile("assets/font/bolddiablo.ttf");

    // Set Up Texts
    mItemTexts[ITEMID::AMULET]->setString("Amulet");
    mItemTexts[ITEMID::CHARM]->setString("Small Charm");
    mItemTexts[ITEMID::REJUV]->setString("Rejuvenation Potion");
    mItemTexts[ITEMID::RING]->setString("Ring");
    mItemTexts[ITEMID::RUNE1]->setString("Rune");
    mItemTexts[ITEMID::TPSCROLL]->setString("Teleportation Scroll");

    for (auto& itemText : mItemTexts)
    {
        itemText->setFont(*mFonts[FONTS::LIGHT]);
        itemText->setCharacterSize(20);
    }
}

sf::Texture& AssetManager::GetTexture(TEXTURES::TEXTURE texture)
{
    assert(texture < TEXTURES::MAX_TEXTURES && texture >= 0 && "Attempted to get texture that doesn't exist!\n");
    return *mTextures[texture];
}

sf::Sprite& AssetManager::GetSprite(SPRITES::SPRITE sprite)
{
    assert(sprite < SPRITES::MAX_SPRITES && sprite >= 0 && "Attempted to get sprite that doesn't exist!\n");
    return *mSprites[sprite];
}

sf::Sprite& AssetManager::GetLevelMap(LEVELS::LEVEL level)
{
    switch (level)
    {
    case LEVELS::LEVEL_ONE: return *mSprites[SPRITES::MAP_ONE];
    case LEVELS::LEVEL_TWO: return *mSprites[SPRITES::MAP_TWO];
    case LEVELS::LEVEL_THREE: return *mSprites[SPRITES::MAP_THREE];
    default:
        return *mSprites[SPRITES::MAP_ONE];
    }
}

sf::Text& AssetManager::GetTextForItemID(ITEMID::ITEM item)
{
    return *mItemTexts[item];
}

sf::Sprite& AssetManager::GetSpriteForItem(ITEMID::ITEM item)
{
    switch (item)
    {
    case ITEMID::AMULET: return *mSprites[SPRITES::AMULET];
    case ITEMID::CHARM: return *mSprites[SPRITES::CHARM];
    case ITEMID::REJUV: return *mSprites[SPRITES::REJUV];
    case ITEMID::RING: return *mSprites[SPRITES::RING];
    case ITEMID::RUNE1: return *mSprites[SPRITES::RUNE1];
    case ITEMID::TPSCROLL: return *mSprites[SPRITES::TPSCROLL];
    default: return *mSprites[SPRITES::TPSCROLL];
    }
}

sf::Color AssetManager::GetColorForRarity(ITEMRARITY::RARITY rarity)
{
    switch (rarity)
    {
    case ITEMRARITY::NORMAL:	return sf::Color::White;
    case ITEMRARITY::MAGIC:		return sf::Color{ 82 , 075, 143 };	break;
    case ITEMRARITY::RARE:		return sf::Color{ 253, 216, 53 };	break;
    case ITEMRARITY::SET:		return sf::Color{ 44 , 190, 52 };	break;
    case ITEMRARITY::UNIQUE:	return sf::Color{ 153, 102, 51 };	break;
    case ITEMRARITY::RUNE:		return sf::Color{ 198, 140, 89 };	break;
    default:					return sf::Color::White;			break;
    }                         
}

sf::Color AssetManager::GetTextboxColor()
{
    return mTextboxColor;
}
