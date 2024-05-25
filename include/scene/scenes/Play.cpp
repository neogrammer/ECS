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
		std::cout << "A" << std::endl;
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
	m_player = eMgr().makeStartingEntities("play");
	m_player->getComponent<CTransform>().pos = Vec2(512, 283);
	m_player->getComponent<CTransform>().prevPos = Vec2(512, 283);
	m_player->getComponent<CShape>().sprite.setPosition({ m_player->getComponent<CTransform>().pos.x,m_player->getComponent<CTransform>().pos.y });
	if (m_player == nullptr)
	{
		std::cout << "Player not found in the play scene's entity manager" << std::endl;
		throw std::runtime_error("shit");
	}
	game.loadAnimations("assets/data/animationAtlas.dat");
	m_player->addComponent<CAnimation>();
	m_player->getComponent<CAnimation>().animation = *game.getAnimation(Config::texNamelookup["Player"], "RunRight");

	m_player->getComponent<CShape>().sprite.setTexture(Config::textures.get((int)Config::texNamelookup["Player"]));
	m_player->getComponent<CShape>().sprite.setTextureRect(m_player->getComponent<CAnimation>().animation.currFrame());
	currentSystem = inputSystem;
}

void Play::processInput()
{
	ActionTarget<int>::processEvents();

	if (inputSystem->inputMap[InputSystem::Signal::Left] == InputSystem::Status::On
		|| inputSystem->inputMap[InputSystem::Signal::Left] == InputSystem::Status::Held)
	{
		if (m_player->getComponent<CTransform>().velocity.x >= 0.1f)
			m_player->getComponent<CTransform>().velocity.x = -60.f;
		else if (m_player->getComponent<CTransform>().velocity.x >= -240.f)
			m_player->getComponent<CTransform>().velocity.x -= 60.f;
	}
	if (inputSystem->inputMap[InputSystem::Signal::Right] == InputSystem::Status::On
		|| inputSystem->inputMap[InputSystem::Signal::Right] == InputSystem::Status::Held)
	{
		if (m_player->getComponent<CTransform>().velocity.x <= -0.1f)
			m_player->getComponent<CTransform>().velocity.x = 60.f;
		else if (m_player->getComponent<CTransform>().velocity.x <= 240.f)
			m_player->getComponent<CTransform>().velocity.x += 60.f;
			
	}
	if (inputSystem->inputMap[InputSystem::Signal::Left] == InputSystem::Status::Off
		&& inputSystem->inputMap[InputSystem::Signal::Right] == InputSystem::Status::Off)
	{
		m_player->getComponent<CTransform>().velocity.x *= 0.86f;
		if (abs(m_player->getComponent<CTransform>().velocity.x) <= 50.f)
			m_player->getComponent<CTransform>().velocity.x *= 0.f;

	}
	
}


void Play::processEvents(std::vector<sf::Event>& l_evts)
{
}

void Play::update(double l_dt)
{
	collisionSystem->update(l_dt);

	movementSystem->update(l_dt);

	// animation
	if (m_player->getComponent<CAnimation>().has)
	{
		if (m_player->getComponent<CTransform>().velocity.x < -0.01f || m_player->getComponent<CTransform>().velocity.x > 0.01f)
		{
			if (m_player->getComponent<CTransform>().velocity.x > 0.01f && m_player->getComponent<CAnimation>().animation.name() != "RunRight")
			{
				// set animation to run right
				m_player->getComponent<CAnimation>().animation = *game.getAnimation(Config::texNamelookup["Player"], "RunRight");
			}
			else if (m_player->getComponent<CTransform>().velocity.x < -0.01f && m_player->getComponent<CAnimation>().animation.name() != "RunLeft")
			{
				//set anim to run left
				m_player->getComponent<CAnimation>().animation = *game.getAnimation(Config::texNamelookup["Player"], "RunLeft");
			}
			
		}
		else
		{
			if (m_player->getComponent<CAnimation>().animation.name() == "RunLeft")
			{
				// idle left
				m_player->getComponent<CAnimation>().animation = *game.getAnimation(Config::texNamelookup["Player"], "IdleLeft");
			}
			else if (m_player->getComponent<CAnimation>().animation.name() == "RunRight")
			{
				// idle right
				m_player->getComponent<CAnimation>().animation = *game.getAnimation(Config::texNamelookup["Player"], "IdleRight");
			}
		}
		m_player->getComponent<CAnimation>().animation.update(sf::seconds((float)l_dt));
		m_player->getComponent<CShape>().sprite.setTextureRect(m_player->getComponent<CAnimation>().animation.currFrame());
	}
}


void Play::render(sf::RenderWindow& l_wnd)
{
	player()->getComponent<CShape>().sprite.setPosition({player()->getComponent<CTransform>().pos.x, player()->getComponent<CTransform>().pos.y });
	l_wnd.draw(player()->getComponent<CShape>().sprite);
}

std::shared_ptr<Entity> Play::player()
{
	return m_entityMgr.getEntity((size_t)0);
}
