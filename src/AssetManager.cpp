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
    mTextures[TEXTURES::WINSCREEN]->loadFromFile("assets/graphics/winscreen.png");
    // BUTTON TEXTURES
    mTextures[TEXTURES::WIDE_BUTTON]->loadFromFile("assets/graphics/button.png");
    mTextures[TEXTURES::INVENTORY_BUTTON]->loadFromFile("assets/graphics/inventorybutton.png");
    mTextures[TEXTURES::MUTE_BUTTON]->loadFromFile("assets/graphics/mutebutton.png");
    mTextures[TEXTURES::UPGRADE_BUTTON]->loadFromFile("assets/graphics/upgradebutton.png");
    mTextures[TEXTURES::SORT_BUTTON]->loadFromFile("assets/graphics/sortbutton.png");
    mTextures[TEXTURES::CLOSE_BUTTON]->loadFromFile("assets/graphics/closebutton.png");
    mTextures[TEXTURES::MINI_BUTTON]->loadFromFile("assets/graphics/minibutton.png");
    mTextures[TEXTURES::CHESTCLOSED]->loadFromFile("assets/graphics/chestclosed.png");
    mTextures[TEXTURES::CHESTOPENED]->loadFromFile("assets/graphics/chestopened.png");
    // MAPS
    mTextures[TEXTURES::MAP_ONE]->loadFromFile("assets/graphics/levels/level1.png");
    mTextures[TEXTURES::MAP_TWO]->loadFromFile("assets/graphics/levels/level2.png");
    mTextures[TEXTURES::MAP_THREE]->loadFromFile("assets/graphics/levels/level3.png");
    mTextures[TEXTURES::MAP_FOUR]->loadFromFile("assets/graphics/levels/level4.png");
    mTextures[TEXTURES::MAP_FIVE]->loadFromFile("assets/graphics/levels/level5.png");
    mTextures[TEXTURES::MAP_SIX]->loadFromFile("assets/graphics/levels/level6.png");
    mTextures[TEXTURES::MAP_SEVEN]->loadFromFile("assets/graphics/levels/level7.png");
    mTextures[TEXTURES::MAP_EIGHT]->loadFromFile("assets/graphics/levels/level8.png");
    mTextures[TEXTURES::MAP_NINE]->loadFromFile("assets/graphics/levels/level9.png");
    mTextures[TEXTURES::MAP_TEN]->loadFromFile("assets/graphics/levels/level10.png");
    mTextures[TEXTURES::MAP_ELEVEN]->loadFromFile("assets/graphics/levels/level11.png");
    mTextures[TEXTURES::MAP_TWELVE]->loadFromFile("assets/graphics/levels/level12.png");
    mTextures[TEXTURES::MAP_THIRTEEN]->loadFromFile("assets/graphics/levels/level13.png");
    // INVENTORY
    mTextures[TEXTURES::INVENTORY]->loadFromFile("assets/graphics/inventory.png");
    // ITEMS
    mTextures[TEXTURES::KEY]->loadFromFile("assets/graphics/items/key.png");
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
    mTextures[TEXTURES::AMETHYST_F]->loadFromFile("assets/graphics/items/flawlessamethyst.png");
    mTextures[TEXTURES::DIAMOND_P]->loadFromFile("assets/graphics/items/perfectdiamond.png");
    mTextures[TEXTURES::DIAMOND_F]->loadFromFile("assets/graphics/items/flawlessdiamond.png");
    mTextures[TEXTURES::EMERALD_P]->loadFromFile("assets/graphics/items/perfectemerald.png");
    mTextures[TEXTURES::EMERALD_F]->loadFromFile("assets/graphics/items/flawlessemerald.png");
    mTextures[TEXTURES::RUBY_P]->loadFromFile("assets/graphics/items/perfectruby.png");
    mTextures[TEXTURES::RUBY_F]->loadFromFile("assets/graphics/items/flawlessruby.png");
    mTextures[TEXTURES::SAPPHIRE_P]->loadFromFile("assets/graphics/items/perfectsapphire.png");
    mTextures[TEXTURES::SAPPHIRE_F]->loadFromFile("assets/graphics/items/flawlesssapphire.png");
    mTextures[TEXTURES::TOPAZ_P]->loadFromFile("assets/graphics/items/perfecttopaz.png");
    mTextures[TEXTURES::TOPAZ_F]->loadFromFile("assets/graphics/items/flawlesstopaz.png");
    mTextures[TEXTURES::SKULL_P]->loadFromFile("assets/graphics/items/perfectskull.png");
    mTextures[TEXTURES::SKULL_F]->loadFromFile("assets/graphics/items/flawlessskull.png");
    mTextures[TEXTURES::JEWEL_1]->loadFromFile("assets/graphics/items/jewel1.png");
    mTextures[TEXTURES::JEWEL_2]->loadFromFile("assets/graphics/items/jewel2.png");
    mTextures[TEXTURES::JEWEL_3]->loadFromFile("assets/graphics/items/jewel3.png");
    mTextures[TEXTURES::JEWEL_4]->loadFromFile("assets/graphics/items/jewel4.png");
    mTextures[TEXTURES::JEWEL_5]->loadFromFile("assets/graphics/items/jewel5.png");
    mTextures[TEXTURES::JEWEL_6]->loadFromFile("assets/graphics/items/jewel6.png");
    mTextures[TEXTURES::RING1]->loadFromFile("assets/graphics/items/ring1.png");
    mTextures[TEXTURES::RING2]->loadFromFile("assets/graphics/items/ring2.png");
    mTextures[TEXTURES::RING3]->loadFromFile("assets/graphics/items/ring3.png");
    mTextures[TEXTURES::TPSCROLL]->loadFromFile("assets/graphics/items/scrolloftownportal.png");
    mTextures[TEXTURES::IDSCROLL]->loadFromFile("assets/graphics/items/scrollofidentify.png");
    mTextures[TEXTURES::ANNIHILUS]->loadFromFile("assets/graphics/items/annihilus.png");
    mTextures[TEXTURES::WORLDSTONE_SHARD]->loadFromFile("assets/graphics/items/worldstoneshard.png");
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
    mSprites[SPRITES::WINSCREEN]->setTexture(GetTexture(TEXTURES::WINSCREEN));
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
    mSprites[SPRITES::MAP_ELEVEN]->setTexture(GetTexture(TEXTURES::MAP_ELEVEN));
    mSprites[SPRITES::MAP_TWELVE]->setTexture(GetTexture(TEXTURES::MAP_TWELVE));
    mSprites[SPRITES::MAP_THIRTEEN]->setTexture(GetTexture(TEXTURES::MAP_THIRTEEN));
    // BUTTONS
    mSprites[SPRITES::WIDE_BUTTON]->setTexture(GetTexture(TEXTURES::WIDE_BUTTON));
    mSprites[SPRITES::INVENTORY_BUTTON]->setTexture(GetTexture(TEXTURES::INVENTORY_BUTTON));
    mSprites[SPRITES::MUTE_BUTTON]->setTexture(GetTexture(TEXTURES::MUTE_BUTTON));
    mSprites[SPRITES::UPGRADE_BUTTON]->setTexture(GetTexture(TEXTURES::UPGRADE_BUTTON));
    mSprites[SPRITES::SORT_BUTTON]->setTexture(GetTexture(TEXTURES::SORT_BUTTON));
    mSprites[SPRITES::CLOSE_BUTTON]->setTexture(GetTexture(TEXTURES::CLOSE_BUTTON));
    mSprites[SPRITES::MINI_BUTTON]->setTexture(GetTexture(TEXTURES::MINI_BUTTON));
    // INVENTORY
    mSprites[SPRITES::INVENTORY]->setTexture(GetTexture(TEXTURES::INVENTORY));
    // CHESTS
    mSprites[SPRITES::CHESTCLOSED]->setTexture(GetTexture(TEXTURES::CHESTCLOSED));
    mSprites[SPRITES::CHESTOPENED]->setTexture(GetTexture(TEXTURES::CHESTOPENED));
    // ITEMS
    mSprites[SPRITES::KEY]->setTexture(GetTexture(TEXTURES::KEY));
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
    mSprites[SPRITES::AMETHYST_F]->setTexture(GetTexture(TEXTURES::AMETHYST_F));
    mSprites[SPRITES::DIAMOND_P]->setTexture(GetTexture(TEXTURES::DIAMOND_P));
    mSprites[SPRITES::DIAMOND_F]->setTexture(GetTexture(TEXTURES::DIAMOND_F));
    mSprites[SPRITES::EMERALD_P]->setTexture(GetTexture(TEXTURES::EMERALD_P));
    mSprites[SPRITES::EMERALD_F]->setTexture(GetTexture(TEXTURES::EMERALD_F));
    mSprites[SPRITES::RUBY_P]->setTexture(GetTexture(TEXTURES::RUBY_P));
    mSprites[SPRITES::RUBY_F]->setTexture(GetTexture(TEXTURES::RUBY_F));
    mSprites[SPRITES::SAPPHIRE_P]->setTexture(GetTexture(TEXTURES::SAPPHIRE_P));
    mSprites[SPRITES::SAPPHIRE_F]->setTexture(GetTexture(TEXTURES::SAPPHIRE_F));
    mSprites[SPRITES::TOPAZ_P]->setTexture(GetTexture(TEXTURES::TOPAZ_P));
    mSprites[SPRITES::TOPAZ_F]->setTexture(GetTexture(TEXTURES::TOPAZ_F));
    mSprites[SPRITES::SKULL_P]->setTexture(GetTexture(TEXTURES::SKULL_P));
    mSprites[SPRITES::SKULL_F]->setTexture(GetTexture(TEXTURES::SKULL_F));
    mSprites[SPRITES::JEWEL_1]->setTexture(GetTexture(TEXTURES::JEWEL_1));
    mSprites[SPRITES::JEWEL_2]->setTexture(GetTexture(TEXTURES::JEWEL_2));
    mSprites[SPRITES::JEWEL_3]->setTexture(GetTexture(TEXTURES::JEWEL_3));
    mSprites[SPRITES::JEWEL_4]->setTexture(GetTexture(TEXTURES::JEWEL_4));
    mSprites[SPRITES::JEWEL_5]->setTexture(GetTexture(TEXTURES::JEWEL_5));
    mSprites[SPRITES::JEWEL_6]->setTexture(GetTexture(TEXTURES::JEWEL_6));
    mSprites[SPRITES::RING1]->setTexture(GetTexture(TEXTURES::RING1));
    mSprites[SPRITES::RING2]->setTexture(GetTexture(TEXTURES::RING2));
    mSprites[SPRITES::RING3]->setTexture(GetTexture(TEXTURES::RING3));
    mSprites[SPRITES::TPSCROLL]->setTexture(GetTexture(TEXTURES::TPSCROLL));
    mSprites[SPRITES::IDSCROLL]->setTexture(GetTexture(TEXTURES::IDSCROLL));
    mSprites[SPRITES::ANNIHILUS]->setTexture(GetTexture(TEXTURES::ANNIHILUS));
    mSprites[SPRITES::WORLDSTONE_SHARD]->setTexture(GetTexture(TEXTURES::WORLDSTONE_SHARD));
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
    mButtonTexts[BUTTONS::NEW_GAME]->setString("New Game");
    mButtonTexts[BUTTONS::LOAD_GAME]->setString("Continue");
    mButtonTexts[BUTTONS::EXIT]->setString("Exit Game");
    mButtonTexts[BUTTONS::NEXT_LEVEL]->setString("Next Level");
    mButtonTexts[BUTTONS::OPEN_INVENTORY]->setString("Inventory");
    mButtonTexts[BUTTONS::EXIT_PLAY]->setString("Main Menu");

    // Set Up Texts
    mItemTexts[ITEMID::GOLD]->setString("Gold");
    mItemTexts[ITEMID::AMULET1]->setString("Amulet");
    mItemTexts[ITEMID::KEY]->setString("Key");
    mItemTexts[ITEMID::AMULET2]->setString("Water Amulet");
    mItemTexts[ITEMID::AMULET3]->setString("Fire Amulet");
    mItemTexts[ITEMID::CHARM1]->setString("Small Charm of Dexterity");
    mItemTexts[ITEMID::CHARM2]->setString("Small Charm of Luck");
    mItemTexts[ITEMID::CHARM3]->setString("Small Charm of Strength");

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
    mItemTexts[ITEMID::AMETHYST_F]->setString("Flawless Amethyst");
    mItemTexts[ITEMID::DIAMOND_P]->setString("Perfect Diamond");
    mItemTexts[ITEMID::DIAMOND_F]->setString("Flawless Diamond");
    mItemTexts[ITEMID::EMERALD_P]->setString("Perfect Emerald");
    mItemTexts[ITEMID::EMERALD_F]->setString("Flawless Emerald");
    mItemTexts[ITEMID::RUBY_P]->setString("Perfect Ruby");
    mItemTexts[ITEMID::RUBY_F]->setString("Flawless Ruby");
    mItemTexts[ITEMID::SAPPHIRE_P]->setString("Perfect Sapphire");
    mItemTexts[ITEMID::SAPPHIRE_F]->setString("Flawless Sapphire");
    mItemTexts[ITEMID::TOPAZ_P]->setString("Perfect Topaz");
    mItemTexts[ITEMID::TOPAZ_F]->setString("Flawless Topaz");
    mItemTexts[ITEMID::SKULL_P]->setString("Perfect Skull");
    mItemTexts[ITEMID::SKULL_F]->setString("Flawless Skull");
    mItemTexts[ITEMID::JEWEL_1]->setString("Diamond Jewel");
    mItemTexts[ITEMID::JEWEL_2]->setString("Ruby Jewel");
    mItemTexts[ITEMID::JEWEL_3]->setString("Emerald Jewel");
    mItemTexts[ITEMID::JEWEL_4]->setString("Opal Jewel");
    mItemTexts[ITEMID::JEWEL_5]->setString("Sapphire Jewel");
    mItemTexts[ITEMID::JEWEL_6]->setString("Amethyst Jewel");
    mItemTexts[ITEMID::RING1]->setString("Ring");
    mItemTexts[ITEMID::RING2]->setString("Ring of Water");
    mItemTexts[ITEMID::RING3]->setString("Ring of Chloranthy");
    mItemTexts[ITEMID::TPSCROLL]->setString("Scroll of Town Portal");
    mItemTexts[ITEMID::IDSCROLL]->setString("Scroll of Identification");
    mItemTexts[ITEMID::ANNIHILUS]->setString("Annihilus");
    mItemTexts[ITEMID::WORLDSTONE_SHARD]->setString("Worldstone Shard");
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
    mItemTexts[ITEMID::KORUNE]->setString("Ko Rune");
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
        itemText->setCharacterSize(FONTS::CHARACTER_SIZE_NORMAL);
    }
    for (auto& button : mButtonTexts)
    {
        button->setFont(*mFonts[FONTS::BOLD]);
        button->setFillColor(sf::Color::Black);
        button->setCharacterSize(FONTS::CHARACTER_SIZE_BUTTONS);
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
    mSoundBuffers[SOUNDBUFFERS::ITEM_PICKUP_SB]->loadFromFile("assets/audio/SFX/itempickup.wav");
    mSoundBuffers[SOUNDBUFFERS::ITEM_FLIP_SB]->loadFromFile("assets/audio/SFX/inventoryfull.wav");
    mSoundBuffers[SOUNDBUFFERS::AMULET_DROP_SB]->loadFromFile("assets/audio/SFX/amuletdrop.wav");
    mSoundBuffers[SOUNDBUFFERS::CHARM_DROP_SB]->loadFromFile("assets/audio/SFX/charmdrop.wav");
    mSoundBuffers[SOUNDBUFFERS::GEM_DROP_SB]->loadFromFile("assets/audio/SFX/gemdrop.wav");
    mSoundBuffers[SOUNDBUFFERS::SKULL_DROP_SB]->loadFromFile("assets/audio/SFX/skulldrop.wav");
    mSoundBuffers[SOUNDBUFFERS::GOLD_DROP_SB]->loadFromFile("assets/audio/SFX/golddrop.wav");
    mSoundBuffers[SOUNDBUFFERS::JEWEL_DROP_SB]->loadFromFile("assets/audio/SFX/jeweldrop.wav");
    mSoundBuffers[SOUNDBUFFERS::KEY_DROP_SB]->loadFromFile("assets/audio/SFX/keydrop.wav");
    mSoundBuffers[SOUNDBUFFERS::RING_DROP_SB]->loadFromFile("assets/audio/SFX/ringdrop.wav");
    mSoundBuffers[SOUNDBUFFERS::RUNE_DROP_SB]->loadFromFile("assets/audio/SFX/runedrop.wav");
    mSoundBuffers[SOUNDBUFFERS::SCROLL_DROP_SB]->loadFromFile("assets/audio/SFX/scrolldrop.wav");

    // Set Sound
    mSounds[PLAYSOUND::BUTTON_DOWN]->setBuffer(GetSoundBuffer(SOUNDBUFFERS::BUTTON_DOWN_SB));
    mSounds[PLAYSOUND::OPEN_CHEST]->setBuffer(GetSoundBuffer(SOUNDBUFFERS::CHEST_OPEN_SB));
    mSounds[PLAYSOUND::ITEM_PICKUP]->setBuffer(GetSoundBuffer(SOUNDBUFFERS::ITEM_PICKUP_SB));
    mSounds[PLAYSOUND::ITEM_FLIP]->setBuffer(GetSoundBuffer(SOUNDBUFFERS::ITEM_FLIP_SB));
    mSounds[PLAYSOUND::AMULET_DROP]->setBuffer(GetSoundBuffer(SOUNDBUFFERS::AMULET_DROP_SB));
    mSounds[PLAYSOUND::CHARM_DROP]->setBuffer(GetSoundBuffer(SOUNDBUFFERS::CHARM_DROP_SB));
    mSounds[PLAYSOUND::GEM_DROP]->setBuffer(GetSoundBuffer(SOUNDBUFFERS::GEM_DROP_SB));
    mSounds[PLAYSOUND::SKULL_DROP]->setBuffer(GetSoundBuffer(SOUNDBUFFERS::SKULL_DROP_SB));
    mSounds[PLAYSOUND::GOLD_DROP]->setBuffer(GetSoundBuffer(SOUNDBUFFERS::GOLD_DROP_SB));
    mSounds[PLAYSOUND::JEWEL_DROP]->setBuffer(GetSoundBuffer(SOUNDBUFFERS::JEWEL_DROP_SB));
    mSounds[PLAYSOUND::KEY_DROP]->setBuffer(GetSoundBuffer(SOUNDBUFFERS::KEY_DROP_SB));
    mSounds[PLAYSOUND::RING_DROP]->setBuffer(GetSoundBuffer(SOUNDBUFFERS::RING_DROP_SB));
    mSounds[PLAYSOUND::RUNE_DROP]->setBuffer(GetSoundBuffer(SOUNDBUFFERS::RUNE_DROP_SB));
    mSounds[PLAYSOUND::SCROLL_DROP]->setBuffer(GetSoundBuffer(SOUNDBUFFERS::SCROLL_DROP_SB));


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
    mMusic[MUSIC::CRYPT]->openFromFile("assets/audio/music/Crypt.wav");
    mMusic[MUSIC::DIABLO]->openFromFile("assets/audio/music/Diablo.wav");
    mMusic[MUSIC::KURAST]->openFromFile("assets/audio/music/Kurast.wav");
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
    case LEVELS::LEVEL_ONE:         return *mSprites[SPRITES::MAP_ONE];
    case LEVELS::LEVEL_TWO:         return *mSprites[SPRITES::MAP_TWO];
    case LEVELS::LEVEL_THREE:       return *mSprites[SPRITES::MAP_THREE];
    case LEVELS::LEVEL_FOUR:        return *mSprites[SPRITES::MAP_FOUR];
    case LEVELS::LEVEL_FIVE:        return *mSprites[SPRITES::MAP_FIVE];
    case LEVELS::LEVEL_SIX:         return *mSprites[SPRITES::MAP_SIX];
    case LEVELS::LEVEL_SEVEN:       return *mSprites[SPRITES::MAP_SEVEN];
    case LEVELS::LEVEL_EIGHT:       return *mSprites[SPRITES::MAP_EIGHT];
    case LEVELS::LEVEL_NINE:        return *mSprites[SPRITES::MAP_NINE];
    case LEVELS::LEVEL_TEN:         return *mSprites[SPRITES::MAP_TEN];
    case LEVELS::LEVEL_ELEVEN:      return *mSprites[SPRITES::MAP_ELEVEN];
    case LEVELS::LEVEL_TWELVE:      return *mSprites[SPRITES::MAP_TWELVE];
    case LEVELS::LEVEL_THIRTEEN:    return *mSprites[SPRITES::MAP_THIRTEEN];
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
    case ITEMID::KEY: return *mSprites[SPRITES::KEY];
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
    case ITEMID::AMETHYST_F: return *mSprites[SPRITES::AMETHYST_F];
    case ITEMID::DIAMOND_P: return *mSprites[SPRITES::DIAMOND_P];
    case ITEMID::DIAMOND_F: return *mSprites[SPRITES::DIAMOND_F];
    case ITEMID::EMERALD_P: return *mSprites[SPRITES::EMERALD_P];
    case ITEMID::EMERALD_F: return *mSprites[SPRITES::EMERALD_F];
    case ITEMID::RUBY_P: return *mSprites[SPRITES::RUBY_P];
    case ITEMID::RUBY_F: return *mSprites[SPRITES::RUBY_F];
    case ITEMID::SAPPHIRE_P: return *mSprites[SPRITES::SAPPHIRE_P];
    case ITEMID::SAPPHIRE_F: return *mSprites[SPRITES::SAPPHIRE_F];
    case ITEMID::TOPAZ_P: return *mSprites[SPRITES::TOPAZ_P];
    case ITEMID::TOPAZ_F: return *mSprites[SPRITES::TOPAZ_F];
    case ITEMID::SKULL_P: return *mSprites[SPRITES::SKULL_P];
    case ITEMID::SKULL_F: return *mSprites[SPRITES::SKULL_F];
    case ITEMID::JEWEL_1: return *mSprites[SPRITES::JEWEL_1];
    case ITEMID::JEWEL_2: return *mSprites[SPRITES::JEWEL_2];
    case ITEMID::JEWEL_3: return *mSprites[SPRITES::JEWEL_3];
    case ITEMID::JEWEL_4: return *mSprites[SPRITES::JEWEL_4];
    case ITEMID::JEWEL_5: return *mSprites[SPRITES::JEWEL_5];
    case ITEMID::JEWEL_6: return *mSprites[SPRITES::JEWEL_6];
    case ITEMID::RING1: return *mSprites[SPRITES::RING1];
    case ITEMID::RING2: return *mSprites[SPRITES::RING2];
    case ITEMID::RING3: return *mSprites[SPRITES::RING3];
    case ITEMID::TPSCROLL: return *mSprites[SPRITES::TPSCROLL];
    case ITEMID::IDSCROLL: return *mSprites[SPRITES::IDSCROLL];
    case ITEMID::ANNIHILUS: return *mSprites[SPRITES::ANNIHILUS];
    case ITEMID::WORLDSTONE_SHARD: return *mSprites[SPRITES::WORLDSTONE_SHARD];
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

sf::Color AssetManager::GetColorForItemText(std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> item)
{
    switch (item.first)
    {
    case ITEMID::WORLDSTONE_SHARD:  return sf::Color::Red;
    case ITEMID::AMETHYST_F:        return sf::Color{ 153, 102, 51 };   break;
    case ITEMID::AMETHYST_P:        return sf::Color{ 153, 102, 51 };   break;
    case ITEMID::DIAMOND_P:         return sf::Color{ 153, 102, 51 };   break;
    case ITEMID::DIAMOND_F:         return sf::Color{ 153, 102, 51 };   break;
    case ITEMID::EMERALD_P:         return sf::Color{ 153, 102, 51 };   break;
    case ITEMID::EMERALD_F:         return sf::Color{ 153, 102, 51 };   break;
    case ITEMID::RUBY_P:            return sf::Color{ 153, 102, 51 };   break;
    case ITEMID::RUBY_F:            return sf::Color{ 153, 102, 51 };   break;  
    case ITEMID::SAPPHIRE_P:        return sf::Color{ 153, 102, 51 };   break;
    case ITEMID::SAPPHIRE_F:        return sf::Color{ 153, 102, 51 };   break;
    case ITEMID::TOPAZ_P:           return sf::Color{ 153, 102, 51 };   break;
    case ITEMID::TOPAZ_F:           return sf::Color{ 153, 102, 51 };   break;
    default: break;
    }
    switch (item.second)
    {
    case ITEMRARITY::NORMAL:	    return sf::Color::White;
    case ITEMRARITY::MAGIC:		    return sf::Color{  51, 102, 255 };	break;
    case ITEMRARITY::RARE:		    return sf::Color{ 253, 216, 53 };	break;
    case ITEMRARITY::SET:		    return sf::Color{ 44 , 190, 52 };	break;
    case ITEMRARITY::UNIQUE:	    return sf::Color{ 153, 102, 51 };	break;
    case ITEMRARITY::RUNE:		    return sf::Color{ 198, 140, 89 };	break;
    default:					    return sf::Color::White;			break;
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
    case BUTTONS::MUTE: return *mSprites[SPRITES::MUTE_BUTTON];
    case BUTTONS::UPGRADE: return *mSprites[SPRITES::UPGRADE_BUTTON];
    case BUTTONS::SORT: return *mSprites[SPRITES::SORT_BUTTON];
    case BUTTONS::CLOSE: return *mSprites[SPRITES::CLOSE_BUTTON];
    case BUTTONS::MINI: return *mSprites[SPRITES::MINI_BUTTON];
    default: return *mSprites[SPRITES::INVENTORY_BUTTON];
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

sf::Font& AssetManager::GetFont(FONTS::FONT font)
{
    return *mFonts[font];
}

PLAYSOUND::PLAYSOUND AssetManager::GetSoundForItem(std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> item)
{
    switch (item.first)
    {
        //Gold
    case ITEMID::GOLD:              return PLAYSOUND::GOLD_DROP;
        //Scrolls
    case ITEMID::TPSCROLL:          return PLAYSOUND::SCROLL_DROP;
    case ITEMID::IDSCROLL:          return PLAYSOUND::SCROLL_DROP;
        //Amulets
    case ITEMID::AMULET1:           return PLAYSOUND::AMULET_DROP;
    case ITEMID::AMULET2:           return PLAYSOUND::AMULET_DROP;
    case ITEMID::AMULET3:           return PLAYSOUND::AMULET_DROP;
        //Charms
    case ITEMID::CHARM1:            return PLAYSOUND::CHARM_DROP;
    case ITEMID::CHARM2:            return PLAYSOUND::CHARM_DROP;
    case ITEMID::CHARM3:            return PLAYSOUND::CHARM_DROP;
    case ITEMID::ANNIHILUS:         return PLAYSOUND::CHARM_DROP;
        //Gems
    case ITEMID::AMETHYST_F:        return PLAYSOUND::GEM_DROP;
    case ITEMID::AMETHYST_P:        return PLAYSOUND::GEM_DROP;
    case ITEMID::DIAMOND_F:         return PLAYSOUND::GEM_DROP;
    case ITEMID::DIAMOND_P:         return PLAYSOUND::GEM_DROP;
    case ITEMID::EMERALD_F:         return PLAYSOUND::GEM_DROP;
    case ITEMID::EMERALD_P:         return PLAYSOUND::GEM_DROP;
    case ITEMID::RUBY_F:            return PLAYSOUND::GEM_DROP;
    case ITEMID::RUBY_P:            return PLAYSOUND::GEM_DROP;
    case ITEMID::SAPPHIRE_F:        return PLAYSOUND::GEM_DROP;
    case ITEMID::SAPPHIRE_P:        return PLAYSOUND::GEM_DROP;
    case ITEMID::TOPAZ_F:           return PLAYSOUND::GEM_DROP;
    case ITEMID::TOPAZ_P:           return PLAYSOUND::GEM_DROP;
        //Skulls
    case ITEMID::SKULL_F:           return PLAYSOUND::SKULL_DROP;
    case ITEMID::SKULL_P:           return PLAYSOUND::SKULL_DROP;
        //Jewels
    case ITEMID::JEWEL_1:           return PLAYSOUND::JEWEL_DROP;
    case ITEMID::JEWEL_2:           return PLAYSOUND::JEWEL_DROP;
    case ITEMID::JEWEL_3:           return PLAYSOUND::JEWEL_DROP;
    case ITEMID::JEWEL_4:           return PLAYSOUND::JEWEL_DROP;
    case ITEMID::JEWEL_5:           return PLAYSOUND::JEWEL_DROP;
    case ITEMID::JEWEL_6:           return PLAYSOUND::JEWEL_DROP;
    case ITEMID::WORLDSTONE_SHARD:  return PLAYSOUND::JEWEL_DROP;
        //Key
    case ITEMID::KEY:               return PLAYSOUND::KEY_DROP;
        //Rings
    case ITEMID::RING1:             return PLAYSOUND::RING_DROP;
    case ITEMID::RING2:             return PLAYSOUND::RING_DROP;
    case ITEMID::RING3:             return PLAYSOUND::RING_DROP;
        //Runes
    case ITEMID::ELRUNE:            return PLAYSOUND::RUNE_DROP;
    case ITEMID::ELDRUNE:           return PLAYSOUND::RUNE_DROP;
    case ITEMID::TIRRUNE:           return PLAYSOUND::RUNE_DROP;
    case ITEMID::NEFRUNE:           return PLAYSOUND::RUNE_DROP;
    case ITEMID::ETHRUNE:           return PLAYSOUND::RUNE_DROP;
    case ITEMID::ITHRUNE:           return PLAYSOUND::RUNE_DROP;
    case ITEMID::TALRUNE:           return PLAYSOUND::RUNE_DROP;
    case ITEMID::RALRUNE:           return PLAYSOUND::RUNE_DROP;
    case ITEMID::ORTRUNE:           return PLAYSOUND::RUNE_DROP;
    case ITEMID::THULRUNE:          return PLAYSOUND::RUNE_DROP;
    case ITEMID::AMNRUNE:           return PLAYSOUND::RUNE_DROP;
    case ITEMID::SOLRUNE:           return PLAYSOUND::RUNE_DROP;
    case ITEMID::SHAELRUNE:         return PLAYSOUND::RUNE_DROP;
    case ITEMID::DOLRUNE:           return PLAYSOUND::RUNE_DROP;
    case ITEMID::HELRUNE:           return PLAYSOUND::RUNE_DROP;
    case ITEMID::IORUNE:            return PLAYSOUND::RUNE_DROP;
    case ITEMID::LUMRUNE:           return PLAYSOUND::RUNE_DROP;
    case ITEMID::KORUNE:            return PLAYSOUND::RUNE_DROP;
    case ITEMID::FALRUNE:           return PLAYSOUND::RUNE_DROP;
    case ITEMID::LEMRUNE:           return PLAYSOUND::RUNE_DROP;
    case ITEMID::PULRUNE:           return PLAYSOUND::RUNE_DROP;
    case ITEMID::UMRUNE:            return PLAYSOUND::RUNE_DROP;
    case ITEMID::MALRUNE:           return PLAYSOUND::RUNE_DROP;
    case ITEMID::ISTRUNE:           return PLAYSOUND::RUNE_DROP;
    case ITEMID::GULRUNE:           return PLAYSOUND::RUNE_DROP;
    case ITEMID::VEXRUNE:           return PLAYSOUND::RUNE_DROP;
    case ITEMID::OHMRUNE:           return PLAYSOUND::RUNE_DROP;
    case ITEMID::LORUNE:            return PLAYSOUND::RUNE_DROP;
    case ITEMID::SURRUNE:           return PLAYSOUND::RUNE_DROP;
    case ITEMID::BERRUNE:           return PLAYSOUND::RUNE_DROP;
    case ITEMID::JAHRUNE:           return PLAYSOUND::RUNE_DROP;
    case ITEMID::CHAMRUNE:          return PLAYSOUND::RUNE_DROP;
    case ITEMID::ZODRUNE:           return PLAYSOUND::RUNE_DROP;
    default:                        return PLAYSOUND::BUTTON_DOWN;
    }
}

int AssetManager::GetCostForNextLevelUpgrade(LEVELS::UPGRADE levelUpgrade)
{
    switch (levelUpgrade)
    {
    case LEVELS::ONE_CHEST: return 10000;
    case LEVELS::TWO_CHEST: return 20000;
    case LEVELS::THREE_CHEST: return 50000;
    case LEVELS::FOUR_CHEST: return 0;
    default: return 0;
    }
}
