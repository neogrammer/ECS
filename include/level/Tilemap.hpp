#ifndef TILEMAP_H__
#define TILEMAP_H__
#include <vector>
#include <memory>
#include <utility>
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../core/Config.hpp"
class Entity;
class Tilemap
{
		
public:
	std::vector<std::shared_ptr<Entity> > m_tiles;
	int numTiles;
	int cols;
	int rows;
	int tw;
	int th;
	Tilemap() = delete;
	explicit Tilemap(std::vector<std::shared_ptr<Entity> > l_tiles);
	~Tilemap() = default;

	void draw(sf::RenderWindow& l_wnd);

	std::vector<std::shared_ptr<Entity> >& getTiles();

};

#endif