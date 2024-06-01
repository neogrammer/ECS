#include "Game.hpp"
#include <imgui.h>

#include <imgui-SFML.h>

#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include "../gamestate/gamestates/PlayState.hpp"
#include "../gamestate/gamestates/TitleState.hpp"
#include <iostream>
#include <typeinfo>
#include <fstream>
#include <type_traits>
#include "../util/Anim.hpp"

// ctor, no dtor neccessary... RAII be like that sometimes
Game::Game()
	: m_gameStates{}, m_currentGameState{ "" }
	, wnd{ sf::VideoMode(G::WND_WIDTH, G::WND_HEIGHT), "ECS_Architecture", sf::Style::None }
	, paused{ false }
{
	/*m_scenes["title"] = std::make_shared<Title>(*this, Config::inputs);
	changeScene("title");*/
	m_gameStates["title"] = std::make_shared<TitleState>(*this, Config::inputs);
	m_currentGameState = "title";
}

std::shared_ptr<GameState> Game::currentGameState()
{
	auto itr = m_gameStates.find(m_currentGameState);
	if (itr == m_gameStates.end())
	{
		std::cout << "uh oh, no scene" << std::endl;
		assert(1 == 2);
		return nullptr;
	}
	else
	{
		return itr->second;
	}
}

void Game::changeGameState(std::string l_gameState)
{
	if (l_gameState == m_currentGameState) return;
	if (m_currentGameState != "")
	{
		auto itr = m_gameStates.find(m_currentGameState);
		if (itr != m_gameStates.end())
		{
			m_gameStates.erase(itr);
		}


	}

	m_currentGameState = l_gameState;

	auto itr = m_gameStates.find(m_currentGameState);
	if (itr != m_gameStates.end())
	{
		return;
	}
	else
	{
		if (m_currentGameState == "title")
		{
			m_gameStates["title"] = std::make_shared<TitleState>(*this, Config::inputs);

		}
		else if (m_currentGameState == "play")
		{
			m_gameStates["play"] = std::make_shared<PlayState>(*this, Config::inputs);

		}
		else
		{
			std::cout << "No Game State of the passed in type " << m_currentGameState << " found!" << std::endl;
			assert(1 == 2);
		}

	/*	if (m_currentScene == "title")
		{
			m_scenes["title"] = std::make_shared<Title>(*this, Config::inputs);
		}
		else if (m_currentScene == "play")
		{
			m_scenes["play"] = std::make_shared<Play>(*this, Config::inputs, "PlayerShitConfigMAYBE");
		}
		else
		{
			std::cout << "no scene" << std::endl;
			m_scenes["title"] = std::make_shared<Title>(*this, Config::inputs);
		}*/
	}

	//m_scenes[m_currentScene]->init();
	return;

}

// value passed to this function always simulates a normalization to 60 fps, no matter what
//  should be smooth physics calculations because of this
void Game::update(sf::Time l_dt)
{
	currentGameState()->update((double)l_dt.asSeconds());


}

// work your magic in here, blit a portion of a giant rendertexture sitting on the GPU the size of the window to the window for performance
void Game::render(sf::RenderWindow& l_wnd)
{
	currentGameState()->render(l_wnd);
}

bool Game::gameRunning = true;


// to abstract implementation away from the main function, just to be clean and concise
void Game::mainLoop()
{



	sf::Time deltaTime{ sf::Time::Zero };
	sf::Clock frameTimer{ };

	wnd.setVerticalSyncEnabled(true);

	wnd.setPosition(sf::Vector2i(450, 300));
	wnd.setSize({ (unsigned int)G::WND_WIDTH, (unsigned int)G::WND_HEIGHT });
	ImGui::SFML::Init(wnd);
	frameTimer.restart();
	bool focus = false;
	bool hadFocus = false;
	bool waitingForARender = false;
	sf::Time fps60 = sf::seconds(1.f / 60.f);

	//

	while (gameRunning)
	{
		focus = wnd.hasFocus();

		if (focus && wnd.isOpen())
		{
			hadFocus = true;
			// process realtime input
			currentGameState()->processInput();
			/*currentScene()->currentSystem->update((double)fps60.asSeconds());*/


			std::vector<sf::Event> evtsToProp;
			evtsToProp.clear();
			// process window events
			sf::Event event;
			while (wnd.pollEvent(event))
			{
				ImGui::SFML::ProcessEvent(wnd, event);
				if (event.type == sf::Event::KeyReleased)
				{
					if (event.key.code == sf::Keyboard::Escape)
					{
						gameRunning = false;
						goto afterLoop;
					}

				}
				else if (event.type == sf::Event::Closed)
				{
					gameRunning = false;
					goto afterLoop;
				}

				evtsToProp.emplace_back(std::move(event));
				if (!gameRunning) goto afterLoop;
			}
			currentGameState()->processEvents(evtsToProp);

			deltaTime += frameTimer.restart();
			ImGui::SFML::Update(wnd, deltaTime);
			waitingForARender = true;
			// uncomment to learn ImGui
			//ImGui::ShowDemoWindow();

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
			if (hadFocus)
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




