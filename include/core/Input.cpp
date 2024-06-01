#include "Input.hpp"

Input::Input()
	: Input(PlayerInput::NONE)
{

}

Input::Input(PlayerInput l_type)
	: m_inputType{l_type}
{
}

Input::~Input()
{
}

void Input::update(sf::Time l_dt)
{
}

PlayerInput Input::id()
{
	return m_inputType;
}
