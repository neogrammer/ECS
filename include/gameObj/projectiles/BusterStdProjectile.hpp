#ifndef BUSTERSTDPROJECTILE_HPP__
#define BUSTERSTDPROJECTILE_HPP__
#include <gameObj/ProjectileObj.hpp>


class BusterStdProjectile : public ProjectileObj
{
public:
	BusterStdProjectile();
	BusterStdProjectile(float inX, float inY, int dir);
	~BusterStdProjectile() override final;

	void processInput() override final;

	void update(sf::Time l_dt) override final;
	
	void render(sf::RenderWindow& l_wnd) override final;
};

#endif