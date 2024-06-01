#include "GameObj.hpp"

int GameObj::m_numObjects = 0;
int GameObj::m_numAlive = 0;

bool GameObj::operator==(const GameObj& b)
{
	if (this == &b)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int GameObj::getNumObjects()
{
	return GameObj::numObjects();
}

const sf::FloatRect GameObj::getBBox()
{
	sf::FloatRect r = sf::FloatRect(this->getCenter().x - m_aabb.halfSize.x, this->getCenter().y - m_aabb.halfSize.y, m_aabb.size.x, m_aabb.size.y);
	return r;
}
Vec2 GameObj::getCenter()
{
	return Vec2(this->getPosition().x + (float)m_spr.getTextureRect().width / 2.f, this->getPosition().y + (float)m_spr.getTextureRect().height / 2.f);
}

float GameObj::aabbHW()
{
	return m_aabb.halfSize.x;
}

float GameObj::aabbHH()
{
	return m_aabb.halfSize.y;
}

const Vec2 GameObj::getPosition()
{
	return Vec2(m_spr.getPosition().x, m_spr.getPosition().y);
}
void GameObj::setPosition(Vec2 l_position)
{
	m_spr.setPosition(sf::Vector2f(l_position.x, l_position.y));
}
void GameObj::move(Vec2 l_displacement)
{
	m_spr.move(sf::Vector2f(l_displacement.x, l_displacement.y));
}
void GameObj::setTexRect(sf::IntRect l_texRect)
{
	m_spr.setTextureRect(l_texRect);
}
void GameObj::setTex(sf::Texture& l_tex, sf::IntRect l_texRect)
{
	m_spr.setTexture(l_tex);
	m_spr.setTextureRect(l_texRect);
}
sf::IntRect GameObj::getTexRect()
{
	return m_spr.getTextureRect();
}
int GameObj::getId()
{
	return id();
}
void GameObj::setId(int l_id)
{
	m_id = l_id;
}
const std::string& GameObj::getTag()
{
	return tag();
	// TODO: insert return statement here
}
void GameObj::setTag(const std::string& l_tag)
{
	m_tag = l_tag;
}

sf::Sprite& GameObj::getSprite()
{
	return spr();
}

int GameObj::id()
{
	return m_id;
}

std::string& GameObj::tag()
{
	return m_tag;
	// TODO: insert return statement here
}

sf::Sprite& GameObj::spr()
{
	return m_spr;
}

BBox& GameObj::aabb()
{
	return m_aabb;
}

int GameObj::numObjects()
{
	return GameObj::m_numObjects;
}

GameObj::GameObj(sf::Texture& l_tex,const std::string& l_tag, const sf::IntRect& l_texRect,const Vec2& l_aabbSize, const Vec2& l_pos)
	: m_spr{}, m_id{ GameObj::m_numObjects++ }, m_tag{ l_tag }, m_aabb{ {l_aabbSize} , {l_aabbSize / 2.f} }
{
	m_spr.setTexture(l_tex);
	m_spr.setPosition(sf::Vector2f(l_pos.x, l_pos.y));
	
	if (l_texRect == sf::IntRect{ {0, 0 }, { 0,0 } })
	{
		m_spr.setTextureRect({ sf::Vector2i(0,0), sf::Vector2i(m_spr.getTexture()->getSize()) });
		if (m_aabb.size == Vec2(0.f, 0.f))
		{
			m_aabb.size = Vec2(m_spr.getTextureRect().width, m_spr.getTextureRect().height);
			m_aabb.halfSize = m_aabb.size / 2.f;
		}
	}
	else
	{
		m_spr.setTextureRect(l_texRect);
		if (m_aabb.size == Vec2(0.f, 0.f))
		{
			m_aabb.size = Vec2(l_texRect.width, l_texRect.height);
			m_aabb.halfSize = m_aabb.size / 2.f;
		}
	}

	++GameObj::m_numAlive;


	
}

GameObj::~GameObj()
{
	--GameObj::m_numAlive;
}

GameObj::GameObj(const GameObj& o)
	: m_spr{ sf::Sprite{} }, m_id{ GameObj::m_numObjects++ }, m_tag{ "" }, m_aabb{ {0,0} , {0,0} }
{
	m_spr.setTexture(*o.m_spr.getTexture());
	m_spr.setPosition(o.m_spr.getPosition());
	m_spr.setScale(o.m_spr.getScale());
	m_spr.setTextureRect(o.m_spr.getTextureRect());
	m_spr.setOrigin(o.m_spr.getOrigin());
	m_spr.setColor(o.m_spr.getColor());
	m_spr.setRotation(o.m_spr.getRotation());

	
    ++GameObj::m_numAlive;

	m_tag = o.m_tag;

	m_aabb.halfSize = o.m_aabb.halfSize;
	m_aabb.size = o.m_aabb.size;
}

GameObj& GameObj::operator=(const GameObj& o)
{
	this->m_spr = o.m_spr;
	this->m_spr.setTexture(*o.m_spr.getTexture());
	this->m_tag = o.m_tag;
	this->m_aabb = o.m_aabb;

	m_id = GameObj::m_numObjects++;
	++GameObj::m_numAlive;

	return *this;
}

GameObj::GameObj(GameObj&& o)
{
	const sf::Texture* tex = o.m_spr.getTexture();
	this->m_spr = std::move(o.m_spr);
	this->m_spr.setTexture(*tex);
	this->m_aabb = std::move(o.m_aabb);
	this->m_id = std::move(o.m_id);
	this->m_tag = std::move(o.m_tag);
}

GameObj& GameObj::operator=(GameObj&& o)
{
	const sf::Texture* tex = o.m_spr.getTexture();
	this->m_spr = std::move(o.m_spr);
	this->m_spr.setTexture(*tex);
	this->m_aabb = std::move(o.m_aabb);
	this->m_id = std::move(o.m_id);
	this->m_tag = std::move(o.m_tag);

	return *this;
}
