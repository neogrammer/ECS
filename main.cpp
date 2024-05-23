#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include "include/core/GameEngine.hpp"

#include <imgui-SFML.h>


int main()
{
	sf::RenderWindow wnd{ sf::VideoMode(1024,576), "ECS_Architecture" };
	ImGui::SFML::Init(wnd);

	sf::Time deltaTime{ sf::Time::Zero };
	sf::Clock frameTimer{ };
	
	bool focus = true;
	wnd.setVerticalSyncEnabled(true);

	GameEngine game;

	frameTimer.restart();
	while (wnd.isOpen())
	{
		wnd.setPosition(sf::Vector2i(450, 300));
		focus = wnd.hasFocus();
		wnd.setSize({ 1024U, 576U });

		if (focus)
		{
			// process realtime input
			// std::vector<sf::Event> evtsToProp;
			// evtsToProp.clear();
			// propogateInput(evtsToProp);
			// evtsToProp.clear();
			// evtsToProp.resize(0);
			// process window events
			sf::Event event;
			while (wnd.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					wnd.close();

				// evtsToProp.emplace_back(std::move(e));
			}
			// ::handleWindowEvents(evtsToProp);

			deltaTime += frameTimer.restart();
			bool repaint = false;
			while ((double)deltaTime.asSeconds() > 0.016666667)
			{
				//update(0.016666667);
				deltaTime -= sf::seconds((float)0.016666667);
				repaint = true;
			}
			// no partual update (carry over to build up to an update next frame if less than 0.016666667 seconds
						
			wnd.clear(sf::Color::Blue);

			// render every frame update only
			if (repaint)
			{
				// render(wnd);
			}
			wnd.display();
		}
		else
		{
			frameTimer.restart();
			deltaTime = sf::Time::Zero;
		}

	}


	return 0;
}

// sf::RenderTexture map;
// map.create(size);
// map.clear();
// map.draw(tilemappedLevelLayers);
// map.display();

// const sf::Texture& textureBG = map.getTexture();