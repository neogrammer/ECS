#ifndef PLAYSTATE_HPP__
#define PLAYSTATE_HPP__
#include "../GameState.hpp"
#include <string>
#include <memory>
#include <utility>
#include "../../core/Config.hpp"
#include "../../level/Tilemap.hpp"
#include <gameObj/actors/PlayerObj.hpp>
#include <level/Tilemap.hpp>
#include <util/Physics.hpp>

class ProjectileObj;
class BusterProjectileObj;

class Player;
class CollisionSystem;
class PlayState : public GameState
{
	friend class CollisionSystem;
	PlayerObj player;
	std::unique_ptr<Tilemap> tmap;
	std::vector<rect> vRects;
	bool mouseLeftHeld{ false };
	bool mouseLeftDown{ false };
	bool mouseLeftClicked{ false };
	bool mouseLeftUp{ true };
	sf::Time m_deltaTime;
	std::unique_ptr<CollisionSystem> colSys;
	bool showCollisionBox{ false };

	std::vector<std::shared_ptr<ProjectileObj> > projectiles;

	sf::Clock shootTimer{};
	float shootDelay{0.86f};


public:
	bool canFireABullet{ true };
	bool shootOnCooldown{ false };
	void startShootTimer();
	void checkIfCanFireAgain();

	Vec2 mpos{ 0.f,0.f };
	PlayState(Game& l_game, ActionMap<int>& l_actionMap);
	~PlayState() override final;
	void init() override final;
	void processInput() override final;
	void processEvents(std::vector<sf::Event>& l_evts) override final;
	void update(double l_dt) override final;
	void render(sf::RenderWindow& l_wnd) override final;

	void GetMouseClick();
	void fireABullet();

};
#endif