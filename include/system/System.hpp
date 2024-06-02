#ifndef SYSTEM_HPP__
#define SYSTEM_HPP__
#include <SFML/Graphics.hpp>
class System
{
protected:
	sf::RenderWindow& wnd;
	sf::Time& dt;
public:
	System(sf::RenderWindow& l_wnd, sf::Time& l_dt);
	virtual ~System();

	virtual void update() = 0;
	virtual void draw() = 0;
};


#endif