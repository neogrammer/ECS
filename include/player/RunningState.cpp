#include "RunningState.hpp"
#include "../ECS/Entity.hpp"


RunningState::RunningState()
	: PlayerState{"RUNNING"}
{

}

RunningState::~RunningState()
{
}

void RunningState::handleInput(Player& player, Input input)
{
	if (input.id() == PlayerInput::JUMP && player.canJump())
	{
		player.setCanJump(false);
		if (player.facingLeft())
		{
			if (player.get().getComponent<cAnimation>().currAnimation->name() != "JumpLeft")
				cAnimation::changeAnimation(player.get(), "JumpLeft");
		}
		else
		{
			if (player.get().getComponent<cAnimation>().currAnimation->name() != "JumpRight")
				cAnimation::changeAnimation(player.get(), "JumpRight");
		}
		player.get().cMgr.velocity().y = -100.f;
		player.setCurrState(PlayerInput::JUMP);
	}

	else if (input.id() == PlayerInput::MOVE_LEFT)
	{
		if (player.canJump() && player.get().getComponent<cAnimation>().currAnimation->name() != "RunLeft")
		{
			cAnimation::changeAnimation(player.get(), "RunLeft");
			//player.setCurrState(PlayerInput::MOVE_LEFT);
		}
		else if (!player.canJump() && player.get().getComponent<cAnimation>().currAnimation->name() != "JumpLeft")
		{
			cAnimation::changeAnimation(player.get(), "JumpLeft");
			player.setCurrState(PlayerInput::JUMP);
		}

		player.setFacingLeft(true);
		player.get().cMgr.velocity().x = -60.f;

	}
	else if (input.id() == PlayerInput::MOVE_RIGHT)
	{
		if (player.canJump() && player.get().getComponent<cAnimation>().currAnimation->name() != "RunRight")
		{
			cAnimation::changeAnimation(player.get(), "RunRight");
			//player.setCurrState(PlayerInput::MOVE_RIGHT);

		}
		else if (!player.canJump() && player.get().getComponent<cAnimation>().currAnimation->name() != "JumpRight")
		{
			cAnimation::changeAnimation(player.get(), "JumpRight");
			player.setCurrState(PlayerInput::JUMP);
		}

		player.setFacingLeft(false);
		player.get().cMgr.velocity().x = 60.f;

	}
	else if (input.id() == PlayerInput::NONE)
	{
		if (player.facingLeft())
		{
			if (player.canJump())
			{
				if (player.get().getComponent<cAnimation>().currAnimation->name() != "IdleLeft")
					cAnimation::changeAnimation(player.get(), "IdleLeft");
				player.setCurrState(PlayerInput::NONE);

			}
			else
			{
				if (player.get().getComponent<cAnimation>().currAnimation->name() != "JumpLeft")
					cAnimation::changeAnimation(player.get(), "JumpLeft");
				player.setCurrState(PlayerInput::JUMP);

			}

		}
		else
		{
			if (player.canJump())
			{
				if (player.get().getComponent<cAnimation>().currAnimation->name() != "IdleRight")
					cAnimation::changeAnimation(player.get(), "IdleRight");
				player.setCurrState(PlayerInput::NONE);
			}
			else
			{
				if (player.get().getComponent<cAnimation>().currAnimation->name() != "JumpRight")
					cAnimation::changeAnimation(player.get(), "JumpRight");
				player.setCurrState(PlayerInput::JUMP);

			}
		}
		//player.get().cMgr.velocity().x = 0.f;
	}
}

void RunningState::update(Player& player, sf::Time l_dt)
{
}
