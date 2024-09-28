#include "AssetManager.h"
#include "MathUtilities.h"


AssetManager::AssetManager()
    :mTextboxColor{ sf::Color({ 0, 0, 0, 200 }) }
{
    InitializeTextureSprites();
    InitializeFontsAndTexts();
    InitializeSounds();
    InitializeMusic();
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
    mTextures[TEXTURES::MAP_FOUR]->loadFromFile("assets/graphics/map4.png");
    mTextures[TEXTURES::MAP_FIVE]->loadFromFile("assets/graphics/map5.png");
    mTextures[TEXTURES::MAP_SIX]->loadFromFile("assets/graphics/map6.png");
    mTextures[TEXTURES::MAP_SEVEN]->loadFromFile("assets/graphics/map7.png");
    mTextures[TEXTURES::MAP_EIGHT]->loadFromFile("assets/graphics/map8.png");
    mTextures[TEXTURES::MAP_NINE]->loadFromFile("assets/graphics/map9.png");
    mTextures[TEXTURES::MAP_TEN]->loadFromFile("assets/graphics/map10.png");
    // INVENTORY
    mTextures[TEXTURES::INVENTORY]->loadFromFile("assets/graphics/inventory.png");
    // PARTICLE
    mTextures[TEXTURES::PARTICLE]->loadFromFile("assets/graphics/particle.png");
    // ITEMS
    mTextures[TEXTURES::AMULET1]->loadFromFile("assets/graphics/items/amulet1.png");
    mTextures[TEXTURES::AMULET2]->loadFromFile("assets/graphics/items/amulet2.png");
    mTextures[TEXTURES::AMULET3]->loadFromFile("assets/graphics/items/amulet3.png");
    mTextures[TEXTURES::CHARM1]->loadFromFile("assets/graphics/items/charm1.png");
    mTextures[TEXTURES::CHARM2]->loadFromFile("assets/graphics/items/charm2.png");
    mTextures[TEXTURES::CHARM3]->loadFromFile("assets/graphics/items/charm3.png");
    mTextures[TEXTURES::REJUV_POTION]->loadFromFile("assets/graphics/items/rejuvenationpotion.png");
    mTextures[TEXTURES::FULL_REJUV_POTION]->loadFromFile("assets/graphics/items/fullrejuvenationpotion.png");
    mTextures[TEXTURES::ANTIDOTE]->loadFromFile("assets/graphics/items/antidote.png");
    mTextures[TEXTURES::OIL_POTION]->loadFromFile("assets/graphics/items/oilpotion.png");
    mTextures[TEXTURES::STAMINA_POTION]->loadFromFile("assets/graphics/items/staminapotion.png");
    mTextures[TEXTURES::SUPER_HEALING_POTION]->loadFromFile("assets/graphics/items/superhealingpotion.png");
    mTextures[TEXTURES::SUPER_MANA_POTION]->loadFromFile("assets/graphics/items/supermanapotion.png");
    mTextures[TEXTURES::THAWING_POTION]->loadFromFile("assets/graphics/items/thawingpotion.png");
    mTextures[TEXTURES::RANCIDGAS_POTION]->loadFromFile("assets/graphics/items/rancidgaspotion.png");

    mTextures[TEXTURES::AMETHYST_P]->loadFromFile("assets/graphics/items/perfectamethyst.png");
    mTextures[TEXTURES::DIAMOND_P]->loadFromFile("assets/graphics/items/perfectdiamond.png");
    mTextures[TEXTURES::EMERALD_P]->loadFromFile("assets/graphics/items/perfectemerald.png");
    mTextures[TEXTURES::RUBY_P]->loadFromFile("assets/graphics/items/perfectruby.png");
    mTextures[TEXTURES::SAPPHIRE_P]->loadFromFile("assets/graphics/items/perfectsapphire.png");
    mTextures[TEXTURES::TOPAZ_P]->loadFromFile("assets/graphics/items/perfecttopaz.png");
    mTextures[TEXTURES::SKULL_P]->loadFromFile("assets/graphics/items/perfectskull.png");
    mTextures[TEXTURES::RING1]->loadFromFile("assets/graphics/items/ring1.png");
    mTextures[TEXTURES::RING2]->loadFromFile("assets/graphics/items/ring2.png");
    mTextures[TEXTURES::RING3]->loadFromFile("assets/graphics/items/ring3.png");
    mTextures[TEXTURES::TPSCROLL]->loadFromFile("assets/graphics/items/scrolloftownportal.png");
    mTextures[TEXTURES::IDSCROLL]->loadFromFile("assets/graphics/items/scrollofidentify.png");
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
    mSprites[SPRITES::MAP_FOUR]->setTexture(GetTexture(TEXTURES::MAP_FOUR));
    mSprites[SPRITES::MAP_FIVE]->setTexture(GetTexture(TEXTURES::MAP_FIVE));
    mSprites[SPRITES::MAP_SIX]->setTexture(GetTexture(TEXTURES::MAP_SIX));
    mSprites[SPRITES::MAP_SEVEN]->setTexture(GetTexture(TEXTURES::MAP_SEVEN));
    mSprites[SPRITES::MAP_EIGHT]->setTexture(GetTexture(TEXTURES::MAP_EIGHT));
    mSprites[SPRITES::MAP_NINE]->setTexture(GetTexture(TEXTURES::MAP_NINE));
    mSprites[SPRITES::MAP_TEN]->setTexture(GetTexture(TEXTURES::MAP_TEN));
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
    mSprites[SPRITES::AMULET1]->setTexture(GetTexture(TEXTURES::AMULET1));
    mSprites[SPRITES::AMULET2]->setTexture(GetTexture(TEXTURES::AMULET2));
    mSprites[SPRITES::AMULET3]->setTexture(GetTexture(TEXTURES::AMULET3));
    mSprites[SPRITES::CHARM1]->setTexture(GetTexture(TEXTURES::CHARM1));
    mSprites[SPRITES::CHARM2]->setTexture(GetTexture(TEXTURES::CHARM2));
    mSprites[SPRITES::CHARM3]->setTexture(GetTexture(TEXTURES::CHARM3));
    mSprites[SPRITES::REJUV_POTION]->setTexture(GetTexture(TEXTURES::REJUV_POTION));
    mSprites[SPRITES::FULL_REJUV_POTION]->setTexture(GetTexture(TEXTURES::FULL_REJUV_POTION));
    mSprites[SPRITES::ANTIDOTE]->setTexture(GetTexture(TEXTURES::ANTIDOTE));
    mSprites[SPRITES::OIL_POTION]->setTexture(GetTexture(TEXTURES::OIL_POTION));
    mSprites[SPRITES::STAMINA_POTION]->setTexture(GetTexture(TEXTURES::STAMINA_POTION));
    mSprites[SPRITES::SUPER_HEALING_POTION]->setTexture(GetTexture(TEXTURES::SUPER_HEALING_POTION));
    mSprites[SPRITES::SUPER_MANA_POTION]->setTexture(GetTexture(TEXTURES::SUPER_MANA_POTION));
    mSprites[SPRITES::THAWING_POTION]->setTexture(GetTexture(TEXTURES::THAWING_POTION));
    mSprites[SPRITES::RANCIDGAS_POTION]->setTexture(GetTexture(TEXTURES::RANCIDGAS_POTION));
    mSprites[SPRITES::AMETHYST_P]->setTexture(GetTexture(TEXTURES::AMETHYST_P));
    mSprites[SPRITES::DIAMOND_P]->setTexture(GetTexture(TEXTURES::DIAMOND_P));
    mSprites[SPRITES::EMERALD_P]->setTexture(GetTexture(TEXTURES::EMERALD_P));
    mSprites[SPRITES::RUBY_P]->setTexture(GetTexture(TEXTURES::RUBY_P));
    mSprites[SPRITES::SAPPHIRE_P]->setTexture(GetTexture(TEXTURES::SAPPHIRE_P));
    mSprites[SPRITES::TOPAZ_P]->setTexture(GetTexture(TEXTURES::TOPAZ_P));
    mSprites[SPRITES::SKULL_P]->setTexture(GetTexture(TEXTURES::SKULL_P));
    mSprites[SPRITES::RING1]->setTexture(GetTexture(TEXTURES::RING1));
    mSprites[SPRITES::RING2]->setTexture(GetTexture(TEXTURES::RING2));
    mSprites[SPRITES::RING3]->setTexture(GetTexture(TEXTURES::RING3));
    mSprites[SPRITES::TPSCROLL]->setTexture(GetTexture(TEXTURES::TPSCROLL));
    mSprites[SPRITES::IDSCROLL]->setTexture(GetTexture(TEXTURES::IDSCROLL));
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

    mButtonTexts[BUTTONS::START]->setString("New Game");
    mButtonTexts[BUTTONS::LOAD_GAME]->setString("Continue Game");
    mButtonTexts[BUTTONS::EXIT]->setString("Exit Game");
    mButtonTexts[BUTTONS::NEXT_LEVEL]->setString("Next Level");
    mButtonTexts[BUTTONS::OPEN_INVENTORY]->setString("Inventory");
    mButtonTexts[BUTTONS::EXIT_PLAY]->setString("Main Menu");

    // Set Up Texts
    mItemTexts[ITEMID::GOLD]->setString("Gold");
    mItemTexts[ITEMID::AMULET1]->setString("Amulet");
    mItemTexts[ITEMID::AMULET2]->setString("Water Amulet");
    mItemTexts[ITEMID::AMULET3]->setString("Fire Amulet");
    mItemTexts[ITEMID::CHARM1]->setString("Small Charm");
    mItemTexts[ITEMID::CHARM2]->setString("Large Charm");
    mItemTexts[ITEMID::CHARM3]->setString("Grand Charm");

    mItemTexts[ITEMID::REJUV_POTION]->setString("Rejuvenation Potion");
    mItemTexts[ITEMID::FULL_REJUV_POTION]->setString("Full Rejuvenation Potion");
    mItemTexts[ITEMID::ANTIDOTE]->setString("Antidote");
    mItemTexts[ITEMID::OIL_POTION]->setString("Oil Potion");
    mItemTexts[ITEMID::STAMINA_POTION]->setString("Stamina Potion");
    mItemTexts[ITEMID::SUPER_HEALING_POTION]->setString("Super Healing Potion");
    mItemTexts[ITEMID::SUPER_MANA_POTION]->setString("Super Mana Potion");
    mItemTexts[ITEMID::THAWING_POTION]->setString("Thawing Potion");
    mItemTexts[ITEMID::RANCIDGAS_POTION]->setString("Rancid Gas Potion");

    mItemTexts[ITEMID::AMETHYST_P]->setString("Perfect Amethyst");
    mItemTexts[ITEMID::DIAMOND_P]->setString("Perfect Diamond");
    mItemTexts[ITEMID::EMERALD_P]->setString("Perfect Emerald");
    mItemTexts[ITEMID::RUBY_P]->setString("Perfect Ruby");
    mItemTexts[ITEMID::SAPPHIRE_P]->setString("Perfect Sapphire");
    mItemTexts[ITEMID::TOPAZ_P]->setString("Perfect Topaz");
    mItemTexts[ITEMID::SKULL_P]->setString("Perfect Skull");
    mItemTexts[ITEMID::RING1]->setString("Ring");
    mItemTexts[ITEMID::RING2]->setString("Ring of Water");
    mItemTexts[ITEMID::RING3]->setString("Ring of Chloranthy");
    mItemTexts[ITEMID::TPSCROLL]->setString("Scroll of Town Portal");
    mItemTexts[ITEMID::IDSCROLL]->setString("Scroll of Identification");
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
    mItemTexts[ITEMID::LORUNE]->setString("Lo Rune");
    mItemTexts[ITEMID::SURRUNE]->setString("Sur Rune");
    mItemTexts[ITEMID::BERRUNE]->setString("Ber Rune");
    mItemTexts[ITEMID::JAHRUNE]->setString("Jah Rune");
    mItemTexts[ITEMID::CHAMRUNE]->setString("Cham Rune");
    mItemTexts[ITEMID::ZODRUNE]->setString("Zod Rune");

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

void AssetManager::InitializeSounds()
{
    for (int i{ 0 }; i < SOUNDBUFFERS::MAX_SOUNDSBUFFERS; i++)
    {
        mSoundBuffers.push_back(std::make_unique<sf::SoundBuffer>());
    }
    assert(std::ssize(mSoundBuffers) == SOUNDBUFFERS::MAX_SOUNDSBUFFERS && "AssetManager failed to initialize correct number of soundbuffers\n");

    for (int i{ 0 }; i < PLAYSOUND::MAX_SOUNDS; i++)
    {
        mSounds.push_back(std::make_unique<sf::Sound>());

    }
    assert(std::ssize(mSounds) == PLAYSOUND::MAX_SOUNDS && "AssetManager failed to initialize correct number of sounds\n");

    // Load Soundbuffers
    mSoundBuffers[SOUNDBUFFERS::BUTTON_DOWN_SB]->loadFromFile("assets/audio/SFX/buttondown.wav");
    mSoundBuffers[SOUNDBUFFERS::CHEST_OPEN_SB]->loadFromFile("assets/audio/SFX/chestopen.wav");

    // Set Sound
    mSounds[PLAYSOUND::BUTTON_DOWN]->setBuffer(GetSoundBuffer(SOUNDBUFFERS::BUTTON_DOWN_SB));
    mSounds[PLAYSOUND::OPEN_CHEST]->setBuffer(GetSoundBuffer(SOUNDBUFFERS::CHEST_OPEN_SB));

    // Volume Setter
    mSounds[PLAYSOUND::OPEN_CHEST]->setVolume(100.f); // <--- Example

}

void AssetManager::InitializeMusic()
{
    for (int i{ 0 }; i < MUSIC::MAX_MUSIC_FILES; i++)
    {
        mMusic.push_back(std::make_unique<sf::Music>());
    }
    assert(std::ssize(mMusic) == MUSIC::MAX_MUSIC_FILES && "AssetManager failed to initialize correct number of music files\n");

    mMusic[MUSIC::INTRO]->openFromFile("assets/audio/music/intro.wav");
    mMusic[MUSIC::TRISTRAM]->openFromFile("assets/audio/music/Tristram.wav");
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

sf::SoundBuffer& AssetManager::GetSoundBuffer(SOUNDBUFFERS::SOUNDBUFFER soundbuffer)
{
    assert(soundbuffer < SOUNDBUFFERS::MAX_SOUNDSBUFFERS && soundbuffer >= 0 && "Attempted to get soundbuffer that doesn't exist!\n");
    return *mSoundBuffers[soundbuffer];
}

sf::Sound& AssetManager::GetSound(PLAYSOUND::PLAYSOUND sound)
{
    assert(sound < PLAYSOUND::MAX_SOUNDS && sound >= 0 && "Attempted to get sound that doesn't exist!\n");
    return *mSounds[sound];
}

sf::Music& AssetManager::GetMusic(MUSIC::PLAYMUSIC music)
{
    assert(music < MUSIC::MAX_MUSIC_FILES && music >= 0 && "Attempted to get music that doesn't exist!\n");
    return *mMusic[music];
}

sf::Sprite& AssetManager::GetLevelMap(LEVELS::LEVEL level)
{
    switch (level)
    {
    case LEVELS::LEVEL_ONE: return *mSprites[SPRITES::MAP_ONE];
    case LEVELS::LEVEL_TWO: return *mSprites[SPRITES::MAP_TWO];
    case LEVELS::LEVEL_THREE: return *mSprites[SPRITES::MAP_THREE];
    case LEVELS::LEVEL_FOUR: return *mSprites[SPRITES::MAP_FOUR];
    case LEVELS::LEVEL_FIVE: return *mSprites[SPRITES::MAP_FIVE];
    case LEVELS::LEVEL_SIX: return *mSprites[SPRITES::MAP_SIX];
    case LEVELS::LEVEL_SEVEN: return *mSprites[SPRITES::MAP_SEVEN];
    case LEVELS::LEVEL_EIGHT: return *mSprites[SPRITES::MAP_EIGHT];
    case LEVELS::LEVEL_NINE: return *mSprites[SPRITES::MAP_NINE];
    case LEVELS::LEVEL_TEN: return *mSprites[SPRITES::MAP_TEN];
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
    case ITEMID::AMULET1: return *mSprites[SPRITES::AMULET1];
    case ITEMID::AMULET2: return *mSprites[SPRITES::AMULET2];
    case ITEMID::AMULET3: return *mSprites[SPRITES::AMULET3];
    case ITEMID::CHARM1: return *mSprites[SPRITES::CHARM1];
    case ITEMID::CHARM2: return *mSprites[SPRITES::CHARM2];
    case ITEMID::CHARM3: return *mSprites[SPRITES::CHARM3];
    case ITEMID::REJUV_POTION: return *mSprites[SPRITES::REJUV_POTION];
    case ITEMID::FULL_REJUV_POTION: return *mSprites[SPRITES::FULL_REJUV_POTION];
    case ITEMID::ANTIDOTE: return *mSprites[SPRITES::ANTIDOTE];
    case ITEMID::OIL_POTION: return *mSprites[SPRITES::OIL_POTION];
    case ITEMID::STAMINA_POTION: return *mSprites[SPRITES::STAMINA_POTION];
    case ITEMID::SUPER_HEALING_POTION: return *mSprites[SPRITES::SUPER_HEALING_POTION];
    case ITEMID::SUPER_MANA_POTION: return *mSprites[SPRITES::SUPER_MANA_POTION];
    case ITEMID::THAWING_POTION: return *mSprites[SPRITES::THAWING_POTION];
    case ITEMID::RANCIDGAS_POTION: return *mSprites[SPRITES::RANCIDGAS_POTION];
    case ITEMID::AMETHYST_P: return *mSprites[SPRITES::AMETHYST_P];
    case ITEMID::DIAMOND_P: return *mSprites[SPRITES::DIAMOND_P];
    case ITEMID::EMERALD_P: return *mSprites[SPRITES::EMERALD_P];
    case ITEMID::RUBY_P: return *mSprites[SPRITES::RUBY_P];
    case ITEMID::SAPPHIRE_P: return *mSprites[SPRITES::SAPPHIRE_P];
    case ITEMID::TOPAZ_P: return *mSprites[SPRITES::TOPAZ_P];
    case ITEMID::SKULL_P: return *mSprites[SPRITES::SKULL_P];
    case ITEMID::RING1: return *mSprites[SPRITES::RING1];
    case ITEMID::RING2: return *mSprites[SPRITES::RING2];
    case ITEMID::RING3: return *mSprites[SPRITES::RING3];
    case ITEMID::TPSCROLL: return *mSprites[SPRITES::TPSCROLL];
    case ITEMID::IDSCROLL: return *mSprites[SPRITES::IDSCROLL];
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
    default: return *mSprites[SPRITES::TPSCROLL];
    }
}

sf::Color AssetManager::GetColorForRarity(ITEMRARITY::RARITY rarity)
{
    switch (rarity)
    {
    case ITEMRARITY::NORMAL:	return sf::Color::White;
    case ITEMRARITY::MAGIC:		return sf::Color{  51, 102, 255 };	break;
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
