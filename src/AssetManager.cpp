#include "AssetManager.h"


AssetManager::AssetManager()
    :mTextboxColor{ sf::Color({ 0, 0, 0, 200 }) }
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

    // TEXTURES
    // MENU
    mTextures[TEXTURES::MAINMENU]->loadFromFile("assets/graphics/mainmenu.png");
    // TEXTURES
    mTextures[TEXTURES::WIDE_BUTTON]->loadFromFile("assets/graphics/button.png");
    mTextures[TEXTURES::SQUARE_BUTTON]->loadFromFile("assets/graphics/inventorybutton.png");
    mTextures[TEXTURES::CHESTCLOSED]->loadFromFile("assets/graphics/chestclosed.png");
    mTextures[TEXTURES::CHESTOPENED]->loadFromFile("assets/graphics/chestopened.png");
    // MAPS
    mTextures[TEXTURES::MAP_ONE]->loadFromFile("assets/graphics/map1.png");
    mTextures[TEXTURES::MAP_TWO]->loadFromFile("assets/graphics/map2.png");
    mTextures[TEXTURES::MAP_THREE]->loadFromFile("assets/graphics/map3.png");
    // INVENTORY
    mTextures[TEXTURES::INVENTORY]->loadFromFile("assets/graphics/inventory.png");
    // PARTICLE
    mTextures[TEXTURES::PARTICLE]->loadFromFile("assets/graphics/particle.png");
    // ITEMS
    mTextures[TEXTURES::AMULET]->loadFromFile("assets/graphics/items/amulet.png");
    mTextures[TEXTURES::CHARM]->loadFromFile("assets/graphics/items/charm.png");
    mTextures[TEXTURES::REJUV]->loadFromFile("assets/graphics/items/rejuv.png");
    mTextures[TEXTURES::RING]->loadFromFile("assets/graphics/items/ring.png");
    mTextures[TEXTURES::TPSCROLL]->loadFromFile("assets/graphics/items/tpscroll.png");
    mTextures[TEXTURES::ELRUNE]->loadFromFile("assets/graphics/runes/Elrune1.png");
    mTextures[TEXTURES::ELDRUNE]->loadFromFile("assets/graphics/runes/Eldrune2.png");
    mTextures[TEXTURES::TIRRUNE]->loadFromFile("assets/graphics/runes/Tirrune3.png");
    mTextures[TEXTURES::NEFRUNE]->loadFromFile("assets/graphics/runes/Nefrune4.png");
    mTextures[TEXTURES::ETHRUNE]->loadFromFile("assets/graphics/runes/Ethrune5.png");
    mTextures[TEXTURES::ITHRUNE]->loadFromFile("assets/graphics/runes/Ithrune6.png");
    mTextures[TEXTURES::TALRUNE]->loadFromFile("assets/graphics/runes/Talrune7.png");
    mTextures[TEXTURES::RALRUNE]->loadFromFile("assets/graphics/runes/Ralrune8.png");
    mTextures[TEXTURES::ORTRUNE]->loadFromFile("assets/graphics/runes/Ortrune9.png");
    mTextures[TEXTURES::THULRUNE]->loadFromFile("assets/graphics/runes/Thulrune10.png");
    mTextures[TEXTURES::AMNRUNE]->loadFromFile("assets/graphics/runes/Amnrune11.png");
    mTextures[TEXTURES::SOLRUNE]->loadFromFile("assets/graphics/runes/Solrune12.png");
    mTextures[TEXTURES::SHAELRUNE]->loadFromFile("assets/graphics/runes/Shaelrune13.png");
    mTextures[TEXTURES::DOLRUNE]->loadFromFile("assets/graphics/runes/Dolrune14.png");
    mTextures[TEXTURES::HELRUNE]->loadFromFile("assets/graphics/runes/Helrune15.png");
    mTextures[TEXTURES::IORUNE]->loadFromFile("assets/graphics/runes/Iorune16.png");
    mTextures[TEXTURES::LUMRUNE]->loadFromFile("assets/graphics/runes/Lumrune17.png");
    mTextures[TEXTURES::KORUNE]->loadFromFile("assets/graphics/runes/Korune18.png");
    mTextures[TEXTURES::FALRUNE]->loadFromFile("assets/graphics/runes/Falrune19.png");
    mTextures[TEXTURES::LEMRUNE]->loadFromFile("assets/graphics/runes/Lemrune20.png");
    mTextures[TEXTURES::PULRUNE]->loadFromFile("assets/graphics/runes/Pulrune21.png");
    mTextures[TEXTURES::UMRUNE]->loadFromFile("assets/graphics/runes/Umrune22.png");
    mTextures[TEXTURES::MALRUNE]->loadFromFile("assets/graphics/runes/Malrune23.png");
    mTextures[TEXTURES::ISTRUNE]->loadFromFile("assets/graphics/runes/Istrune24.png");
    mTextures[TEXTURES::GULRUNE]->loadFromFile("assets/graphics/runes/Gulrune25.png");
    mTextures[TEXTURES::VEXRUNE]->loadFromFile("assets/graphics/runes/Vexrune26.png");
    mTextures[TEXTURES::OHMRUNE]->loadFromFile("assets/graphics/runes/Ohmrune27.png");
    mTextures[TEXTURES::LORUNE]->loadFromFile("assets/graphics/runes/Lorune28.png");
    mTextures[TEXTURES::SURRUNE]->loadFromFile("assets/graphics/runes/Surrune29.png");
    mTextures[TEXTURES::BERRUNE]->loadFromFile("assets/graphics/runes/Berrune30.png");
    mTextures[TEXTURES::JAHRUNE]->loadFromFile("assets/graphics/runes/Jahrune31.png");
    mTextures[TEXTURES::CHAMRUNE]->loadFromFile("assets/graphics/runes/Chamrune32.png");
    mTextures[TEXTURES::ZODRUNE]->loadFromFile("assets/graphics/runes/Zodrune33.png");
    mTextures[TEXTURES::GOLD_SMALL]->loadFromFile("assets/graphics/items/gold_large.png");
    mTextures[TEXTURES::GOLD_MEDIUM]->loadFromFile("assets/graphics/items/gold_large.png");
    mTextures[TEXTURES::GOLD_LARGE]->loadFromFile("assets/graphics/items/gold_large.png");
   

    // SPRITES SETUP
    // MENU
    mSprites[SPRITES::MAINMENU]->setTexture(GetTexture(TEXTURES::MAINMENU));
    // MAPS
    mSprites[SPRITES::MAP_ONE]->setTexture(GetTexture(TEXTURES::MAP_ONE));
    mSprites[SPRITES::MAP_TWO]->setTexture(GetTexture(TEXTURES::MAP_TWO));
    mSprites[SPRITES::MAP_THREE]->setTexture(GetTexture(TEXTURES::MAP_THREE));
    // BUTTONS
    mSprites[SPRITES::WIDE_BUTTON]->setTexture(GetTexture(TEXTURES::WIDE_BUTTON));
    mSprites[SPRITES::SQUARE_BUTTON]->setTexture(GetTexture(TEXTURES::SQUARE_BUTTON));
    // INVENTORY
    mSprites[SPRITES::INVENTORY]->setTexture(GetTexture(TEXTURES::INVENTORY));
    // PARTICLE
    mSprites[SPRITES::PARTICLE]->setTexture(GetTexture(TEXTURES::PARTICLE));
    // CHESTS
    mSprites[SPRITES::CHESTCLOSED]->setTexture(GetTexture(TEXTURES::CHESTCLOSED));
    mSprites[SPRITES::CHESTOPENED]->setTexture(GetTexture(TEXTURES::CHESTOPENED));
    // ITEMS
    mSprites[SPRITES::AMULET]->setTexture(GetTexture(TEXTURES::AMULET));
    mSprites[SPRITES::CHARM]->setTexture(GetTexture(TEXTURES::CHARM));
    mSprites[SPRITES::REJUV]->setTexture(GetTexture(TEXTURES::REJUV));
    mSprites[SPRITES::RING]->setTexture(GetTexture(TEXTURES::RING));
    mSprites[SPRITES::TPSCROLL]->setTexture(GetTexture(TEXTURES::TPSCROLL));
    // RUNES
    mSprites[SPRITES::ELRUNE]->setTexture(GetTexture(TEXTURES::ELRUNE));
    mSprites[SPRITES::ELDRUNE]->setTexture(GetTexture(TEXTURES::ELDRUNE));
    mSprites[SPRITES::TIRRUNE]->setTexture(GetTexture(TEXTURES::TIRRUNE));
    mSprites[SPRITES::NEFRUNE]->setTexture(GetTexture(TEXTURES::NEFRUNE));
    mSprites[SPRITES::ETHRUNE]->setTexture(GetTexture(TEXTURES::ETHRUNE));
    mSprites[SPRITES::ITHRUNE]->setTexture(GetTexture(TEXTURES::ITHRUNE));
    mSprites[SPRITES::TALRUNE]->setTexture(GetTexture(TEXTURES::TALRUNE));
    mSprites[SPRITES::RALRUNE]->setTexture(GetTexture(TEXTURES::RALRUNE));
    mSprites[SPRITES::ORTRUNE]->setTexture(GetTexture(TEXTURES::ORTRUNE));
    mSprites[SPRITES::THULRUNE]->setTexture(GetTexture(TEXTURES::THULRUNE));
    mSprites[SPRITES::AMNRUNE]->setTexture(GetTexture(TEXTURES::AMNRUNE));
    mSprites[SPRITES::SOLRUNE]->setTexture(GetTexture(TEXTURES::SOLRUNE));
    mSprites[SPRITES::SHAELRUNE]->setTexture(GetTexture(TEXTURES::SHAELRUNE));
    mSprites[SPRITES::DOLRUNE]->setTexture(GetTexture(TEXTURES::DOLRUNE));
    mSprites[SPRITES::HELRUNE]->setTexture(GetTexture(TEXTURES::HELRUNE));
    mSprites[SPRITES::IORUNE]->setTexture(GetTexture(TEXTURES::IORUNE));
    mSprites[SPRITES::LUMRUNE]->setTexture(GetTexture(TEXTURES::LUMRUNE));
    mSprites[SPRITES::KORUNE]->setTexture(GetTexture(TEXTURES::KORUNE));
    mSprites[SPRITES::FALRUNE]->setTexture(GetTexture(TEXTURES::FALRUNE));
    mSprites[SPRITES::LEMRUNE]->setTexture(GetTexture(TEXTURES::LEMRUNE));
    mSprites[SPRITES::PULRUNE]->setTexture(GetTexture(TEXTURES::PULRUNE));
    mSprites[SPRITES::UMRUNE]->setTexture(GetTexture(TEXTURES::UMRUNE));
    mSprites[SPRITES::MALRUNE]->setTexture(GetTexture(TEXTURES::MALRUNE));
    mSprites[SPRITES::ISTRUNE]->setTexture(GetTexture(TEXTURES::ISTRUNE));
    mSprites[SPRITES::GULRUNE]->setTexture(GetTexture(TEXTURES::GULRUNE));
    mSprites[SPRITES::VEXRUNE]->setTexture(GetTexture(TEXTURES::VEXRUNE));
    mSprites[SPRITES::OHMRUNE]->setTexture(GetTexture(TEXTURES::OHMRUNE));
    mSprites[SPRITES::LORUNE]->setTexture(GetTexture(TEXTURES::LORUNE));
    mSprites[SPRITES::SURRUNE]->setTexture(GetTexture(TEXTURES::SURRUNE));
    mSprites[SPRITES::BERRUNE]->setTexture(GetTexture(TEXTURES::BERRUNE));
    mSprites[SPRITES::JAHRUNE]->setTexture(GetTexture(TEXTURES::JAHRUNE));
    mSprites[SPRITES::CHAMRUNE]->setTexture(GetTexture(TEXTURES::CHAMRUNE));
    mSprites[SPRITES::ZODRUNE]->setTexture(GetTexture(TEXTURES::ZODRUNE));
    // GOLD
    mSprites[SPRITES::GOLD_SMALL]->setTexture(GetTexture(TEXTURES::GOLD_LARGE));
    mSprites[SPRITES::GOLD_MEDIUM]->setTexture(GetTexture(TEXTURES::GOLD_LARGE));
    mSprites[SPRITES::GOLD_LARGE]->setTexture(GetTexture(TEXTURES::GOLD_LARGE));
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
    mItemTexts[ITEMID::GOLD]->setString("Gold");
    mItemTexts[ITEMID::AMULET]->setString("Amulet");
    mItemTexts[ITEMID::CHARM]->setString("Small Charm");
    mItemTexts[ITEMID::REJUV]->setString("Rejuvenation Potion");
    mItemTexts[ITEMID::RING]->setString("Ring");
    mItemTexts[ITEMID::ELRUNE]->setString("El Rune");
    mItemTexts[ITEMID::ELDRUNE]->setString("Eld Rune");
    mItemTexts[ITEMID::TIRRUNE]->setString("Tir Rune");
    mItemTexts[ITEMID::NEFRUNE]->setString("Nef Rune");
    mItemTexts[ITEMID::ETHRUNE]->setString("Eth Rune");
    mItemTexts[ITEMID::ITHRUNE]->setString("Ith Rune");
    mItemTexts[ITEMID::TALRUNE]->setString("Tal Rune");
    mItemTexts[ITEMID::RALRUNE]->setString("Ral Rune");
    mItemTexts[ITEMID::ORTRUNE]->setString("Ort Rune");
    mItemTexts[ITEMID::THULRUNE]->setString("Thul Rune");
    mItemTexts[ITEMID::AMNRUNE]->setString("Amn Rune");
    mItemTexts[ITEMID::SOLRUNE]->setString("Sol Rune");
    mItemTexts[ITEMID::SHAELRUNE]->setString("Shael Rune");
    mItemTexts[ITEMID::DOLRUNE]->setString("Dol Rune");
    mItemTexts[ITEMID::HELRUNE]->setString("Hel Rune");
    mItemTexts[ITEMID::IORUNE]->setString("Io Rune");
    mItemTexts[ITEMID::LUMRUNE]->setString("Lum Rune");
    mItemTexts[ITEMID::KORUNE]->setString("Kor Rune");
    mItemTexts[ITEMID::FALRUNE]->setString("Fal Rune");
    mItemTexts[ITEMID::LEMRUNE]->setString("Lem Rune");
    mItemTexts[ITEMID::PULRUNE]->setString("Pul Rune");
    mItemTexts[ITEMID::UMRUNE]->setString("Um Rune");
    mItemTexts[ITEMID::MALRUNE]->setString("Mal Rune");
    mItemTexts[ITEMID::ISTRUNE]->setString("Ist Rune");
    mItemTexts[ITEMID::GULRUNE]->setString("Gul Rune");
    mItemTexts[ITEMID::VEXRUNE]->setString("Vex Rune");
    mItemTexts[ITEMID::OHMRUNE]->setString("Ohm Rune");
    mItemTexts[ITEMID::LORUNE]->setString("Lor Rune");
    mItemTexts[ITEMID::SURRUNE]->setString("Sur Rune");
    mItemTexts[ITEMID::BERRUNE]->setString("Ber Rune");
    mItemTexts[ITEMID::JAHRUNE]->setString("Jah Rune");
    mItemTexts[ITEMID::CHAMRUNE]->setString("Cham Rune");
    mItemTexts[ITEMID::ZODRUNE]->setString("Zod Rune");
   
        
    
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

sf::Text& AssetManager::GetTextForButtons(BUTTONS::BUTTON_TEXT text)
{
    return *mButtonTexts[text];
}

sf::Sprite& AssetManager::GetSpriteForItem(ITEMID::ITEM item)
{
    switch (item)
    {
    case ITEMID::GOLD: return *mSprites[SPRITES::GOLD_LARGE];
    case ITEMID::AMULET: return *mSprites[SPRITES::AMULET];
    case ITEMID::CHARM: return *mSprites[SPRITES::CHARM];
    case ITEMID::REJUV: return *mSprites[SPRITES::REJUV];
    case ITEMID::RING: return *mSprites[SPRITES::RING];
    case ITEMID::ELRUNE: return *mSprites[SPRITES::ELRUNE];
    case ITEMID::ELDRUNE: return *mSprites[SPRITES::ELDRUNE];
    case ITEMID::TIRRUNE: return *mSprites[SPRITES::TIRRUNE];
    case ITEMID::NEFRUNE: return *mSprites[SPRITES::NEFRUNE];
    case ITEMID::ETHRUNE: return *mSprites[SPRITES::ETHRUNE];
    case ITEMID::ITHRUNE: return *mSprites[SPRITES::ITHRUNE];
    case ITEMID::TALRUNE: return *mSprites[SPRITES::TALRUNE];
    case ITEMID::RALRUNE: return *mSprites[SPRITES::RALRUNE];
    case ITEMID::ORTRUNE: return *mSprites[SPRITES::ORTRUNE];
    case ITEMID::THULRUNE: return *mSprites[SPRITES::THULRUNE];
    case ITEMID::AMNRUNE: return *mSprites[SPRITES::AMNRUNE];
    case ITEMID::SOLRUNE: return *mSprites[SPRITES::SOLRUNE];
    case ITEMID::SHAELRUNE: return *mSprites[SPRITES::SHAELRUNE];
    case ITEMID::DOLRUNE: return *mSprites[SPRITES::DOLRUNE];
    case ITEMID::HELRUNE: return *mSprites[SPRITES::HELRUNE];
    case ITEMID::IORUNE: return *mSprites[SPRITES::IORUNE];
    case ITEMID::LUMRUNE: return *mSprites[SPRITES::LUMRUNE];
    case ITEMID::KORUNE: return *mSprites[SPRITES::KORUNE];
    case ITEMID::FALRUNE: return *mSprites[SPRITES::FALRUNE];
    case ITEMID::LEMRUNE: return *mSprites[SPRITES::LEMRUNE];
    case ITEMID::PULRUNE: return *mSprites[SPRITES::PULRUNE];
    case ITEMID::UMRUNE: return *mSprites[SPRITES::UMRUNE];
    case ITEMID::MALRUNE: return *mSprites[SPRITES::MALRUNE];
    case ITEMID::ISTRUNE: return *mSprites[SPRITES::ISTRUNE];
    case ITEMID::GULRUNE: return *mSprites[SPRITES::GULRUNE];
    case ITEMID::VEXRUNE: return *mSprites[SPRITES::VEXRUNE];
    case ITEMID::OHMRUNE: return *mSprites[SPRITES::OHMRUNE];
    case ITEMID::LORUNE: return *mSprites[SPRITES::LORUNE];
    case ITEMID::SURRUNE: return *mSprites[SPRITES::SURRUNE];
    case ITEMID::BERRUNE: return *mSprites[SPRITES::BERRUNE];
    case ITEMID::JAHRUNE: return *mSprites[SPRITES::JAHRUNE];
    case ITEMID::CHAMRUNE: return *mSprites[SPRITES::CHAMRUNE];
    case ITEMID::ZODRUNE: return *mSprites[SPRITES::ZODRUNE];
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

sf::Sprite& AssetManager::GetSpriteForButton(BUTTONS::BUTTON_TYPE button)
{
    switch (button)
    {
    case BUTTONS::WIDE: return *mSprites[SPRITES::WIDE_BUTTON];
    default: return *mSprites[SPRITES::SQUARE_BUTTON];
    }
}

sf::Sprite& AssetManager::GetSpriteForGoldQuantity(int quantity)
{
    if (quantity < 100)
    {
        return *mSprites[SPRITES::GOLD_SMALL];
    }
    else if (quantity < 500)
    {
        return *mSprites[SPRITES::GOLD_MEDIUM];
    }
    else
    {
        return *mSprites[SPRITES::GOLD_LARGE];
    }
}
