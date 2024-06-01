#include "Config.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>


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




// for resources
ResourceManager<sf::Texture, int> Config::textures;
ResourceManager<sf::Font, int> Config::fonts;
ResourceManager<sf::Music, int> Config::music;
ResourceManager<sf::SoundBuffer, int> Config::sounds;

ActionMap<int> Config::inputs{};
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
    initInputs();
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
    textures.load((int)Textures::TitleBG, "assets/textures/TitleScreen.jpg");
    textures.load((int)Textures::Selector, "assets/textures/select.png");
    textures.load((int)Textures::Spear, "assets/textures/spear.png");
    textures.load((int)Textures::Tileset1, "assets/textures/crateria64.png");



}

std::map<std::string, Config::Textures> Config::texNamelookup = {
    {"Player", Textures::Player},
    {"TitleBG", Textures::TitleBG},
    {"Selector", Textures::Selector},
    {"Spear", Textures::Spear},
    {"Tileset1", Textures::Tileset1}
};





/// <summary>
/// font enum resources
/// </summary>
void Config::initFonts()
{
    fonts.load((int)Fonts::FiraOTF, "assets/fonts/Fira.otf");
}


/// <summary>
/// setup input enum mappings
/// </summary>
void Config::initInputs()
{

    // realtime events

    // Keyboard pressed commands
    inputs.map((int)Config::Inputs::X, Action(sf::Keyboard::W));
    inputs.map((int)Config::Inputs::Y, Action(sf::Keyboard::D));
    inputs.map((int)Config::Inputs::A, Action(sf::Keyboard::Space));
    inputs.map((int)Config::Inputs::B, Action(sf::Keyboard::A));
    inputs.map((int)Config::Inputs::L1, Action(sf::Keyboard::Q));
    inputs.map((int)Config::Inputs::R1, Action(sf::Keyboard::R));
    // menu controls
    inputs.map((int)Config::Inputs::Start, Action(sf::Keyboard::Enter));
    inputs.map((int)Config::Inputs::Select, Action(sf::Keyboard::Slash));
    // direction controls
    inputs.map((int)Config::Inputs::Up, Action(sf::Keyboard::Up));
    inputs.map((int)Config::Inputs::Down, Action(sf::Keyboard::Down));
    inputs.map((int)Config::Inputs::Left, Action(sf::Keyboard::Left));
    inputs.map((int)Config::Inputs::Right, Action(sf::Keyboard::Right));


    // Joystick Controls
    // Axis mappings
    inputs.map((int)Config::Inputs::AxisX, Action(sf::Joystick::Axis::X, Action::Type::RealTime | Action::Type::Tilted));
    inputs.map((int)Config::Inputs::AxisY, Action(sf::Joystick::Axis::Y, Action::Type::RealTime | Action::Type::Tilted));
    inputs.map((int)Config::Inputs::DPadX, Action(sf::Joystick::Axis::PovX, Action::Type::RealTime | Action::Type::Tilted));
    inputs.map((int)Config::Inputs::DPadY, Action(sf::Joystick::Axis::PovY, Action::Type::RealTime | Action::Type::Tilted));
    // Button mappings
    inputs.map((int)Config::Inputs::JoyA, Action(JoystickBtn::A, Action::Type::RealTime | Action::Type::Pressed));
    inputs.map((int)Config::Inputs::JoyB, Action(JoystickBtn::B, Action::Type::RealTime | Action::Type::Pressed));
    inputs.map((int)Config::Inputs::JoyX, Action(JoystickBtn::X, Action::Type::RealTime | Action::Type::Pressed));
    inputs.map((int)Config::Inputs::JoyY, Action(JoystickBtn::Y, Action::Type::RealTime | Action::Type::Pressed));
    inputs.map((int)Config::Inputs::JoyL1, Action(JoystickBtn::L1, Action::Type::RealTime | Action::Type::Pressed));
    inputs.map((int)Config::Inputs::JoyR1, Action(JoystickBtn::R1, Action::Type::RealTime | Action::Type::Pressed));
    inputs.map((int)Config::Inputs::JoyStart, Action(JoystickBtn::Start, Action::Type::RealTime | Action::Type::Pressed));
    inputs.map((int)Config::Inputs::JoySelect, Action(JoystickBtn::Select, Action::Type::RealTime | Action::Type::Pressed));
}

