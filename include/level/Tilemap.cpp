#include "Tilemap.hpp"
#include "../ECS/Entity.hpp"
#include "../ECS/Factories.hpp"
Tilemap::Tilemap(std::vector<std::shared_ptr<Entity> > l_tiles)
	: m_tiles{}
	, numTiles{144}
	, cols{16}
	, rows{9}
	, tw{64}
	, th{64}
{
	cols = 16;
	rows = 9;
	int texRows = 15;
	int texCols = 32;
	m_tiles.clear();

	
	m_tiles.reserve(144);


		int level[144] = {
			64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
			64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
			64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
			64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
			64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
			64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
			64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
			64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
		};

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			size_t index = size_t(y * cols + x);
			int texIndex = level[index];
			sf::IntRect texRect = sf::IntRect(int(texIndex % texCols) * (int)tw, int(texIndex / texCols) * (int)th, (int)tw, (int)th);

			m_tiles.emplace_back(std::move(Make::Tile(l_tiles[index]->id(), "Tileset1", texRect, Vec2(x * tw, y * th), ((texIndex == 64) ? false : true) )));
			m_tiles.back()->getComponent<CShape>().sprite.setTexture(Config::textures.get((int)Config::Textures::Tileset1));
			m_tiles.back()->getComponent<CTransform>().pos = Vec2(x * tw + (tw/2), y * th + (tw / 2));
			m_tiles.back()->getComponent<CTransform>().prevPos = Vec2(x * tw + (tw / 2), y * th + (tw / 2));
			m_tiles.back()->getComponent<CShape>().sprite.setPosition({ Vec2(x * tw + (tw / 2), y * th + (tw / 2)).x, Vec2(x * tw + (tw / 2), y * th + (tw / 2)).y });

			l_tiles[index].reset();



		}
	}
	l_tiles.clear();


}

void Tilemap::draw(sf::RenderWindow& l_wnd)
{
	for (auto& t : m_tiles)
	{
		l_wnd.draw(t->getComponent<CShape>().sprite);
	}
}

std::vector<std::shared_ptr<Entity>>& Tilemap::getTiles()
{
	return m_tiles;
}


