#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>

int main()
{
	sf::RenderWindow wnd{ sf::VideoMode(1024,576), "ECS_Architecture" };
	ImGui::SFML::Init(wnd);
	
	bool focus = true;
	wnd.setVerticalSyncEnabled(true);

	while (wnd.isOpen())
	{
		wnd.setPosition(sf::Vector2i(450, 300));
		focus = wnd.hasFocus();
		wnd.setSize({ 1024U, 576U });
		
		if (focus)
		{
			sf::Event event;
			while (wnd.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					wnd.close();
			}
			wnd.clear(sf::Color::Blue);

			wnd.display();
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