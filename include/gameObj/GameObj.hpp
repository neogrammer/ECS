#ifndef GAMEOBJ_HPP__
#define GAMEOBJ_HPP__
#include <SFML/Graphics.hpp>
#include <util/Vec2.hpp>
#include <util/BBox.hpp>
#include <core/Config.hpp>
#include <string>
class GameObj
{

	int m_id{ -1 };
	std::string m_tag{ "" };
	sf::Sprite m_spr{};
	BBox m_aabb{ {2,2},{1,1} };
	static int m_numAlive;
	static int m_numObjects;
	Vec2 m_velocity{ 0.f,0.f };
protected:
	int id();
	std::string& tag();
	sf::Sprite& spr();
	BBox& aabb();
	static int numObjects();
	Vec2 vel();
public:
	GameObj(sf::Texture& l_tex, const std::string& l_tag,const sf::IntRect& l_texRect = sf::IntRect{ {0,0},{0,0} }, const Vec2& l_aabbSize = Vec2(0.f, 0.f), const Vec2& l_pos = Vec2(0.f, 0.f));
	virtual ~GameObj();

	GameObj(const GameObj& o);
	GameObj& operator=(const GameObj& o);
	GameObj(GameObj&& o) noexcept;
	GameObj& operator=(GameObj&& o) noexcept;
	bool operator==(const GameObj& b);

	Vec2& getVelocity();
	static int getNumObjects();
	const sf::FloatRect getBBox();
	Vec2 getCenter();
	float aabbHW();
	float aabbHH();

	const Vec2 getPosition();
	void setPosition(Vec2 l_position);
	void move(Vec2 l_displacement);

	void setTexRect(sf::IntRect l_texRect);
	void setTex(sf::Texture& l_tex, sf::IntRect l_texRect);
	sf::IntRect getTexRect();

	int getId();
	void setId(int l_id);
	const std::string& getTag();
	void setTag(const std::string& l_tag);
	sf::Sprite& getSprite();

	// this will call derived command queue for ai or process mapped input for users
	virtual void processInput() = 0;
	// update the obj in one call, as this will call animate and what not if its a part of this object down the line
	virtual void update(sf::Time l_dt) = 0;
	// render the properly updated obj
	virtual void render(sf::RenderWindow& l_wnd) = 0;
};

#endif