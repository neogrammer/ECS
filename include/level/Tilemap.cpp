#include "Tilemap.hpp"


Tilemap::Tilemap(sf::Texture& l_texSheet, std::vector<int>& l_tiles, int l_pitch, int l_tileSize, int l_mapPitch)
	: tex{ l_texSheet }
	, tiles{}
	, tileset{}
	, numTiles{(int)((l_texSheet.getSize().y / l_tileSize) * l_pitch) }
	, sheetCols{l_pitch}
	, mapCols{l_mapPitch}
	, rows{(int)(l_tiles.size() / l_mapPitch) }
	, tw{l_tileSize}
	, th{l_tileSize}
{
	int sheetRows = numTiles / sheetCols;
	int mapRows = (int)(l_tiles.size() / l_mapPitch);

	tiles.clear();
	tileset.clear();

	//if (l_level == "intro")
	//{

	//	numTiles = 144;
	//    cols= 16;
	// 	rows= 9;
	//	tw= 64;
	//	th= 64;

	//	int texRows = 15;
	//	int texCols = 32;
	//	
	//	//m_tiles.clear();


		//m_tiles.reserve(144);

		tileset.reserve(sheetCols * sheetRows);
		for (int y  = 0; y < sheetRows; y++)
		{
			for (int x = 0; x < l_pitch; x++)
			{
				size_t index = size_t(y * l_pitch + x);
				sf::IntRect rect = { {x * tw, y * th}, {tw, th} };
				tileset.push_back(rect);
			}
		}
		tileset.shrink_to_fit();


		tiles.reserve(mapRows * l_mapPitch);
		for (int y = 0; y < mapRows; y++)
		{
			for (int x = 0; x < mapCols; x++)
			{
				size_t index = size_t(y * mapCols + x);
				size_t tileIndex = l_tiles.at(index);
				if (tileIndex != 64) {
					sf::IntRect tmpRect = tileset.at(tileIndex);
					Vec2 tmpPos = Vec2(x * tw, y * th);
					tiles.push_back(std::make_shared<TileObj>( tex,tmpRect,tmpPos ));
				}
				//	auto e = l_eMgr.addEntity(Vec2((float)tw,(float)th),"tile", { {texRect.left,texRect.top},{texRect.width,texRect.height} }, "Tileset1", Vec2(x * tw, y * th));
				//	e->addComponent<cRigidBody>(false, Vec2(texRect.width, texRect.height), Vec2(0, 0), Vec2(e->cMgr.getPosition().x, e->cMgr.getPosition().y));
				//	m_tiles.push_back(e);
				
			}
		}
		tiles.shrink_to_fit();
		//l_eMgr.update(0.016666667);
}


TileObj& Tilemap::tile(int l_index)
{
	return *tiles[l_index];
}

std::vector<std::shared_ptr<TileObj>>& Tilemap::getTiles()
{
	return tiles;
}

void Tilemap::render(sf::RenderWindow& l_wnd)
{
	for (auto& t : tiles)
	{
		t->render(l_wnd);
	}
}

