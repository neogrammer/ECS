#include "Anim.hpp"
#include <iostream>
void Anim::animate()
{
	if (++m_currIndex >= m_frames.size())
	{
		if (!m_looping)
		{
			m_currIndex = m_frames.size() - 1;
		}
		else
		{
			m_currIndex = 0;
		}
	}
	if (m_currIndex == m_frames.size() - 1)
	{
		m_onLastFrame = true;
	}
	else
	{
		m_onLastFrame = false;
	}
}

Anim::Anim()
	: Anim{{1,1}}
{
	// better call setup asap, or im gonna try reading from "Default" texture, whatever the hell that is
}

Anim::Anim( sf::Vector2i l_frameSize, const std::string& l_name, int l_numFrames, int l_cols, int l_rows, sf::Vector2i l_startPos, float l_frameDelay, bool l_looping, bool l_isFlippedH, bool l_isFlippedV)
	: m_frames {}, m_currIndex{ 0 }, m_frameDelayElapsed{ sf::Time::Zero }, m_frameDelay{ l_frameDelay }, m_looping{ l_looping }, m_isFlippedH{ l_isFlippedH }, m_isFlippedV{ l_isFlippedV }, m_name{ l_name }
	, m_onLastFrame{ false }
{
	m_frames.clear();

	for (int y = 0; y < l_rows; y++)
	{
		for (int x = 0; x < l_cols; x++)
		{
			m_frames.push_back(sf::IntRect(x*l_frameSize.x + l_startPos.x, y * l_frameSize.y + l_startPos.y, l_frameSize.x, l_frameSize.y));
		}
	}
	m_frameDelayElapsed = sf::Time::Zero;
}

Anim::~Anim()
{

}

const int Anim::totalFrames() const
{
	return (int)m_frames.size();
}

const std::string& Anim::name() const
{
	return m_name;
}

sf::IntRect& Anim::currFrame()
{
	return m_frames[m_currIndex];
}

void Anim::setCurrIdx(int idx)
{
	if (idx < m_frames.size())
	{
		m_currIndex = idx;
	}
	else
	{
		std::cout << "index not within range, setting index back to zero" << std::endl;
		m_currIndex = 0;
	}
}

bool Anim::onLastFrame()
{
	return m_onLastFrame;
}

void Anim::update(sf::Time l_dt)
{
	m_frameDelayElapsed += l_dt;

	if (m_frameDelayElapsed.asSeconds() > m_frameDelay)
	{
		m_frameDelayElapsed = sf::Time::Zero;

		animate();
	}
}

void Anim::setLooping(bool l_loop)
{
	m_looping = l_loop;
}

void Anim::setVFlip(bool l_vFlip)
{
	m_isFlippedV = l_vFlip;
}

void Anim::setHFlip(bool l_hFlip)
{
	m_isFlippedH = l_hFlip;
}

const std::string& Anim::getName() const
{
	return m_name;
}
