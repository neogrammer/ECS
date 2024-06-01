#include "PlayState.hpp"
#include "../../core/Game.hpp"
#include "../../gameObj/actors/player/PlayerInput.hpp"
#include <util/Physics.hpp>
#include "../../gameObj/actors/Player.hpp"
#include "../../core/Input.hpp"
#include "../GameState.hpp"

#include <fstream>
#include <iostream>

PlayState::PlayState(Game& l_game, ActionMap<int>& l_actionMap)
	: GameState(l_game, l_actionMap)
	, tmap{}
	, player{}
{
	// action bindings
	this->bind((int)Config::Inputs::Up, [this](const sf::Event&) {
		std::cout << "Pressed up seen by the state" << std::endl;
		});
	this->bind((int)Config::Inputs::Down, [this](const sf::Event&) {
		});
	this->bind((int)Config::Inputs::Left, [this](const sf::Event&) {

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

	std::vector<int> level = {
			64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
			64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
			64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
			64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
			64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
			64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
			64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
			64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
			 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1
	};

	tmap = std::make_unique<Tilemap>(Config::textures.get((int)Config::Textures::Tileset1), level, 32, 64, 16);
}

PlayState::~PlayState()
{
}

void PlayState::init()
{
	//	the_player = std::make_shared<Player>(eMgr().makeStartingEntities("play"));
	//the_player->setCurrState(PlayerInput::JUMP);

	//tmap = std::shared_ptr<Tilemap>(new Tilemap{ eMgr(), "intro" });
}



void PlayState::processInput()
{
	ActionTarget<int>::processEvents();
	player.processInput();
}


void PlayState::processEvents(std::vector<sf::Event>& l_evts)
{
}

void PlayState::update(double l_dt)
{
	

	 player.update(sf::seconds((float)l_dt));
}


void PlayState::render(sf::RenderWindow& l_wnd)
{
	auto mpos = sf::Mouse::getPosition(l_wnd);

	rect r = { {player.getPosition()}, {Vec2(player.getTexRect().width,player.getTexRect().height)}};

	if (Physics::PointVsRect(Vec2(mpos.x, mpos.y), r))
	{
		player.getSprite().setColor(sf::Color(255, 0, 0, 255));
	}
	else
	{
		player.getSprite().setColor(sf::Color(255, 255,255, 255));
	}

	for (auto& t : tmap->getTiles())
	{
		rect r2 = { {t->getPosition()}, {Vec2(t->getTexRect().width,t->getTexRect().height)} };
		if (Physics::PointVsRect(Vec2(mpos.x, mpos.y), r2))
		{
			t->setCollided(true);
		}
		
	}

	tmap->render(l_wnd);
	player.render(l_wnd);
	sf::RectangleShape shp(sf::Vector2f(player.getTexRect().width, player.getTexRect().height));
	shp.setFillColor(sf::Color(0, 255, 185, 100));
	shp.setOutlineColor(sf::Color::White);
	shp.setOutlineThickness(2);
	shp.setPosition(sf::Vector2f(player.getBBox().left, player.getBBox().top));
	l_wnd.draw(shp);
}
