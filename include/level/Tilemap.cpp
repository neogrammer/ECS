#include "Tilemap.hpp"
#include "../ECS/Entity.hpp"
#include "../ECS/Factories.hpp"
#include "../ECS/EntityManager.hpp"
Tilemap::Tilemap(EntityManager& l_eMgr, const std::string& l_level)
	: m_tiles{}
	, numTiles{}
	, cols{}
	, rows{}
	, tw{}
	, th{}
{


	if (l_level == "intro")
	{

		numTiles = 144;
	    cols= 16;
	 	rows= 9;
		tw= 64;
		th= 64;

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
			 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1
		};

		for (int y = 0; y < rows; y++)
		{
			for (int x = 0; x < cols; x++)
			{
				size_t index = size_t(y * cols + x);
				int texIndex = level[index];
				sf::IntRect texRect = sf::IntRect(int(texIndex % texCols) * (int)tw, int(texIndex / texCols) * (int)th, (int)tw, (int)th);
				if (texIndex != 64)
				{
					auto e = l_eMgr.addEntity(Vec2((float)tw,(float)th),"tile", { {texRect.left,texRect.top},{texRect.width,texRect.height} }, "Tileset1", Vec2(x * tw, y * th));
					e->addComponent<cRigidBody>(false, Vec2(texRect.width, texRect.height), Vec2(0, 0), Vec2(e->cMgr.getPosition().x, e->cMgr.getPosition().y));
					m_tiles.push_back(e);
				}
			}
		}
		l_eMgr.update(0.016666667);
	}
}

void Tilemap::draw(sf::RenderWindow& l_wnd)
{
	for (auto& t : m_tiles)
	{
		t->render(l_wnd);
	}
}

std::vector<std::shared_ptr<Entity>>& Tilemap::getTiles()
{
	return m_tiles;
}


