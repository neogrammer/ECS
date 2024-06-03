#include "PlayState.hpp"
#include "../../core/Game.hpp"
#include "../../gameObj/actors/player/PlayerInput.hpp"
#include <util/Physics.hpp>
#include "../../gameObj/actors/Player.hpp"
#include "../../core/Input.hpp"
#include <util/Physics.hpp>
#include "../GameState.hpp"
#include <system/systems/CollisionSystem.hpp>

#include <fstream>
#include <iostream>

PlayState::PlayState(Game& l_game, ActionMap<int>& l_actionMap)
	: GameState(l_game, l_actionMap)
	, tmap{}
	, player{}
	, vRects{}
	, colSys{}
	, m_deltaTime{ sf::Time::Zero }
{

	// action bindings
	this->bind((int)Config::Inputs::Up, [this](const sf::Event&) {\
		});
	this->bind((int)Config::Inputs::Down, [this](const sf::Event&) {
		
		});

	this->bind((int)Config::Inputs::Start, [this](const sf::Event&) {
		showCollisionBox = false;
		});
	this->bind((int)Config::Inputs::Select, [this](const sf::Event&) {
		showCollisionBox = true;
		});
	this->bind((int)Config::Inputs::Left, [this](const sf::Event&) {
		
		});

	this->bind((int)Config::Inputs::Right, [this](const sf::Event&) {
		
		});

	this->bind((int)Config::Inputs::A, [this](const sf::Event&) {
		std::cout << "Fire a bullet" << std::endl;
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

	init();

	colSys = std::make_unique<CollisionSystem>(*this, l_game.wnd, m_deltaTime);
}

PlayState::~PlayState()
{
}

void PlayState::init()
{

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

void PlayState::GetMouseClick()
{

	mouseLeftClicked = false;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (mouseLeftDown)
		{

			mouseLeftHeld = true;

		}
		else
		{
			mouseLeftDown = true;

		}
		mouseLeftUp = false;
	}
	else
	{
		if (mouseLeftDown || mouseLeftHeld)
		{
			mouseLeftClicked = true;
			mouseLeftDown = false;
			mouseLeftHeld = false;
			mouseLeftUp = true;
		}
		else
		{
			mouseLeftUp = true;
		}

	}

	if (mouseLeftClicked)
	{
		std::cout << "CLicked" << std::endl;
	}
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
	m_deltaTime = sf::seconds((float)l_dt);
	GetMouseClick();
    
    // check collisions with the map and adjust velocity accordingly
    colSys->update();

    //  Update the playerObject based on end of frame calculated velocity to finalize the physics for this state's frame
    // returns the players state used in render
	player.update(sf::seconds((float)l_dt));

	// check the players state against the returned value by the playerObject's update method stored in this states update function
		//  if it is not what the current animation of that entity is, then switch it to the returned state gotten at the end of the update function
		// 
		// playerAnimator.changeAnimation(m_currentPlayerState);
		// if (not the same texture either)
		//	||||||playerObj||||||player.setTexture(Comfig::textures.get((int)texnameLookup[playerAnimator.currentAnimation().texName]);
		// 
		// playerAnimator.update(l_dt);
		//||||||playerObj|||||player.setTextureRect(playerAnimator.getCurrFrameRect());

}


void PlayState::render(sf::RenderWindow& l_wnd)
{
	// update mouse coords
	mpos = Vec2(sf::Mouse::getPosition(l_wnd).x, sf::Mouse::getPosition(l_wnd).y);

	// render the tilemap
	tmap->render(l_wnd);

	//render the player at the right spot with the correct anumation
	player.render(l_wnd);

	if (showCollisionBox) {
		sf::RectangleShape shp(sf::Vector2f((float)player.getTexRect().width, (float)player.getTexRect().height));
		shp.setFillColor(sf::Color(0, 255, 185, 100));
		shp.setOutlineColor(sf::Color::White);
		shp.setOutlineThickness(2);
		shp.setPosition(sf::Vector2f(player.getBBox().left, player.getBBox().top));
		l_wnd.draw(shp);
	}

}
