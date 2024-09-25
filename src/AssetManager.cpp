#include "AssetManager.h"


AssetManager::AssetManager()
{
    InitializeTextureSprites();
    InitializeFontsAndTexts();
    InitializeImages();
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
    mTextures[TEXTURES::WIDE_BUTTON]->loadFromFile("assets/graphics/button.png");
    mTextures[TEXTURES::SQUARE_BUTTON]->loadFromFile("assets/graphics/inventorybutton.png");
    mTextures[TEXTURES::INVENTORY]->loadFromFile("assets/graphics/inventory.png");
    mTextures[TEXTURES::CHESTCLOSED]->loadFromFile("assets/graphics/chestclosed.png");
    mTextures[TEXTURES::CHESTOPENED]->loadFromFile("assets/graphics/chestopened.png");
    mTextures[TEXTURES::MAP_ONE]->loadFromFile("assets/graphics/map1.png");
    mTextures[TEXTURES::PARTICLE]->loadFromFile("assets/graphics/particle.png");
    mTextures[TEXTURES::AMULET]->loadFromFile("assets/graphics/items/amulet.png");
    mTextures[TEXTURES::CHARM]->loadFromFile("assets/graphics/items/charm.png");
    mTextures[TEXTURES::REJUV]->loadFromFile("assets/graphics/items/amulet.png");
    mTextures[TEXTURES::RING]->loadFromFile("assets/graphics/items/rejuv.png");
    mTextures[TEXTURES::RUNE1]->loadFromFile("assets/graphics/items/rune1.png");
    mTextures[TEXTURES::TPSCROLL]->loadFromFile("assets/graphics/items/tpscroll.png");

    mSprites[SPRITES::MAINMENU]->setTexture(GetTexture(TEXTURES::MAINMENU));
    mSprites[SPRITES::MAP_ONE]->setTexture(GetTexture(TEXTURES::MAP_ONE));
    mSprites[SPRITES::WIDE_BUTTON]->setTexture(GetTexture(TEXTURES::WIDE_BUTTON));
    mSprites[SPRITES::SQUARE_BUTTON]->setTexture(GetTexture(TEXTURES::SQUARE_BUTTON));
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

    for (int i{ 0 }; i < BUTTONS::MAX_BUTTONS; i++)
    {
        mButtonTexts.push_back(std::make_unique<sf::Text>());
    }
    assert(std::ssize(mButtonTexts) == BUTTONS::MAX_BUTTONS && "AssetManager failed to initialize correct number of button texts\n");


    // Load fonts
    mFonts[FONTS::LIGHT]->loadFromFile("assets/font/lightdiablo.ttf");
    mFonts[FONTS::BOLD]->loadFromFile("assets/font/bolddiablo.ttf");

    mButtonTexts[BUTTONS::START]->setString("Start");
    mButtonTexts[BUTTONS::EXIT]->setString("Exit");
    mButtonTexts[BUTTONS::NEXT_LEVEL]->setString("Next Level");

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
    for (auto& button : mButtonTexts)
    {
        button->setFont(*mFonts[FONTS::BOLD]);
        button->setFillColor(sf::Color::Black);
        button->setCharacterSize(45);
    }
}

void AssetManager::InitializeImages()
{
    for (int i{ 0 }; i < IMAGES::MAX_IMAGES; i++)
    {
        mImages.push_back(std::make_unique<sf::Image>());
    }
    assert(std::ssize(mImages) == IMAGES::MAX_IMAGES && "AssetManager failed to initialize correct number of images\n");

    // Load Images
    mImages[IMAGES::DEFAULT_CURSOR]->loadFromFile("assets/graphics/cursoropen.png");
    mImages[IMAGES::CLOSED_CURSOR]->loadFromFile("assets/graphics/cursorclosed.png");
    mImages[IMAGES::ICON]->loadFromFile("assets/graphics/icon.png");
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

sf::Image& AssetManager::GetImage(IMAGES::IMAGE image)
{
    assert(image < IMAGES::MAX_IMAGES && image >= 0 && "Attempted to get image that doesn't exist!\n");
    return *mImages[image];
}

sf::Sprite& AssetManager::GetLevelMap(LEVELS::LEVEL level)
{
    switch (level)
    {
    case LEVELS::LEVEL_ONE: return *mSprites[SPRITES::MAP_ONE];
    default:
        return *mSprites[SPRITES::MAP_ONE];
    }
}

sf::Text& AssetManager::GetTextForItemID(ITEMID::ITEM item)
{
    return *mItemTexts[item];
}

sf::Text& AssetManager::GetTextForButtons(BUTTONS::BUTTON_TEXT text)
{
    return *mButtonTexts[text];
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

sf::Sprite& AssetManager::GetSpriteForButton(BUTTONS::BUTTON_TYPE button)
{
    switch (button)
    {
    case BUTTONS::WIDE: return *mSprites[SPRITES::WIDE_BUTTON];
    default: return *mSprites[SPRITES::SQUARE_BUTTON];
    }
}
