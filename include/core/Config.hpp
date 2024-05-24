#ifndef CONFIG_HPP__
#define CONFIG_HPP__

#include <SFML/Graphics.hpp>
#include "ResourceManager.hpp"
#include <vector>
#include <string>
class Entity;

typedef std::vector<std::shared_ptr<Entity> > EntityVec;
typedef std::map<std::string, EntityVec> EntityMap;

struct PlayerConfig
{
    //dataType member1;
    //dataType member2;

    PlayerConfig(std::string l_filename);
};

struct rect
{
    float cx;
    float cy;
    float halfSizeX;
    float halfSizeY;
};

/// Config for the resources for the game is handled here in one fell swoop, before the game is even created
/// </summary>
class Config
{
    // initalize the resources for the entire game
    static void initFonts();
    static void initMusic();
    static void initSounds();
    static void initTextures();
    static void initPlayerInputs();
public:
    // screen configuration global settings
    static float SCREENW;
    static float SCREENH;
    static int TILEH;
    static int TILEW;


    static sf::Vector2f GRAVITY;


    /// <summary>
    /// We don't need to create this class as everything useful is staticcaly accessible
    /// </summary>
    Config() = delete;
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;



    // Housing all the textures in one place so anything in need of a Texture can be a reference initialized to this structure
    enum class Textures : int
    {
        Player,
        Count
    };

    // fonts for the game
    enum class Fonts : int { Count };

    // background music
    enum class Music : int { Count };

    // short sounds
    enum class Sounds : int
    {
        Count
    };



    // resource buckets for each type of resource
    static ResourceManager<sf::Texture, int> textures;
    static ResourceManager<sf::Font, int> fonts;
    static ResourceManager<sf::Music, int> music;
    static ResourceManager<sf::SoundBuffer, int> sounds;

    /// <summary>
    /// Call this before anything else within main to set up all the resources for use within the game
    /// </summary>
    static void initialize();

};

#endif