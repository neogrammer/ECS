#include "InputSystem.hpp"
#include "../core/GameEngine.hpp"

InputSystem::InputSystem(GameEngine& l_game)
	: System{l_game}
	, currentlyPressed{}
{
	currentlyPressed.clear();
	currentlyPressed.push_back(std::pair(Signal::Up, false));
	currentlyPressed.push_back(std::pair(Signal::Down, false));
	currentlyPressed.push_back(std::pair(Signal::Left, false));
	currentlyPressed.push_back(std::pair(Signal::Right, false));

	inputMap = {
		 {Signal::Up, Status::Off},
		{Signal::Down, Status::Off},
		{Signal::Left, Status::Off},
		{Signal::Right, Status::Off}
	};

}

InputSystem::~InputSystem()
{
}

void InputSystem::update(double l_dt)
{
	for (auto& inputFrame : currentlyPressed)
	{
		switch (inputFrame.first)
		{
			case Signal::Down:
				{
					if (inputFrame.second == true)
					{
						if (inputMap[Signal::Down] == Status::Off)
						{
							inputMap[Signal::Down] = Status::On;
						}
						else if (inputMap[Signal::Down] == Status::On)
						{
							inputMap[Signal::Down] = Status::Held;
						}
						else if (inputMap[Signal::Down] == Status::Released)
						{
							inputMap[Signal::Down] = Status::On;
						}
						else if (inputMap[Signal::Down] == Status::Held)
						{
							inputMap[Signal::Down] = Status::Held;
						}
					}
					else {
						if (inputMap[Signal::Down] == Status::Off)
						{
							inputMap[Signal::Down] = Status::Off;
						}
						else if (inputMap[Signal::Down] == Status::On)
						{
							inputMap[Signal::Down] = Status::Off;
						}
						else if (inputMap[Signal::Down] == Status::Released)
						{
							inputMap[Signal::Down] = Status::Off;
						}
						else if (inputMap[Signal::Down] == Status::Held)
						{
							inputMap[Signal::Down] = Status::Released;
						}
					}
				}	
				break;
			case Signal::Up:
				{
				if (inputFrame.second == true)
				{
					if (inputMap[Signal::Up] == Status::Off)
					{
						inputMap[Signal::Up] = Status::On;
					}
					else if (inputMap[Signal::Up] == Status::On)
					{
						inputMap[Signal::Up] = Status::Held;
					}
					else if (inputMap[Signal::Up] == Status::Released)
					{
						inputMap[Signal::Up] = Status::On;
					}
					else if (inputMap[Signal::Up] == Status::Held)
					{
						inputMap[Signal::Up] = Status::Held;
					}
				}
				else {
					if (inputMap[Signal::Up] == Status::Off)
					{
						inputMap[Signal::Up] = Status::Off;
					}
					else if (inputMap[Signal::Up] == Status::On)
					{
						inputMap[Signal::Up] = Status::Off;
					}
					else if (inputMap[Signal::Up] == Status::Released)
					{
						inputMap[Signal::Up] = Status::Off;
					}
					else if (inputMap[Signal::Up] == Status::Held)
					{
						inputMap[Signal::Up] = Status::Released;
					}
				}
				}
				break; 
			case Signal::Left:
				{
				if (inputFrame.second == true)
				{
					if (inputMap[Signal::Left] == Status::Off)
					{
						inputMap[Signal::Left] = Status::On;
					}
					else if (inputMap[Signal::Left] == Status::On)
					{
						inputMap[Signal::Left] = Status::Held;
					}
					else if (inputMap[Signal::Left] == Status::Released)
					{
						inputMap[Signal::Left] = Status::On;
					}
					else if (inputMap[Signal::Left] == Status::Held)
					{
						inputMap[Signal::Left] = Status::Held;
					}
				}
				else {
					if (inputMap[Signal::Left] == Status::Off)
					{
						inputMap[Signal::Left] = Status::Off;
					}
					else if (inputMap[Signal::Left] == Status::On)
					{
						inputMap[Signal::Left] = Status::Off;
					}
					else if (inputMap[Signal::Left] == Status::Released)
					{
						inputMap[Signal::Left] = Status::Off;
					}
					else if (inputMap[Signal::Left] == Status::Held)
					{
						inputMap[Signal::Left] = Status::Released;
					}
				}
				}
				break; 
			case Signal::Right:
				{
				if (inputFrame.second == true)
				{
					if (inputMap[Signal::Right] == Status::Off)
					{
						inputMap[Signal::Right] = Status::On;
					}
					else if (inputMap[Signal::Right] == Status::On)
					{
						inputMap[Signal::Right] = Status::Held;
					}
					else if (inputMap[Signal::Right] == Status::Released)
					{
						inputMap[Signal::Right] = Status::On;
					}
					else if (inputMap[Signal::Right] == Status::Held)
					{
						inputMap[Signal::Right] = Status::Held;
					}
				}
				else {
					if (inputMap[Signal::Right] == Status::Off)
					{
						inputMap[Signal::Right] = Status::Off;
					}
					else if (inputMap[Signal::Right] == Status::On)
					{
						inputMap[Signal::Right] = Status::Off;
					}
					else if (inputMap[Signal::Right] == Status::Released)
					{
						inputMap[Signal::Right] = Status::Off;
					}
					else if (inputMap[Signal::Right] == Status::Held)
					{
						inputMap[Signal::Right] = Status::Released;
					}
				}

				}
				break;
			default:
				break;
		}

		
	}
	currentlyPressed[0].second = false;
	currentlyPressed[1].second = false;
	currentlyPressed[2].second = false;
	currentlyPressed[3].second = false;


	

}

