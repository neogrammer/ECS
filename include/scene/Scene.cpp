#include "Scene.hpp"
#include "../core/GameEngine.hpp"

Scene::Scene(GameEngine& l_game, ActionMap<int>& l_actionMap)
	: ActionTarget<int>{l_actionMap}
	, game{l_game}
	, m_entityMgr{}
{
}

Scene::~Scene()
{
}

EntityManager& Scene::eMgr()
{
	return m_entityMgr;
}
