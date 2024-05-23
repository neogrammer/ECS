#include "GameEngine.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include "../../include/core/GameEngine.hpp"

#include <imgui-SFML.h>

// ctor, no dtor neccessary... RAII be like that sometimes
GameEngine::GameEngine()
	: m_entityManager{}, m_systems{}
	, wnd{ sf::VideoMode(::GameProperties::SCRW, ::GameProperties::SCRH), "ECS_Architecture" }
{
	m_systems.clear();
	// 0 - Movement System
	m_systems.emplace_back(std::make_unique<MovementSystem>());
}

// hotpotato that shit
void GameEngine::propogateInput(std::vector<sf::Event>& l_evts)
{
	for (auto& e : l_evts)
	{
		// check which event and handle it via delegation
		// if delegate returns true, it was a successful execution, 
		//   log the event into an action file sequentially for an action replay file we could possibly use
	}
}

// make it rain on em
void GameEngine::handleWindowEvents(std::vector<sf::Event>& l_evts)
{
	for (auto& e : l_evts)
	{
		if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Escape)
		{
			wnd.close();
		}
		// check which event , handle it here first as super ceding any inner game action, such as reset,
		//   then still pass it along in case a delegate is waiting for it
	}
}

// value passed to this function always simulates a normalization to 60 fps, no matter what
//  should be smooth physics calculations because of this
void GameEngine::update(double l_dt)
{
	m_entityManager.update(l_dt);

	for (auto& s : m_systems)
	{
		s->update(l_dt);
	}
}

// work your magic in here, blit a portion of a giant rendertexture sitting on the GPU the size of the window to the window for performance
void GameEngine::render(sf::RenderWindow& l_wnd)
{
}

// to abstract implementation away from the main function, just to be clean and concise
void GameEngine::mainLoop()
{
	
	ImGui::SFML::Init(wnd);

	sf::Time deltaTime{ sf::Time::Zero };
	sf::Clock frameTimer{ };

	bool focus = true;
	wnd.setVerticalSyncEnabled(true);

	

	frameTimer.restart();
	while (wnd.isOpen())
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
				if (event.type == sf::Event::Closed)
					wnd.close();

				evtsToProp.emplace_back(std::move(event));
			}
			handleWindowEvents(evtsToProp);

			deltaTime += frameTimer.restart();
			bool repaint = false;
			while ((double)deltaTime.asSeconds() > ::GameProperties::FPS)
			{
				update(::GameProperties::FPS);
				deltaTime -= sf::seconds((float)::GameProperties::FPS);
				repaint = true;
			}
			// no partual update (carry over to build up to an update next frame if less than 0.016666667 seconds

			wnd.clear(sf::Color::Blue);

			// render every frame update only
			if (repaint)
			{
				render(wnd);
			}
			wnd.display();
		}
		else
		{
			frameTimer.restart();
			deltaTime = sf::Time::Zero;
		}

	}
	
}




