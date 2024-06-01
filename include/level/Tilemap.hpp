#ifndef TILEMAP_H__
#define TILEMAP_H__
#include <vector>
#include <memory>
#include <utility>
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../core/Config.hpp"
#include "gameObj/TileObj.hpp"

class Tilemap
{
	std::vector<std::shared_ptr<TileObj> > tiles;
	sf::Texture& tex;
public:
	std::vector<sf::IntRect> tileset;

	int numTiles;
	int sheetCols;
	int mapCols;
	int rows;
	int tw;
	int th;
	Tilemap() = delete;
	explicit Tilemap(sf::Texture& l_texSheet, std::vector<int>& l_tiles, int l_pitch, int l_tileSize, int l_mapPitch);
	~Tilemap() = default;

	TileObj& tile(int l_index);
	void render(sf::RenderWindow& l_wnd);
	std::vector<std::shared_ptr<TileObj>>& getTiles();
	

};

#endif