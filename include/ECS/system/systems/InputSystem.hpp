#ifndef INPUTSYSTEM_HPP__
#define INPUTSYSTEM_HPP__

#include "../System.hpp"
#include <vector>
#include <map>

class GameEngine;

class InputSystem : public System
{
public:

	enum class Signal : int
	{
		Up = 0, Down = 1, Left = 2, Right = 3
	};

	enum class Status
	{
		On, Off, Released, Held
	};

	std::map<Signal, Status> inputMap{};
	std::vector<std::pair<Signal, bool> > currentlyPressed{};
	InputSystem(GameEngine& l_game);
	~InputSystem() override final;

	void update(double l_dt) override final;
};

#endif