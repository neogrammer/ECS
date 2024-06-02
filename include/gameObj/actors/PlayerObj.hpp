#ifndef PLAYEROBJ_HPP__
#define PLAYEROBJ_HPP__

#include <gameObj/ActorObj.hpp>
#include <action/ActionTarget.hpp>

class PlayerObj : public ActorObj, public ActionTarget<int>
{
	bool downPressed{ false }, leftPressed{ false }, rightPressed{ false };
	bool m_hasCollidedWithGround{ false };

public:


	PlayerObj();
	~PlayerObj() override final;

	virtual void processInput() override;

	virtual void update(sf::Time l_dt) override;

	virtual void render(sf::RenderWindow& l_wnd) override;

	bool& collidedWithGround();
};

#endif