#include "include/core/GameEngine.hpp"

int main()
{
	GameEngine game;

	game.mainLoop();

	return 0;
}

// sf::RenderTexture map;
// map.create(size);
// map.clear();
// map.draw(tilemappedLevelLayers);
// map.display();

// const sf::Texture& textureBG = map.getTexture();