#ifndef ANIMATION_HPP__
#define ANIMATION_HPP__
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include <string>
class Animation
{
	std::string m_name{ "none" };
	std::vector<sf::IntRect> m_frames{};
	size_t m_currIndex{};
	sf::Time m_frameDelayElapsed{ sf::Time::Zero };
	float m_frameDelay{0.1f}; // ten frames a second by default
	bool m_looping{ true };
	bool m_isFlippedH{ false };
	bool m_isFlippedV{ false };
	bool m_onLastFrame{ false };
	void animate();


public:
	// not in a useful state
	Animation();
	// first texture in the sheet must be to the furthest left and all rows are the same length except for maybe the last if the frames are a few short on the last row
	Animation(sf::Vector2i l_frameSize, const std::string& l_name = "default", int l_numFrames = 1, int l_cols = 1, int l_rows = 1, sf::Vector2i l_startPos = { 0,0 }, float l_frameDelay = 0.1f, bool l_looping = true, bool l_isFlippedH = false, bool l_isFlippedV = false);
	
	Animation(const Animation&) = default;
	Animation& operator=(const Animation&) = default;

	Animation(Animation&&) = delete;
	Animation& operator=(Animation&&) = delete;
	
	~Animation();
	

	const int totalFrames() const;
	const std::string& name() const;
	sf::IntRect& currFrame();
	void setCurrIdx(int idx);
	bool onLastFrame();
	void update(sf::Time l_dt);
	void setLooping(bool l_loop);
	void setVFlip(bool l_vFlip);
	void setHFlip(bool l_hFlip);
	const std::string& getName() const ;

};

#endif