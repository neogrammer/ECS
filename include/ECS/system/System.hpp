#ifndef SYSTEM_HPP__
#define SYSTEM_HPP__


class GameEngine;

enum class SystemType
{
	Movement,
	Count
};


class System
{
protected:
	GameEngine& game;
public:
	System() = delete;
	explicit System(GameEngine& l_game) : game{ l_game } {}
	virtual ~System() {}

	virtual void update(double l_dt) = 0;
};

#endif