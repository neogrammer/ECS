#ifndef SYSTEM_HPP__
#define SYSTEM_HPP__

enum class SystemType
{
	Movement,
	Count
};


class System
{
public:
	System() = default;
	virtual ~System() {}

	virtual void update(double l_dt) = 0;
};

#endif