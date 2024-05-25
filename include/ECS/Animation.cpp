#include "Animation.hpp"

void Animation::animate()
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

Animation::Animation()
	: Animation{ {1,1} }
{

}

Animation::Animation(sf::Vector2i l_frameSize, const std::string& l_name, int l_numFrames, int l_cols, int l_rows, sf::Vector2i l_startPos, float l_frameDelay, bool l_looping, bool l_isFlippedH, bool l_isFlippedV)
	: m_frames{}, m_currIndex{ 0 }, m_frameDelayElapsed{ sf::Time::Zero }, m_frameDelay{ l_frameDelay }, m_looping{ l_looping }, m_isFlippedH{l_isFlippedH}, m_isFlippedV{l_isFlippedV}, m_name{l_name}
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

Animation::~Animation()
{

}

const int Animation::totalFrames() const
{
	return (int)m_frames.size();
}

const std::string& Animation::name() const
{
	return m_name;
}

sf::IntRect& Animation::currFrame()
{
	return m_frames[m_currIndex];
}

bool Animation::onLastFrame()
{
	return m_onLastFrame;
}

void Animation::update(sf::Time l_dt)
{
	m_frameDelayElapsed += l_dt;

	if (m_frameDelayElapsed.asSeconds() > m_frameDelay)
	{
		m_frameDelayElapsed = sf::Time::Zero;

		animate();
	}
}

void Animation::setLooping(bool l_loop)
{
	m_looping = l_loop;
}

void Animation::setVFlip(bool l_vFlip)
{
	m_isFlippedV = l_vFlip;
}

void Animation::setHFlip(bool l_hFlip)
{
	m_isFlippedH = l_hFlip;
}
