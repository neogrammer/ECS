#ifndef RENDERSYSTEM_HPP__
#define RENDERSYSTEM_HPP__

#include "../System.hpp"

class RenderSystem : public System
{
public:
	RenderSystem();
	~RenderSystem() override final;

	void update(double l_dt) override final;
};

#endif