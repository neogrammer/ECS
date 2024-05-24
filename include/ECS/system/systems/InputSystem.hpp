#ifndef INPUTSYSTEM_HPP__
#define INPUTSYSTEM_HPP__

#include "../System.hpp"
class GameEngine;

class InputSystem : public System
{
public:
	InputSystem(GameEngine& l_game);
	~InputSystem() override final;

	void update(double l_dt) override final;
};

#endif