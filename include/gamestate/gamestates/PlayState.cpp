#include "PlayState.hpp"
#include "../../core/Game.hpp"
#include "../../gameObj/actors/player/PlayerInput.hpp"
#include <util/Physics.hpp>
#include "../../gameObj/actors/Player.hpp"
#include "../../core/Input.hpp"
#include <util/Physics.hpp>
#include "../GameState.hpp"

#include <fstream>
#include <iostream>

PlayState::PlayState(Game& l_game, ActionMap<int>& l_actionMap)
	: GameState(l_game, l_actionMap)
	, tmap{}
	, player{}
	, vRects{}
{
	// action bindings
	this->bind((int)Config::Inputs::Up, [this](const sf::Event&) {
		std::cout << "Pressed up seen by the state" << std::endl;
		});
	this->bind((int)Config::Inputs::Down, [this](const sf::Event&) {
		player.getVelocity().y += 100.0f * (float)m_dt;
		});
	this->bind((int)Config::Inputs::Left, [this](const sf::Event&) {
		player.getVelocity().x -= 100.0f * (float)m_dt;
		});

	this->bind((int)Config::Inputs::Right, [this](const sf::Event&) {
		player.getVelocity().x += 100.0f * (float)m_dt;
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
	m_dt = (float)l_dt;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (mouseLeftDown)
		{
			
			mouseLeftHeld = true;
			std::cout << "HEld" << std::endl;
		}
		else
		{
			mouseLeftDown = true;
			std::cout << "Down" << std::endl;
		}
		mouseLeftUp = false;
	}
	else
	{
		if (mouseLeftDown || mouseLeftHeld)
		{
			mouseLeftClicked = true;
			std::cout << "CLicked" << std::endl;
		}
		else
		{
			mouseLeftClicked = false;
		}
		mouseLeftDown = false;
		mouseLeftHeld = false;
		mouseLeftUp = true;

	}


	 player.update(sf::seconds((float)l_dt));

	 rect r = { {player.getCenter().x - player.aabbHW(),player.getCenter().y - player.aabbHH()},{player.getBBox().width, player.getBBox().height} };
	 r.vel = player.getVelocity();
	/* if (mouseLeftHeld)
		r.vel += (mpos - r.pos).normalized() * 100.0f * (float)l_dt;*/

	 float t2 = 0, min_t = INFINITY;
	 Vec2 cp2, cn2;
	 std::vector<std::pair<int, float>> z;
	 // Work out collision point, add it to vector along with rect ID
	
	 auto& ts = tmap->getTiles();
	 for (int i = 0; i < tmap->getTiles().size(); i++)
	 {
		 rect r2 = { {ts[i]->getCenter().x - ts[i]->aabbHW(), ts[i]->getCenter().y - ts[i]->aabbHH()},{ts[i]->getBBox().width,ts[i]->getBBox().height}};

		 if (Physics::DynamicRectVsRect(&r, (float)l_dt, r2, cp2, cn2, t2))
		 {
			 z.push_back({ i, t2 });
		 }
	 }

	 // Do the sort
	 std::sort(z.begin(), z.end(), [](const std::pair<int, float>& a, const std::pair<int, float>& b)
		 {
			 return a.second < b.second;
		 });

	 // Now resolve the collision in correct order 
	 for (auto j : z)
	 {
		 rect r2 = { {ts[j.first]->getCenter().x - ts[j.first]->aabbHW(), ts[j.first]->getCenter().y - ts[j.first]->aabbHH()},{ts[j.first]->getBBox().width,ts[j.first]->getBBox().height} };
		 Physics::ResolveDynamicRectVsRect(&r, m_dt, &r2);
		 
	 }

	 // UPdate the player rectangles position, with its modified velocity
	 player.getVelocity() = r.vel;
	 player.move(player.getVelocity() * m_dt);
	
}


void PlayState::render(sf::RenderWindow& l_wnd)
{
	mpos = Vec2(sf::Mouse::getPosition(l_wnd).x, sf::Mouse::getPosition(l_wnd).y);

	tmap->render(l_wnd);
	player.render(l_wnd);

	sf::RectangleShape shp(sf::Vector2f((float)player.getTexRect().width, (float)player.getTexRect().height));
	shp.setFillColor(sf::Color(0, 255, 185, 100));
	shp.setOutlineColor(sf::Color::White);
	shp.setOutlineThickness(2);
	shp.setPosition(sf::Vector2f(player.getBBox().left, player.getBBox().top));
	l_wnd.draw(shp);

}
