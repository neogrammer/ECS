#include <imgui.h>

#include <imgui-SFML.h>

#include "GameEngine.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include "../../include/core/GameEngine.hpp"

#include "../ECS/system/systems/MovementSystem.hpp"
#include "../ECS/system/systems/RenderSystem.hpp"
#include "../ECS/system/systems/CollisionSystem.hpp"
#include "../ECS/system/systems/InputSystem.hpp"
#include "../scene/scenes/Play.hpp"
#include "../scene/scenes/Title.hpp"


#include <iostream>
#include <typeinfo>
#include <type_traits>

// ctor, no dtor neccessary... RAII be like that sometimes
GameEngine::GameEngine()
	: m_scenes{}, m_currentScene{}
	, wnd{ sf::VideoMode(::GameProperties::SCRW, ::GameProperties::SCRH), "ECS_Architecture", sf::Style::None }
	, paused{false}
{
	m_scenes["play"] = std::make_shared<Play>(*this, "aStringGoesHere");
	m_scenes["title"] = std::make_shared<Title>(*this);

	m_currentScene = "title";

}

std::shared_ptr<Scene> GameEngine::currentScene()
{
	return m_scenes[m_currentScene];
}

void GameEngine::changeScene(std::string l_scene)
{
	m_currentScene = l_scene;
}

// hotpotato that shit
void GameEngine::propogateInput(std::vector<sf::Event> l_evts)
{
	currentScene()->propogateInput(std::move(l_evts));
}

// make it rain on em
void GameEngine::handleWindowEvents(std::vector<sf::Event>& l_evts)
{
	
	for (auto& e : l_evts)
	{
		if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Escape)
		{
			gameRunning = false;
		}
		// check which event , handle it here first as super ceding any inner game action, such as reset,
		//   then still pass it along in case a delegate is waiting for it
	}
	currentScene()->processEvents(l_evts);
}

// value passed to this function always simulates a normalization to 60 fps, no matter what
//  should be smooth physics calculations because of this
void GameEngine::update(sf::Time l_dt)
{
	currentScene()->update((double)l_dt.asSeconds());

	
}

// work your magic in here, blit a portion of a giant rendertexture sitting on the GPU the size of the window to the window for performance
void GameEngine::render(sf::RenderWindow& l_wnd)
{
	currentScene()->render(l_wnd);
}

std::vector<sf::Event> GameEngine::checkRealtime()
{
	std::vector<sf::Event> evts;
	evts.clear();
	for (int i = 0; i < sf::Keyboard::KeyCount; i++)
	{
		auto k = (sf::Keyboard::Key)i;
		if (sf::Keyboard::isKeyPressed(k))
		{
			evts.emplace_back(sf::Event{});
			evts.back().type = sf::Event::KeyPressed;
			evts.back().key.code = k;
		}
	}
	return evts;
}

bool GameEngine::gameRunning = true;


// to abstract implementation away from the main function, just to be clean and concise
void GameEngine::mainLoop()
{
	
	

	sf::Time deltaTime{ sf::Time::Zero };
	sf::Clock frameTimer{ };

	wnd.setVerticalSyncEnabled(true);

	wnd.setPosition(sf::Vector2i(450, 300));
	wnd.setSize({ (unsigned int)::GameProperties::SCRW, (unsigned int)::GameProperties::SCRH });
	ImGui::SFML::Init(wnd);
	frameTimer.restart();
	bool focus = false;
	bool hadFocus = false;
	bool waitingForARender = false;
	sf::Time fps60 = sf::seconds(1.f / 60.f);
	while (gameRunning)
	{
		focus = wnd.hasFocus();

		if (focus && wnd.isOpen())
		{
			hadFocus = true;
			// process realtime input
			propogateInput(std::move(checkRealtime()));

			std::vector<sf::Event> evtsToProp;
			evtsToProp.clear();
			// process window events
			sf::Event event;
			while (wnd.pollEvent(event))
			{
				ImGui::SFML::ProcessEvent(wnd, event);

				if (event.type == sf::Event::Closed)
				{
					gameRunning = false;
					goto afterLoop;
				}

				evtsToProp.emplace_back(std::move(event));
				if (!gameRunning) goto afterLoop;
			}
			handleWindowEvents(evtsToProp);

			deltaTime += frameTimer.restart();
			ImGui::SFML::Update(wnd, deltaTime);
			waitingForARender = true;
			ImGui::ShowDemoWindow();
	
			while (deltaTime > fps60)
			{
				update(fps60);
				
				deltaTime -= fps60;
			}
			ImGui::Begin("Window");
			ImGui::SeparatorText("hello world");
			ImGui::End();

			wnd.clear(sf::Color::Blue);

			render(wnd);
			ImGui::SFML::Render(wnd);
			waitingForARender = false;
			wnd.display();
			
		}
		else
		{
			frameTimer.restart();
			if (hadFocus )
			{
				hadFocus = false;
				if (waitingForARender)
				{
					ImGui::SFML::Render(wnd);
					waitingForARender = false;
				}
			}
		}

	}
afterLoop:
	if (waitingForARender)
	{
		ImGui::SFML::Render(wnd);
		waitingForARender = false;
	}
	ImGui::SFML::Shutdown();
	wnd.close();
}




