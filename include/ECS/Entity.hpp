#ifndef ENTITY_HPP__
#define ENTITY_HPP__
#include <utility>
#include <memory>
#include <string>
#include "component/components/Components.hpp"
#include <tuple>
#include "component/components/cMaster.hpp"
#include <type_traits>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "../util/Vec2.hpp"


// Additional Components and Entity can take on
typedef std::tuple<
	cRigidBody,
	cGravity,
	cLifespan,
	cAnimation
> CTuple;

class EntityManager;
class GameEngine;
class Entity
{
	friend class cMaster;
	friend class EntityManager;
	friend class Make;

	
	size_t m_id;
	std::string m_tag;
	bool m_alive;
	std::tuple<cRigidBody, cGravity, cLifespan, cAnimation> m_cTuple;
	Entity() = delete;
	Entity(EntityManager& l_eMgr, const std::string& l_tag, sf::IntRect l_texFrame, size_t l_id, std::string l_texName, Vec2 l_pos = Vec2(0.0f,0.0f));

public:
	// Master Component, one on every entity. Contols Entity interaction with itself by acting as the hub between them so functionality becomes encapsulated
	// without adding specific funnctionality to any of the simple component structures in our ECS pattern, and carries a reference to its owning Entity 
	cMaster cMgr;
	EntityManager& eMgr;
	size_t id();
	bool isAlive();
	const std::string& tag();
	void destroy();

	// each entity calls update on its master component cMgr, which in turn 
	void processInput();
	void update(sf::Time l_dt);
	void render(sf::RenderWindow& l_wnd);



	template <typename AComponent>
	bool hasComponent() const
	{
		
		return getComponent<AComponent>().has;
	};

	template <typename AComponent, typename... AComponentArgs>
	AComponent& addComponent(AComponentArgs&&... l_args)
	{
		

			auto& component = getComponent<AComponent>();
			component = AComponent(std::forward<AComponentArgs>(l_args)...);
			component.has = true;
			return component;
	
	};

	template <typename AComponent>
	AComponent & getComponent()
	{
		return std::get<AComponent>(m_cTuple);
	};

	template <typename AComponent>
	const AComponent& getComponent() const
	{
		return std::get<AComponent>(m_cTuple);
	};

	template <typename AComponent>
	void removeComponent()
	{
		getComponent<AComponent>() = AComponent();
	};

};
#endif