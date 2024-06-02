#include <system/systems/CollisionSystem.hpp>
#include <iostream>

CollisionSystem::CollisionSystem(PlayState& l_gameState, sf::RenderWindow& l_wnd, sf::Time& l_dt) 
	: System(l_wnd, l_dt)
	, gameState{l_gameState}
{
}

CollisionSystem::~CollisionSystem()
{

}

void CollisionSystem::update()
{
	auto* g = dynamic_cast<PlayState*>(&gameState);
	// CollisionManager->CheckPlayerToTileMap(player, tmap);
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// store the current frame player's position and velocity, then update those values based on physics
	///////////////////////////////////////////////////////////////////////////////////////////////////

	rect r = { {g->player.getCenter().x - g->player.aabbHW(), g->player.getCenter().y - g->player.aabbHH()},{ g->player.getBBox().width, g->player.getBBox().height} };
	r.vel = g->player.getVelocity();
	//// contact point, contact notmal, t2 - hit dist along ray to object colliding with, center point to collision point
	float t2 = 0, min_t = INFINITY;
	Vec2 cp2, cn2;
	std::vector<std::pair<int, float>> z;
	//// Work out collision point, add it to vector along with rect ID
	auto& ts = g->tmap->getTiles();
	for (int i = 0; i < g->tmap->getTiles().size(); i++) {
		rect r2 = { {ts[i]->getCenter().x - ts[i]->aabbHW(), ts[i]->getCenter().y - ts[i]->aabbHH()},{ts[i]->getBBox().width,ts[i]->getBBox().height} };
		if (Physics::DynamicRectVsRect(&r, g->m_deltaTime.asSeconds(), r2, cp2, cn2, t2))
		{
			z.push_back({ i, t2 });
		}
	}
	// Do the sort
	std::sort(z.begin(), z.end(), [](const std::pair<int, float>& a, const std::pair<int, float>& b) { return a.second < b.second; });
	// Now resolve the collision in correct order 
	for (auto& j : z) {
		rect r2 = { {ts[j.first]->getCenter().x - ts[j.first]->aabbHW(), ts[j.first]->getCenter().y - ts[j.first]->aabbHH()},
			{ ts[j.first]->getBBox().width,ts[j.first]->getBBox().height} };
		if (Physics::ResolveDynamicRectVsRect(&r, g->m_deltaTime.asSeconds(), &r2))
		{
			if (r.contact.at(0) != nullptr)
			{


			}
			if (r.contact.at(1) != nullptr)
			{
				
				r.vel.y = 0.f;
				g->player.getVelocity().y = 0.f;
				g->player.collidedWithGround() = true;

			}
			if (r.contact.at(2) != nullptr)
			{
		
				r.vel.y = 0.f;
				g->player.getVelocity().y = 0.f;
				g->player.collidedWithGround() = true;

			}
		    if (r.contact.at(3) != nullptr)
			{


			}
		}
	}
	// UPdate the player rectangles position, with its modified velocity
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	///   Finish up by setting the player's info that was passed in and changed, back into that player's info
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	g->player.getVelocity() = r.vel;

}

// not used
void CollisionSystem::draw()
{
	
}
