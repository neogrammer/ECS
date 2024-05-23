#include "GameEngine.hpp"

// ctor, no dtor neccessary... RAII be like that sometimes
GameEngine::GameEngine()
{
}

// hotpotato that shit
void GameEngine::propogateInput(std::vector<sf::Event>& l_evts)
{
	for (auto& e : l_evts)
	{
		// check which event and handle it via delegation
		// if delegate returns true, it was a successful execution, 
		//   log the event into an action file sequentially for an action replay file we could possibly use
	}
}

// make it rain on em
void GameEngine::handleWindowEvents(std::vector<sf::Event>& l_evts)
{
	for (auto& e : l_evts)
	{
		// check which event , handle it here first as super ceding any inner game action, such as reset,
		//   then still pass it along in case a delegate is waiting for it
	}
}

// value passed to this function always simulates a normalization to 60 fps, no matter what
//  should be smooth physics calculations because of this
void GameEngine::update(double l_dt)
{
}

// work your magic in here, blit a portion of a giant rendertexture sitting on the GPU the size of the window to the window for performance
void GameEngine::render(sf::RenderWindow& l_wnd)
{
}

// to abstract implementation away from the main function, just to be clean and concise
void GameEngine::mainLoop()
{
}




