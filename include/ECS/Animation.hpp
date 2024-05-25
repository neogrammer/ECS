#ifndef ANIMATION_HPP__
#define ANIMATION_HPP__
#include <SFML/Graphics/Texture.hpp>
class Animation
{
	sf::Texture* tex;
public:
	Animation();
	Animation(sf::Texture* l_tex);
	Animation(const Animation&) = default;
	Animation& operator=(const Animation&) = default;

	~Animation();
};

#endif