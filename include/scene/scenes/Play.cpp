#include "Play.hpp"
#include "../../core/GameEngine.hpp"
#include "../ECS/system/systems/RenderSystem.hpp"
#include "../ECS/system/systems/MovementSystem.hpp"
#include "../ECS/system/systems/InputSystem.hpp"
#include "../ECS/system/systems/CollisionSystem.hpp"

#include <fstream>
#include <iostream>

Play::Play(GameEngine& l_game, ActionMap<int>& l_actionMap, std::string l_playerCfgFile)
	: Scene(l_game, l_actionMap)
	, m_playerCfg(l_playerCfgFile)
	, m_player{}
	, renderSystem{ nullptr }
	, inputSystem{ nullptr }
	, collisionSystem{ nullptr }
	, movementSystem{ nullptr }
	, tmap{}
{
	
	inputSystem = std::make_shared<InputSystem>(game);
	renderSystem = std::make_shared<RenderSystem>(game, &game.wnd);
	movementSystem = std::make_shared<MovementSystem>(game);
	collisionSystem = std::make_shared<CollisionSystem>(game);
	


	// action bindings
	this->bind((int)Config::Inputs::Up, [this](const sf::Event&) {
		inputSystem->currentlyPressed[0].second = true;
		});
	this->bind((int)Config::Inputs::Down, [this](const sf::Event&) {
		inputSystem->currentlyPressed[1].second = true;

		});
	this->bind((int)Config::Inputs::Left, [this](const sf::Event&) {
		inputSystem->currentlyPressed[2].second = true;
		});

	this->bind((int)Config::Inputs::Right, [this](const sf::Event&) {
		inputSystem->currentlyPressed[3].second = true;
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

Play::~Play()
{
}

void Play::init()
{
	if (!eMgr().calledMakeStart)
		m_player = eMgr().makeStartingEntities("play");

	if (m_player == nullptr)
	{
		std::cout << "Player not found in the play scene's entity manager" << std::endl;
		throw std::runtime_error("shit");
	}

	currentSystem = inputSystem;

	tmap = std::shared_ptr<Tilemap>(new Tilemap{ eMgr(), "intro" });
}



void Play::processInput()
{
	ActionTarget<int>::processEvents();

	if (inputSystem->inputMap[InputSystem::Signal::Left] == InputSystem::Status::On
		|| inputSystem->inputMap[InputSystem::Signal::Left] == InputSystem::Status::Held)
	{
		if (m_player->getComponent<cRigidBody>().vel.x >= 0.1f)
			m_player->getComponent<cRigidBody>().vel.x = -60.f;
		else if (m_player->getComponent<cRigidBody>().vel.x >= -240.f)
			m_player->getComponent<cRigidBody>().vel.x -= 60.f;
	}
	if (inputSystem->inputMap[InputSystem::Signal::Right] == InputSystem::Status::On
		|| inputSystem->inputMap[InputSystem::Signal::Right] == InputSystem::Status::Held)
	{
	    if (m_player->getComponent<cRigidBody>().vel.x <= -0.1f)
			m_player->getComponent<cRigidBody>().vel.x = 60.f;
		else if (m_player->getComponent<cRigidBody>().vel.x <= 240.f)
			m_player->getComponent<cRigidBody>().vel.x += 60.f;
			
	}
	if (inputSystem->inputMap[InputSystem::Signal::Left] == InputSystem::Status::Off
		&& inputSystem->inputMap[InputSystem::Signal::Right] == InputSystem::Status::Off)
	{
		m_player->getComponent<cRigidBody>().vel.x *= 0.86f;
		if (abs(m_player->getComponent<cRigidBody>().vel.x) <= 50.f)
			m_player->getComponent<cRigidBody>().vel.x *= 0.f;

	}
	
}


void Play::processEvents(std::vector<sf::Event>& l_evts)
{
}

void Play::update(double l_dt)
{
	collisionSystem->update(l_dt);

	movementSystem->update(l_dt);

	m_player->update(sf::seconds((float)l_dt));
	

		 if (m_player->getComponent<cAnimation>().has)
		 {
			 if (m_player->getComponent<cRigidBody>().vel.x < -0.01f || m_player->getComponent<cRigidBody>().vel.x > 0.01f)
			 {
				 if (m_player->getComponent<cRigidBody>().vel.x > 0.01f && m_player->getComponent<cAnimation>().currAnimation->name() != "RunRight")
				 {
					 // set animation to run right
					 cAnimation::changeAnimation(*m_player, "RunRight");
				 }
				 else if (m_player->getComponent<cRigidBody>().vel.x < -0.01f && m_player->getComponent<cAnimation>().currAnimation->name() != "RunLeft")
				 {
					 //set anim to run left
					 cAnimation::changeAnimation(*m_player, "RunLeft");
				 }

			 }
			 else
			 {
				 if (m_player->getComponent<cAnimation>().currAnimation->name() == "RunLeft")
				 {
					 // idle left
					 cAnimation::changeAnimation(*m_player, "IdleLeft");

				 }
				 else if (m_player->getComponent<cAnimation>().currAnimation->name() == "RunRight")
				 {
					 // idle right
					 cAnimation::changeAnimation(*m_player, "IdleRight");

				 }
			 }
		 }


	//	m_player->getComponent<CAnimation>().animation.update(sf::seconds((float)l_dt));
	//	m_player->getComponent<CShape>().sprite.setTextureRect(m_player->getComponent<CAnimation>().animation.currFrame());
	//}
}


void Play::render(sf::RenderWindow& l_wnd)
{
	tmap->draw(l_wnd);
	m_player->render(l_wnd);


}

std::shared_ptr<Entity> Play::player()
{
	return m_entityMgr.getEntity((size_t)0);
}