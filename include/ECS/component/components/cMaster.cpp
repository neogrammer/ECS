#include "cMaster.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include "../../../ECS/EntityManager.hpp"
#include "../../../util/Physics.hpp"
class Entity;
// for static functions on this page only
#define RigidBody_ e.getComponent<cRigidBody>()
#define Animation_ e.getComponent<cAnimation>() 
#define Lifespan_ e.getComponent<cLifespan>() 
#define Gravity_ e.getComponent<cGravity>() 


cMaster::cMaster(Vec2 l_bboxSize, Entity& l_owner, sf::IntRect l_texFrame, std::string l_texName, Vec2 l_pos)
	: Component{}, m_state{ EntState::NOT_ANIMATED }, m_owner{ l_owner }
	, m_dt{ sf::Time::Zero }
	, m_spr{}, m_texMap{}
	, m_texStrVec{}, m_texFrameRect{}
	, m_bbox{}
	, m_velocity{ 0.f,0.f }
	, m_prevPos{ l_pos }
{
	auto name = Config::texNamelookup[l_texName];

	// these remain size of 0 until an animation(or bundle of animations) is(are) loaded by file 
	m_texMap.clear();
	m_texStrVec.clear();
	m_texFrameRect.clear();
	//m_texStrVec.push_back(l_texName);
	m_spr.setTexture(Config::textures.get((int)name));
	m_bbox.insert(std::pair(name, BBox{ l_bboxSize, l_bboxSize / 2.f } ));
	m_currTex = name;
	m_spr.setTextureRect(l_texFrame);
	// stays put until a rigid body is added or manually changed by the master component
	m_spr.setPosition({ l_pos.x,l_pos.y });
 }


cMaster::~cMaster()
{
	for (auto& t: m_texMap)
	{
		t.second = nullptr;
	}
}

void cMaster::setCurrentTex(std::string l_tex)
{
	if (std::any_of(m_texStrVec.begin(), m_texStrVec.end(), [&](std::string s) {return s == l_tex; }))
	{
		m_spr.setTexture(*m_texMap[Config::texNamelookup[l_tex]]);
		m_currTex = Config::texNamelookup[l_tex];
		for (int i = 0; i < m_texStrVec.size(); i++)
		{
			if (m_texStrVec[i] == l_tex)
			{
				m_spr.setTextureRect(m_texFrameRect[i]);
				break;
			}
		}
		
	}
	else
	{ 
		std::cout << "No texture prepared in entity::ID " << m_owner.id() << " named " << l_tex << std::endl;
	}
}

void cMaster::setFrame(sf::IntRect l_frame)
{
	m_spr.setTextureRect(l_frame);
}



Vec2 cMaster::getSize()
{
	return Vec2(m_spr.getTextureRect().width, m_spr.getTextureRect().height);
}

EntState cMaster::getState()
{
	return m_state;
}

void cMaster::setState(EntState l_state)
{
	m_state = l_state;
}

void cMaster::setPosition(Vec2 l_pos)
{
	m_spr.setPosition(sf::Vector2f(l_pos.x,l_pos.y));
}

Vec2 cMaster::getPosition()
{
	return Vec2(m_spr.getPosition().x,m_spr.getPosition().y);
}

void cMaster::move(Vec2 l_offset)
{
	Vec2 off = l_offset * m_dt.asSeconds();
	m_spr.move({ off.x, off.y });
}

void cMaster::setOrigin(Vec2 l_orig)
{
	m_spr.setOrigin(l_orig.x, l_orig.y);
}

void cMaster::addTexture(std::string l_texName, Vec2 l_frameSize, bool setCurrent)
{
	if (setCurrent == false)
	{
		if (m_texMap.find(Config::texNamelookup[l_texName]) == m_texMap.end())
		{
			m_texMap.insert(std::pair{ Config::texNamelookup[l_texName], &Config::textures.get((int)Config::texNamelookup[l_texName]) });
			m_texStrVec.push_back(l_texName);
			m_texFrameRect.push_back(sf::IntRect({0, 0}, {(int)l_frameSize.x, (int)l_frameSize.y}));
			m_bbox.insert(std::pair(Config::texNamelookup[l_texName], BBox{ {l_frameSize},{l_frameSize / 2.f} }));
		}
		else
		{
			//std::cout << " add texture failed for entity::ID " << m_owner.id() << " because texture " << l_texName << " already is in the container m_texMap!" << std::endl;
		}
	}
	else
	{
		std::cout << "not yet implemented (addTexture where setCurrent == true)" << std::endl;
	}
	return;
}


void cMaster::processInput()
{
	std::cout << "not yet implemented (processInput)" << std::endl;
}

void cMaster::update(sf::Time l_dt)
{
	m_dt = l_dt;

	if (m_owner.hasComponent<cGravity>())
	{
		velocity().y += m_owner.getComponent<cGravity>().magnitude;
		move(velocity());
	}

	if (m_owner.m_tag == "player")
	{
		Physics::ResolveCollisions(m_owner, m_owner.eMgr.getEntities("tile"));
	}
	
	//// if has rigidbody component run movement logic
	//if (m_owner.hasComponent<cRigidBody>())
	//{
	//	if (m_owner.hasComponent<cGravity>())
	//	{
	//		m_owner.getComponent<cRigidBody>().vel.y += m_owner.getComponent<cGravity>().magnitude * l_dt.asSeconds();
	//	}
	//	m_owner.getComponent<cRigidBody>().update(m_dt);
	//	



	//	//Collision section
	//	if (m_owner.m_tag == "player")
	//	{
	//		auto& tiles = m_owner.eMgr.getEntities("tile");
	//		
	//		//check collsions with this entity m_owner, and the tiles
	//		// using their RigidBody Components
	//		auto& playerBody = m_owner.getComponent<cRigidBody>();
	//		


	//		for (auto& tile : tiles)
	//		{
	//			auto& tileBody = tile->getComponent<cRigidBody>();

	//			Vec2 overlap{ -1, -1 }; // start off at no overlap
	//			overlap = Physics::RectVsRect(m_owner, *tile);
	//			if(overlap.x > 0.f && overlap.y > 0.f)
	//			//if (Physics::isColliding(playerBody, tileBody, overlap))   // if true, then overlap is the overlap passed back
	//			//{
	//			{
	//				playerBody.center.y -= overlap.y;
	//				playerBody.vel.y = 0.f;
	//			}
	//		}
	//		
	//	}
		//Physics::RectVsRect(Entity & a, Entity & b)
		//{
		//	Vec2 overlap(-1.f, -1.f);

		//	if (a.cMgr.x1() < b.cMgr.x2()
		//		&& b.cMgr.x1() < a.cMgr.x2()
		//		&& a.cMgr.y1() < b.cMgr.y2()
		//		&& b.cMgr.y1() < a.cMgr.y2())
		//	{
		//		//collision, return the overlap
		//		float dx = abs(b.cMgr.center().x - a.cMgr.center().x);
		//		float dy = abs(b.cMgr.center().y - a.cMgr.center().y);

		//		overlap.x = a.cMgr.bbox().halfSize.x + b.cMgr.bbox().halfSize.x - dx;
		//		overlap.y = a.cMgr.bbox().halfSize.y + b.cMgr.bbox().halfSize.y - dy;
		//	}

		//	return overlap;
		//}

		//Vec2 Physics::PrevOverlap(Entity & a, Entity & b)
		//{
		//	Vec2 a_offset = Vec2(a.cMgr.prevPos().x * a.cMgr.dt() - a.cMgr.getPosition().x * a.cMgr.dt(), a.cMgr.prevPos().y * a.cMgr.dt() - a.cMgr.getPosition().y * a.cMgr.dt());
		//	Vec2 b_offset = Vec2(b.cMgr.prevPos().x * b.cMgr.dt() - b.cMgr.getPosition().x * b.cMgr.dt(), b.cMgr.prevPos().y * b.cMgr.dt() - b.cMgr.getPosition().y * b.cMgr.dt());

		//	//collision, return the overlap
		//	float dx = abs((b.cMgr.center().x + b_offset.x) - (a.cMgr.center().x + a_offset.x));
		//	float dy = abs((b.cMgr.center().y + b_offset.y) - (a.cMgr.center().y + a_offset.y));

		//	return Vec2(a.cMgr.bbox().halfSize.x + b.cMgr.bbox().halfSize.x - dx, a.cMgr.bbox().halfSize.y + b.cMgr.bbox().halfSize.y - dy);

		//}
		//void Physics::ResolveCollisions(Entity & a, EntityVec & eVec)
		//{
		//	// Entity A should have already accepted input this frame and updated the velocity, AND updated the sprites position

		//	for (auto& e : eVec)
		//	{
		//		Vec2 overlap = RectVsRect(a, *e);


		//		Vec2 norm = a.cMgr.prevPos() - a.cMgr.getPosition();
		//		norm = norm / Vec2(abs(norm.x), abs(norm.y));

		//		if (overlap.x > 0 && overlap.y > 0) // if not, check next entity for collision
		//		{
		//			// collision, get over lap from last frame
		//			Vec2 previousOlap = PrevOverlap(a, *e);

		//			if (previousOlap.x <= 0.f && previousOlap.y <= 0.f)
		//			{
		//				// no overlap last frame, resolve on the greatest dimension of the current overlap
		//				if (overlap.x > overlap.y)
		//				{
		//					// resolve on x
		//					a.cMgr.move(Vec2(norm.x * overlap.x, 0.0f));
		//					a.cMgr.velocity().x = 0.f;
		//				}
		//				else
		//				{
		//					//resolve on y
		//					a.cMgr.move(Vec2(0.f, norm.y * overlap.y));
		//					a.cMgr.velocity().y = 0.f;
		//				}
		//			}
		//			else if (previousOlap.x <= 0.f && previousOlap.y > 0.f)
		//			{
		//				// resolve on x
		//				a.cMgr.move(Vec2(norm.x * overlap.x, 0.0f));
		//				a.cMgr.velocity().x = 0.f;
		//			}
		//			else if (previousOlap.y <= 0.f && previousOlap.x > 0.f)
		//			{
		//				//resolve on y
		//				a.cMgr.move(Vec2(0.f, norm.y * overlap.y));
		//				a.cMgr.velocity().y = 0.f;
		//			}
		//			else
		//			{
		//				// change nothing ? maybe
		//			}
		//		}

			//}
			// 
			

			// done checking for Entity A, the player most likely, should work against tiles and other obstacles
			// sprite has been moved accordingly and velocity updated to stop moving in the collided direction, now animate then render, then update the previous position

		// now position the owner to this location
	//	m_spr.setPosition(m_owner.getComponent<cRigidBody>().center.x, m_owner.getComponent<cRigidBody>().center.y);
	//}

	// if has animation component run animation logic
	if (m_owner.hasComponent<cAnimation>())
	{
		

		auto& currAnim = m_owner.getComponent<cAnimation>().currAnimation->getName();
		auto& animTex = m_owner.getComponent<cAnimation>().animTextureMap[currAnim];
		if (m_spr.getTexture() != NULL)
		{
			if (m_spr.getTexture() != &(Config::textures.get((int)Config::texNamelookup[animTex])))
			{
				m_spr.setTexture(Config::textures.get((int)Config::texNamelookup[animTex]));
			}
		}
		else
		{
			// m_spr texture is NULL, so lets assign it to the one in the owners animation component's texture map connected to by that entitys current animation
			// thus it should definitely exist if this code is ran, where the entity in question indeed has a animation component,where at least one texture and animation is required
			// or this just wont be ran at all
			m_spr.setTexture(Config::textures.get((int)Config::texNamelookup[animTex]));
		}
		

		// NOT 100% sure if this should go at the top of the function or not
		// now animate the animation accordingly
		m_owner.getComponent<cAnimation>().update(m_dt);

		
		// now update the texture and the tex rect since we have checked for the correct texture for this animation currently running and updated the frame accordingly
		// because if the animation changed to a different one using a different texture it shoul all be connected and reader to sync up to the entitys sprite now
		// for rendering		
		m_spr.setTextureRect(m_owner.getComponent<cAnimation>().currAnimation->currFrame());

	}

	// else look pretty with its current static tex an tex rect
}

void cMaster::render(sf::RenderWindow& l_wnd)
{
	// everything should be set to be rendered
	l_wnd.draw(m_spr);

	m_prevPos = Vec2(m_spr.getPosition().x, m_spr.getPosition().y);
}



Vec2 cRigidBody::topLeft(Entity& e) {
	return Vec2(RigidBody_.center - RigidBody_.halfSize);
};
Vec2 cRigidBody::bottomRight(Entity& e) {
	return Vec2(RigidBody_.center + RigidBody_.halfSize);
};


void cAnimation::setup(Entity& e, std::string l_filename) {
	if (!e.hasComponent<cAnimation>())
	{ 
		std::cout << "no animation component on entity::ID " << e.id() << std::endl;
		return;
	}
	std::ifstream iFile;
	iFile.open(l_filename);

	if (!iFile.is_open())
	{
		std::cout << "Animation File " << l_filename << " unable to be read in!" << std::endl;
	}
	else
	{
		int numTextures;
		int totalAnimations{ 0 };
		iFile >> numTextures;

		for (int i = 0; i < numTextures; i++)
		{
			std::string texName;
			iFile >> texName;
			int numAnimsInTexture;
			iFile >> numAnimsInTexture;
			
			for (int j = 0; j < numAnimsInTexture; j++)
			{
				std::string animName;
				iFile >> animName;
				Animation_.animTextureMap.insert(std::pair{ animName, texName });
				Animation_.animNames.push_back(animName);

				//file is open
				int sizex, sizey, numframes, cols, rows, startposx, startposy, framedelayMS;
				std::string looping, flippedH, flippedV;

				iFile >> sizex >> sizey >> numframes >> cols >> rows >> startposx >> startposy >> framedelayMS >> looping >> flippedH >> flippedV;
				e.cMgr.addTexture(texName, Vec2(sizex, sizey));

				const std::string str = animName;
				Animation_.animations.insert(std::pair{str, std::make_shared<Animation>(sf::Vector2i(sizex, sizey), str, numframes, cols, rows, sf::Vector2i{ startposx,startposy }, (float)framedelayMS / 1000.f, (looping == "true") ? true : false, (flippedH == "true") ? true : false, (flippedV == "true") ? true : false)});
				std::cout << "Animation " << animName << ": with properties: sizex: " << sizex << ", sizey: " << sizey << ", numFrames: " <<
					numframes << ", colsInAnim: " << cols << ", rowsInAnim: " << rows << ", startposx: " << startposx << ", startposy: " << ", framedelayMS: " <<
					framedelayMS << ", looping(0 == false, 1 == true): " << looping << ", flippedH: " << flippedH << ", flippedV: " << flippedV <<
					" ::: was added to Entity::ID " << e.id() << ", and has been linked to texture: " << texName << "\n";
				
			}
			totalAnimations += numAnimsInTexture;
		}
		
		iFile.close();

		std::cout << "Total Animations loaded: " << totalAnimations << ", using a total of " << numTextures << " textures that were loaded" << std::endl;
	}
	Animation_.wasSetupRan = true;
	cAnimation::changeAnimation(e, Animation_.animNames[0]);
	return;
}

void cAnimation::changeAnimation(Entity& e, std::string l_animName)
{
	if (!Animation_.wasSetupRan)
	{
		std::cout << "Entity::ID " << e.id() << " is changing animation, but setup was not ran on that entity's animation component yet! " << std::endl;
		return;
	}
	else
	{
		if (std::any_of(Animation_.animNames.begin(), Animation_.animNames.end(), [&](std::string s) {return s == l_animName; }) )
		{
			std::string texName = Animation_.animTextureMap[l_animName];
			e.cMgr.setCurrentTex(texName);
			Animation_.currAnimation = Animation_.animations[l_animName];
			Animation_.currAnimation->setCurrIdx(0);
		}
		else
		{ 
			std::cout << "anim name not found in collection of possible animation names within animation component on entity::ID " << e.id() << "!" << std::endl;
			return;
		}
	}
};

std::vector<std::string> cAnimation::getAnimNames(Entity& e)
{
	std::vector<std::string> animNames{};
	animNames.clear();
	if (!Animation_.wasSetupRan)
	{
		std::cout << "Entity::ID " << e.id() << " is being queried for all animation names, but setup was not ran on that entity's animation component yet! " << std::endl;
		return animNames;
	}
	else
	{
		for (auto& aName : Animation_.animNames)
		{
			animNames.push_back(aName);
		}
		return animNames;
	}
};

Vec2 cMaster::center()
{
	Vec2 c(Vec2(m_spr.getPosition().x, m_spr.getPosition().y) + (getSize() / 2.f));
	return c;
}

float cMaster::x1()
{
	return center().x - bbox().halfSize.x;
}

float cMaster::x2()
{
	return center().x + bbox().halfSize.x;
}

float cMaster::y1()
{
	return center().x - bbox().halfSize.y;
}

float cMaster::y2()
{
	return center().x + bbox().halfSize.y;
}

const BBox& cMaster::bbox()
{
	return m_bbox[m_currTex];
}

float cMaster::dt()
{
	return m_dt.asSeconds();
}

sf::Sprite& cMaster::spr()
{
	return m_spr;
}

Vec2& cMaster::prevPos()
{
	return m_prevPos;
}

Vec2& cMaster::velocity()
{
	return m_velocity;
}
