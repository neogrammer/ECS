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


#include <imgui-SFML.h>
#include <imgui.h>
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

	m_currentScene = "play";

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
void GameEngine::propogateInput(std::vector<sf::Event>& l_evts)
{
	currentScene()->propogateInput(l_evts);
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
void GameEngine::update(double l_dt)
{
	currentScene()->update(l_dt);

	
}

// work your magic in here, blit a portion of a giant rendertexture sitting on the GPU the size of the window to the window for performance
void GameEngine::render(sf::RenderWindow& l_wnd)
{
	currentScene()->render(l_wnd);
}

bool GameEngine::gameRunning = true;


// to abstract implementation away from the main function, just to be clean and concise
void GameEngine::mainLoop()
{
	
	

	sf::Time deltaTime{ sf::Time::Zero };
	sf::Clock frameTimer{ };

	bool focus = true;
	wnd.setVerticalSyncEnabled(true);

	ImGui::SFML::Init(wnd);
	frameTimer.restart();
	bool guiIsOpen = false;
	while (gameRunning)
	{
		wnd.setPosition(sf::Vector2i(450, 300));
		focus = wnd.hasFocus();
		wnd.setSize({ (unsigned int)::GameProperties::SCRW, (unsigned int)::GameProperties::SCRH });

		if (focus)
		{
			// process realtime input
			std::vector<sf::Event> evtsToProp;
			evtsToProp.clear();
			propogateInput(evtsToProp);
			evtsToProp.clear();
			evtsToProp.resize(0);
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
			bool repaint = false;
			while ((double)deltaTime.asSeconds() > ::GameProperties::FPS)
			{
				update(::GameProperties::FPS);
				if (guiIsOpen)
				{
					ImGui::SFML::Render();
					guiIsOpen = false;
				}
				if (!guiIsOpen)
				{
					ImGui::SFML::Update(wnd, deltaTime);
					ImGui::Begin("Window");
					ImGui::SeparatorText("hello world");
					ImGui::End();
				}

				deltaTime -= sf::seconds((float)::GameProperties::FPS);
				repaint = true;
			}
			if (repaint && !guiIsOpen)
			{
				guiIsOpen = true;
			}
			// no partual update (carry over to build up to an update next frame if less than 0.016666667 seconds

			// render every frame update only
			if (repaint)
			{
				wnd.clear(sf::Color::Blue);

				render(wnd);

				if (guiIsOpen)
				{
					ImGui::SFML::Render(wnd);
					guiIsOpen = false;
				}

				wnd.display();
				
			}
			
		}
		else
		{
			frameTimer.restart();
			deltaTime = sf::Time::Zero;
		}

	}
	// gameRunning is false
afterLoop:
	if (guiIsOpen)
	{
		ImGui::SFML::Render(wnd);
	}
	ImGui::SFML::Shutdown();
	wnd.close();

	return;
}




