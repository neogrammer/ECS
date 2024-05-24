#include "Config.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include "../ECS/Entity.hpp"

//Config Structs
PlayerConfig::PlayerConfig(std::string l_filename)
{
    // load data from file into struct members
}




// static members for screen
float Config::SCREENW{ 1440 };
float Config::SCREENH{ 900 };
int Config::TILEW{ 64 };
int Config::TILEH{ 64 };


sf::Vector2f Config::GRAVITY{ 0.f , 4.8f };

// for resources
ResourceManager<sf::Texture, int> Config::textures;
ResourceManager<sf::Font, int> Config::fonts;
ResourceManager<sf::Music, int> Config::music;
ResourceManager<sf::SoundBuffer, int> Config::sounds;
// for events

/// <summary>
/// Initialize all the resources here in one fell swoop
/// </summary>
void Config::initialize()
{
    initTextures();
    initFonts();
    initMusic();
    initSounds();
}

/// <summary>
/// setup music enum resources
/// </summary>
void Config::initMusic()
{
}

/// <summary>
/// setup sound enum resources
/// </summary>
void Config::initSounds()
{
}

/// <summary>
/// Texture enum resources
/// </summary>
void Config::initTextures()
{
    textures.load((int)Textures::Player, "assets/textures/player_atlas84x84.png");
}

/// <summary>
/// font enum resources
/// </summary>
void Config::initFonts()
{
    //fonts.load(Fonts::Font1, "assets/fnt/Ww.ttf");
}

