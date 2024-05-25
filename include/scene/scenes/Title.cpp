#include "Title.hpp"
#include "../../core/GameEngine.hpp"
#include "../ECS/system/systems/RenderSystem.hpp"
#include "../ECS/system/systems/MovementSystem.hpp"
#include "../ECS/system/systems/InputSystem.hpp"
#include "../ECS/system/systems/CollisionSystem.hpp"
#include <iostream>

Title::Title(GameEngine& l_game, ActionMap<int>& l_actionMap)
	: Scene(l_game, l_actionMap)
	, m_systems{}
	, spear{}
	, titleBG{}
	, titleFont{}
	, selector{}
	, curChoice{ 1 }
{
	m_systems.clear();
	// 0 - Movement System
	m_systems.emplace_back(std::make_unique<RenderSystem>(game, &game.wnd));
	m_systems.emplace_back(std::make_unique<MovementSystem>(game));
	m_systems.emplace_back(std::make_unique<InputSystem>(game));
	m_systems.emplace_back(std::make_unique<CollisionSystem>(game));

	titleBG.setTexture(Config::textures.get((int)Config::Textures::TitleBG));
	titleFont.setFont(Config::fonts.get((int)Config::Fonts::FiraOTF));
	titleFont.setString("MegaMario");
	titleFont.setCharacterSize(72);
	titleFont.setFillColor(sf::Color::Black);
	titleFont.setOutlineThickness(6);
	titleFont.setOutlineColor(sf::Color::White);
	titleFont.setPosition(50, 100);

	level1Text.setFont(Config::fonts.get((int)Config::Fonts::FiraOTF));
	level1Text.setString("Play Level1");
	level1Text.setCharacterSize(44);
	level1Text.setFillColor(sf::Color::Black);
	level1Text.setOutlineThickness(6);
	level1Text.setOutlineColor(sf::Color::White);
	level1Text.setPosition(50, 250);

	selector.setTexture(Config::textures.get((int)Config::Textures::Selector));
	selector.setPosition(250, 400);

	spear.setTexture(Config::textures.get((int)Config::Textures::Spear));
	spear.setTextureRect({ {0, 0}, {192, 192} });
	spear.setPosition(choicePos[curChoice]);

	// action bindings
	this->bind((int)Config::Inputs::Up, [this](const sf::Event&) {
		curChoice = 0;
		});

	this->bind((int)Config::Inputs::Down, [this](const sf::Event&) {
		curChoice = 1;
		});

	this->bind((int)Config::Inputs::Right, [this](const sf::Event&) {
		
		});

	this->bind((int)Config::Inputs::A, [this](const sf::Event&) {
	
		});
	this->bind((int)Config::Inputs::AxisX, [this](const sf::Event&) {
		sf::Joystick::update();

		float speed = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);
		if (speed < 0.0f)
		{
		
		}
		else
		{
		
		}

		});
	this->bind((int)Config::Inputs::DPadX, [this](const sf::Event&) {
		sf::Joystick::update();

		float speed = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX);
		if (speed < 0.0f)
		{
		
		}
		else
		{

		}

		});

}

Title::~Title()
{
}

void Title::processInput()
{
	ActionTarget<int>::processEvents();
}


void Title::processEvents(std::vector<sf::Event>& l_evts)
{
}

void Title::update(double l_dt)
{

	for (auto& s : m_systems)
	{

		if (dynamic_cast<RenderSystem*>(s.get()) == nullptr)
			s->update(l_dt);
	}
	spear.setPosition(choicePos[curChoice]);
}

void Title::render(sf::RenderWindow& l_wnd)
{
	// this system only renders, which is handled outside of the traditional update section
	//  hence the odd name here that is misleading, it renders to the window, not updates
	//m_systems.at(0)->update(::GameProperties::FPS);
	l_wnd.draw(titleBG);
	l_wnd.draw(titleFont);
	l_wnd.draw(level1Text);
	l_wnd.draw(spear);
}
