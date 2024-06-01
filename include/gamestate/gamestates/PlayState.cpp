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

	vRects.push_back({ { 10.f ,10.f }, { 30.f,20.f }, { 0.f, 0.f} });
	vRects.push_back({ { 100.f ,100.f }, { 80.f,50.f }, { 0.f, 0.f} });
	//vRects.push_back({ { 0.f ,0.f }, { 0.f,0.f }, { 0.f, 0.f} });
	//vRects.push_back({ { 0.f ,0.f }, { 0.f,0.f }, { 0.f, 0.f} });
	//vRects.push_back({ { 0.f ,0.f }, { 0.f,0.f }, { 0.f, 0.f} });
	//vRects.push_back({ { 0.f ,0.f }, { 0.f,0.f }, { 0.f, 0.f} });
	//vRects.push_back({ { 0.f ,0.f }, { 0.f,0.f }, { 0.f, 0.f} });
	//vRects.push_back({ { 0.f ,0.f }, { 0.f,0.f }, { 0.f, 0.f} });

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
}


void PlayState::render(sf::RenderWindow& l_wnd)
{

	rect r = { {player.getPosition()}, {Vec2(player.getTexRect().width,player.getTexRect().height)}};

	Vec2 ray_point = { 20,20 };
	Vec2 ray_direction = mpos - ray_point;
	sf::VertexArray arr(sf::PrimitiveType::Lines, 2);

	arr[0].position = sf::Vector2f(ray_point.x,ray_point.y);
	arr[1].position = sf::Vector2f(mpos.x, mpos.y);
	arr[0].color = sf::Color::White;
	arr[1].color = sf::Color::White;

	rect s = { Vec2(mpos.x - 5.f, mpos.y - 20.f), {10.f, 40.0f} };

	if (Physics::RectVsRect(s, r))
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
		if (Physics::RectVsRect({ Vec2(mpos.x - 5.f, mpos.y - 20.f), {10.f, 40.0f} }, r2))
		{
			t->setCollided(true);
		}
		
	}

	Vec2 cp, cn;
	float t;

	if (Physics::RayVsRect(ray_point, ray_direction, r, t, cn, cp) && t <= 1.0f)
	{
		arr[0].color = sf::Color::Red;
		arr[1].color = sf::Color::Red;
	}
	else
	{
		arr[0].color = sf::Color::White;
		arr[1].color = sf::Color::White;
	}

	Vec2 box_origin = vRects[0].pos;
	Vec2 box_dir = mpos - box_origin;
	box_dir.normalize();

	Vec2 old = vRects[0].pos;
	Vec2 oldV = vRects[0].vel;
	if (mouseLeftHeld)
		vRects[0].vel += box_dir * 100.f * m_dt;
	else
		vRects[0].vel = { 0.f,0.f };

	vRects[0].pos += vRects[0].vel * m_dt;

	if (Physics::RectVsRect(vRects[0], vRects[1]))
	{
		vRects[0].pos = old;
		while (Physics::RectVsRect(vRects[0], vRects[1]))
		{
			vRects[0].pos += -1 * oldV * m_dt;
		}
		vRects[0].vel = vRects[0].vel * cn;

	}
	

	for (int i = 1; i < vRects.size(); i++)
	{
		if (Physics::DynamicVsRect(vRects[0], vRects[i], m_dt, t, cn, cp))
		{

			vRects[0].vel = { 0.f,0.f };
			
		}
	}
	vRects[0].pos += vRects[0].vel * m_dt;

	tmap->render(l_wnd);
	player.render(l_wnd);
	sf::RectangleShape shp(sf::Vector2f((float)player.getTexRect().width, (float)player.getTexRect().height));
	shp.setFillColor(sf::Color(0, 255, 185, 100));
	shp.setOutlineColor(sf::Color::White);
	shp.setOutlineThickness(2);
	shp.setPosition(sf::Vector2f(player.getBBox().left, player.getBBox().top));
	l_wnd.draw(shp);

	sf::RectangleShape shp2(sf::Vector2f(s.size.x, s.size.y));
	shp2.setFillColor(sf::Color(0, 0, 0, 100));
	shp2.setOutlineColor(sf::Color::Black);
	shp2.setOutlineThickness(1);
	shp2.setPosition(sf::Vector2f(mpos.x - s.size.x / 2.f, mpos.y - s.size.y / 2.f));
	l_wnd.draw(shp2);

	l_wnd.draw(arr);

	sf::RectangleShape shpVr1(sf::Vector2f(vRects[0].size.x, vRects[0].size.y));
	shpVr1.setFillColor(sf::Color::Transparent);
	shpVr1.setOutlineColor(sf::Color::White);
	shpVr1.setOutlineThickness(2);
	shpVr1.setPosition(sf::Vector2f(vRects[0].pos.x, vRects[0].pos.y));
	l_wnd.draw(shpVr1);

	sf::RectangleShape shpVr2(sf::Vector2f(vRects[1].size.x, vRects[1].size.y));
	shpVr2.setFillColor(sf::Color::Transparent);
	shpVr2.setOutlineColor(sf::Color::White);
	shpVr2.setOutlineThickness(2);
	shpVr2.setPosition(sf::Vector2f(vRects[1].pos.x, vRects[1].pos.y));
	l_wnd.draw(shpVr2);

	sf::VertexArray lil(sf::PrimitiveType::Lines, 2);
	lil[0].color = sf::Color::Green;
	lil[1].color = sf::Color::Green;
	lil[0].position = sf::Vector2f(box_origin.x,box_origin.y);
	lil[1].position = sf::Vector2f(box_dir.x,box_dir.y);

	/*(sf::Vector2f( vRects[1].pos.x - box_origin.x, vRects[1].pos.y - box_origin.y));
	lil.setFillColor(sf::Color(0, 255, 0, 200));
	lil.setOutlineColor(sf::Color::Black);
	lil.setOutlineThickness(1);
	lil.setPosition(sf::Vector2f(box_origin.x, box_origin.y));*/
	l_wnd.draw(lil);

	mpos = Vec2(sf::Mouse::getPosition(l_wnd).x, sf::Mouse::getPosition(l_wnd).y);

}
