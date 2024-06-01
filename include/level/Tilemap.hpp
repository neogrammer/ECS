#ifndef TILEMAP_H__
#define TILEMAP_H__
#include <vector>
#include <memory>
#include <utility>
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../core/Config.hpp"

class Tilemap
{
		
public:
	int numTiles;
	int cols;
	int rows;
	int tw;
	int th;
	Tilemap() = delete;
	explicit Tilemap(const std::string& l_level);
	~Tilemap() = default;

	void draw(sf::RenderWindow& l_wnd);

	

};

#endif