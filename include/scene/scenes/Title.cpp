#include "Title.hpp"
#include "../../core/GameEngine.hpp"
#include "../ECS/system/systems/RenderSystem.hpp"
#include "../ECS/system/systems/MovementSystem.hpp"
#include "../ECS/system/systems/InputSystem.hpp"
#include "../ECS/system/systems/CollisionSystem.hpp"
#include <iostream>
Title::Title(GameEngine& l_game)
	: Scene(l_game)
	, m_systems{}
	, spear{}
	, titleBG{}
	, titleFont{}
	, selector{}
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
	spear.setPosition(320, 160);
}

Title::~Title()
{
}

void Title::propogateInput(std::vector<sf::Event> l_evts)
{

	// container of keys pressed this frame
	for (auto& e : l_evts)
	{
		switch (e.type)
		{
		case sf::Event::KeyPressed:
		{
			switch (e.key.code)
			{
			case sf::Keyboard::Enter:
				std::cout << "Input System Test:  Working" << std::endl;
				// add "Enter" to keys pressed this frame
				break;
			default:
				break;
			}
		}
			break;
		default:
			break;
		}
	}
	// send container to ActiveKeys data structure, review Status of ActiveKeys unique to this Scene
	// any currently Status::OFF that are in the container, set Status::ON, 
	// any currently Status::ON but not in the container, set Status::RELEASED, 
	// any currently STATUS::ON and are in the container, set Status::HELD, 
	// any currently STATUS::RELEASED that are not in the container set Status::OFF, but the ones that are set Status::ON

	// now we have the states of all our current keyboard, send those updated states to be processed by each active key's registered action for their respective Status
	// which is a partial function living in another class defined as the varying parameter for the function bound to a Derived scene type, 
	// so the same function  can switch on the scene type and change its behavior dynamically while having access to the scenes data for manipulation
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
