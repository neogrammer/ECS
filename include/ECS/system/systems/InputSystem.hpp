#ifndef INPUTSYSTEM_HPP__
#define INPUTSYSTEM_HPP__

#include "../System.hpp"

class InputSystem : public System
{
public:
	InputSystem();
	~InputSystem() override final;

	void update(double l_dt) override final;
};

#endif