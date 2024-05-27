#include "cMaster.hpp"
#include "../ECS/Entity.hpp"
cMaster::cMaster(Entity& l_owner, sf::IntRect l_texFrame, std::string l_texName, Vec2 l_pos)
	: Component{}, m_owner{l_owner}, m_dt{sf::Time::Zero}
	, m_spr{}, m_texMap{}, m_texStrVec{}, m_texFrameRect{}
{
	auto name = Config::texNamelookup[l_texName];

	m_texMap[name] = &Config::textures.get((int)name);
	m_texStrVec.clear();
	m_texFrameRect.clear();
	m_texStrVec.push_back(l_texName);
	m_texFrameRect.push_back(l_texFrame);
	m_spr.setTexture(*m_texMap[name]);
	m_spr.setTextureRect(l_texFrame);
	m_spr.setOrigin({ l_texFrame.width / 2.f, l_texFrame.width / 2.f });
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
}

void cMaster::setFrame(sf::IntRect l_frame)
{
}

void cMaster::setSize(Vec2 l_frameSize)
{
}

Vec2 cMaster::getSize()
{
	return Vec2();
}

void cMaster::setPosition(Vec2 l_pos)
{
}

Vec2 cMaster::getPosition()
{
	return Vec2();
}

void cMaster::move(Vec2 l_offset)
{
}

void cMaster::addTexture(std::string l_texName, sf::IntRect l_texFrame, bool setCurrent)
{
}


void cMaster::processInput()
{
}

void cMaster::update(sf::Time l_dt)
{
	m_dt = l_dt;
}

void cMaster::render(sf::RenderWindow& l_wnd)
{
}
