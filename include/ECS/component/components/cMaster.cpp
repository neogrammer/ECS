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


cMaster::cMaster(Entity& l_owner, sf::IntRect l_texFrame, std::string l_texName, Vec2 l_pos)
	: Component{}, m_state{EntState::NOT_ANIMATED}, m_owner{l_owner}
	, m_dt{ sf::Time::Zero }
	, m_spr{}, m_texMap{}
	, m_texStrVec{}, m_texFrameRect{}
{
	auto name = Config::texNamelookup[l_texName];

	// these remain size of 0 until an animation(or bundle of animations) is(are) loaded by file 
	m_texMap.clear();
	m_texStrVec.clear();
	m_texFrameRect.clear();
	//m_texStrVec.push_back(l_texName);
	m_spr.setTexture(Config::textures.get((int)name));
	m_spr.setTextureRect(l_texFrame);
	// update this when switching animations if the texture changes
	m_spr.setOrigin({ l_texFrame.width / 2.f, l_texFrame.width / 2.f });
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

	
	// if has rigidbody component run movement logic
	if (m_owner.hasComponent<cRigidBody>())
	{
		if (m_owner.hasComponent<cGravity>())
		{
			m_owner.getComponent<cRigidBody>().vel.y += m_owner.getComponent<cGravity>().magnitude * l_dt.asSeconds();
		}
		m_owner.getComponent<cRigidBody>().update(m_dt);
		



		//Collision section
		if (m_owner.m_tag == "player")
		{
			auto& tiles = m_owner.eMgr.getEntities("tile");
			
			//check collsions with this entity m_owner, and the tiles
			// using their RigidBody Components
			auto& playerBody = m_owner.getComponent<cRigidBody>();
			
			for (auto& tile : tiles)
			{
				auto& tileBody = tile->getComponent<cRigidBody>();

				Vec2 overlap{ -1, -1 }; // start off at no overlap
				if (Physics::isColliding(playerBody, tileBody, overlap))   // if true, then overlap is the overlap passed back
				{
					playerBody.center.y -= overlap.y;
					playerBody.vel.y = 0.f;

				//	if (m_owner.getComponent<cAnimation>().currAnimation->name() == "JumpLeft")
				//	{
				//		if (playerBody.vel.x < 0.1f)
				//			cAnimation::changeAnimation(m_owner, "RunLeft");
				//		else if (playerBody.vel.x > 0.0f)
				//			cAnimation::changeAnimation(m_owner, "RunRight");
				//		else
				//			cAnimation::changeAnimation(m_owner, "IdleLeft");
				//	}
				//	else if (m_owner.getComponent<cAnimation>().currAnimation->name() == "JumpRight")
				//	{
				//		if (playerBody.vel.x > 0.1f)
				//			cAnimation::changeAnimation(m_owner, "RunRight");
				//		else if (playerBody.vel.x < 0.0f)
				//			cAnimation::changeAnimation(m_owner, "RunLeft");
				//		else
				//			cAnimation::changeAnimation(m_owner, "IdleRight");
				//	}
				//	else
				//	{
				//		if (playerBody.vel.x > 0.0f)
				//		{
				//			if (m_owner.getComponent<cAnimation>().currAnimation->name() != "RunRight")
				//				cAnimation::changeAnimation(m_owner, "RunRight");
				//		}
				//		else if (playerBody.vel.x < 0.0f)
				//		{
				//			if (m_owner.getComponent<cAnimation>().currAnimation->name() != "RunLeft")
				//				cAnimation::changeAnimation(m_owner, "RunLeft");
				//		}
				//		else
				//		{
				//			if (m_owner.getComponent<cAnimation>().currAnimation->name() == "RunRight")
				//			{
				//				cAnimation::changeAnimation(m_owner, "IdleRight");
				//			}
				//			else if (m_owner.getComponent<cAnimation>().currAnimation->name() == "RunLeft")
				//			{
				//				cAnimation::changeAnimation(m_owner, "IdleLeft");
				//			}
				//		}
				//	}
				//	
				//}
				//else
				//{
				//	if (m_owner.getComponent<cRigidBody>().vel.y > 20.f)
				//	{
				//		if (m_owner.getComponent<cRigidBody>().vel.x < 0.0f)
				//		{
				//			cAnimation::changeAnimation(m_owner, "JumpLeft");
				//		}
				//		else if (m_owner.getComponent<cRigidBody>().vel.x > 0.0f)
				//		{
				//			cAnimation::changeAnimation(m_owner, "JumpRight");
				//		}
				//		else
				//		{
				//			if (m_owner.getComponent<cAnimation>().currAnimation->name() == "RunRight" || m_owner.getComponent<cAnimation>().currAnimation->name() == "IdleRight")
				//			{
				//				cAnimation::changeAnimation(m_owner, "JumpRight");
				//			}
				//			else if (m_owner.getComponent<cAnimation>().currAnimation->name() == "RunLeft" || m_owner.getComponent<cAnimation>().currAnimation->name() == "IdleLeft")
				//			{
				//				cAnimation::changeAnimation(m_owner, "JumpLeft");
				//			}
				//		}
				//		// check if player is shooting, if so shoot left or right depending on velocity or current jump animation direction
				//	}
				//	else if (m_owner.getComponent<cRigidBody>().vel.y < -20.f)
				//	{
				//		if (m_owner.getComponent<cRigidBody>().vel.x < 0.0f)
				//		{
				//			cAnimation::changeAnimation(m_owner, "JumpLeft");
				//		}
				//		else if (m_owner.getComponent<cRigidBody>().vel.x > 0.0f)
				//		{
				//			cAnimation::changeAnimation(m_owner, "JumpRight");
				//		}
				//		else
				//		{
				//			if (m_owner.getComponent<cAnimation>().currAnimation->name() == "RunRight" || m_owner.getComponent<cAnimation>().currAnimation->name() == "IdleRight")
				//			{
				//				cAnimation::changeAnimation(m_owner, "JumpRight");
				//			}
				//			else if (m_owner.getComponent<cAnimation>().currAnimation->name() == "RunLeft" || m_owner.getComponent<cAnimation>().currAnimation->name() == "IdleLeft")
				//			{
				//				cAnimation::changeAnimation(m_owner, "JumpLeft");
				//			}
				//		}

				//		// check if player is shooting, if so shoot left or right depending on velocity or current jump animation direction
				//	}
				//	else
				//	{
				//		// if player is shooting, if playeranim is running or idle left, runshootleft or shootleft depending on vel.x, same for right
				//	}
					//  user is on the ground, if the player is pressing the shoot button, change animation to shoot if not already
					//  if user pressed the jump button, here set the velocity.y of the player to -value and , update center.y  and if not already set to jump anim an
					//  set player to jumping == true;
				}
				
			}
			
		}

		// now position the owner to this location
		m_spr.setPosition(m_owner.getComponent<cRigidBody>().center.x, m_owner.getComponent<cRigidBody>().center.y);
	}

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


