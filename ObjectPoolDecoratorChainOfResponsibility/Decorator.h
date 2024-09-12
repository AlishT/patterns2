#pragma once
#include <iostream>

class Weapon
{
public:
	~Weapon() {};
	virtual float recoilControl() const = 0;
};

class Rifle : public Weapon 
{
private:
	float controlValue = 100.0f;

public:
	float recoilControl() const override
	{
		return controlValue;
	}
};

class StockComponent : public Weapon
{
protected:
	float bonusControl = 1.5f;
	std::shared_ptr<Weapon> weapon;

public:
	StockComponent(std::shared_ptr<Weapon> _weapon) :
		weapon(_weapon)
	{}

	float recoilControl() const override
	{
		return weapon->recoilControl() * bonusControl;
	}
};

class UnderbarrelComponent : public StockComponent
{
public:
	UnderbarrelComponent(std::shared_ptr<Weapon> _weapon) : StockComponent(_weapon)
	{}

	float recoilControl() const override
	{
		return StockComponent::recoilControl() * bonusControl;
	}
};


