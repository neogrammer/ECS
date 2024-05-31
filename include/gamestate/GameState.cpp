#include "GameState.hpp"
#include "../core/Game.hpp"

GameState::GameState(Game& l_game, ActionMap<int>& l_actionMap)
	: ActionTarget<int>{ l_actionMap }
	, game{ l_game }
	, m_entityMgr{}
	, currentSystem{}
{
	currentSystem = nullptr;
}

GameState::~GameState()
{
}

EntityManager& GameState::eMgr()
{
	return m_entityMgr;
}
