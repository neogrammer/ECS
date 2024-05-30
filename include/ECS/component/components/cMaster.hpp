#ifndef MASTER_HPP__
#define MASTER_HPP__
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <SFML/Graphics/Rect.hpp>
#include "../Component.hpp"
#include "../../../util/Vec2.hpp"
#include "../../../core/Config.hpp"
#include "../../../util/EntStates.hpp"
#include "../../../util/BBox.hpp"

class Entity;


class cMaster : public Component
{
	friend class Entity;

	EntState m_state;
	Entity& m_owner;
	sf::Time m_dt{sf::Time::Zero};


	void processInput();
	void update(sf::Time l_dt);
	void render(sf::RenderWindow& l_wnd);

	void setFrame(sf::IntRect l_frame);
	// every entity is a game object in the universe with locale, and a physical description such as a sprite image texture, texture rect
	// velocity, size of the sprite frame with the handle anchor at it's center and position.  with functions to update these qualities if the 
	// entity has them components, otherwise those properties are ignored by the game, as well as functios to get the leftRop and bottomRight
	// coords in world space as well as its position in the center, in world space.  The origin however is the center.x - leftTop.x etc..
	sf::Sprite m_spr{};
	Vec2 m_prevPos{0.f,0.f };
	Vec2 m_velocity{0.f,0.f};

	std::map<Config::Textures, BBox> m_bbox{};

	Config::Textures m_currTex;
	std::map<Config::Textures, sf::Texture*> m_texMap{};
	std::vector<std::string> m_texStrVec{};
	// may change size with each texture, but all in that texturesheet are uniform size in case of animation component is added
	std::vector<sf::IntRect> m_texFrameRect{};

	//std::map<std::string, Config::Textures> m_texMap;


public:
	cMaster() = delete;
	cMaster(Vec2 l_bboxSize, Entity& l_owner, sf::IntRect l_texFrame, std::string l_texName, Vec2 l_pos = Vec2(0.f,0.f));
	~cMaster() override final;
	cMaster(const cMaster&) = delete;
	cMaster& operator=(const cMaster&) = delete;
	cMaster(cMaster&&) = delete;
	cMaster& operator=(cMaster&&) = delete;


	//  bounding box functions
	Vec2 center();
	float x1();
	float x2();
	float y1();
	float y2();
	const BBox& bbox();
	float dt();

	// sprite physics functions
	sf::Sprite& spr();
	Vec2& prevPos();
	Vec2& velocity();
	Vec2 getSize();
	
	
	EntState getState();
	void setState(EntState l_state);
	void setPosition(Vec2 l_pos);
	Vec2 getPosition();

	void move(Vec2 l_offset);
	void setOrigin(Vec2 l_orig);
	void addTexture(std::string l_texName, Vec2 l_frameSize, bool setCurrent = false);
	// looks string up in the parallel vectors to update the entities m_spr.textureRect
	void setCurrentTex(std::string l_tex);
};

#endif