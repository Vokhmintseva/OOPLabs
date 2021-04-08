#pragma once
#include <string>
#include <map>

class Car
{
public:
	Car();
	
    bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int newGear);
	bool SetSpeed(int newSpeed);

	bool IsTurnedOn() const;
	std::string GetDirection() const;
	unsigned int GetSpeed() const;
	int GetGear() const;
	std::string GetGearErrorReason() const;
	std::string GetSpeedErrorReason() const;
	
private:
	enum class Gear
	{
		Reverse = -1,
		Neutral = 0,
		One = 1,
		Two = 2,
		Three = 3,
		Four = 4,
		Five = 5,
	};
	
	struct SpeedLimits
	{
		int Min;
		int Max;
	};

	/*const std::map<int, Car::Gear> gears =
	{
		{-1, Car::Gear::Reverse},
		{0, Car::Gear::Neutral},
		{1, Car::Gear::One},
		{2, Car::Gear::Two},
		{3, Car::Gear::Three},
		{4, Car::Gear::Four},
		{5, Car::Gear::Five}
	};*/
	
	const std::map<Car::Gear, SpeedLimits> speedLimits =
	{
		{Car::Gear::Reverse, {-20, 0}},
		{Car::Gear::Neutral, {-20, 150}},
		{Car::Gear::One, {0, 30}},
		{Car::Gear::Two, {20, 50}},
		{Car::Gear::Three, {30, 60}},
		{Car::Gear::Four, {40, 90}},
		{Car::Gear::Five, {50, 150}}
	};

	bool CanSwitchGear(Car::Gear newGear);
	bool CanSetSpeed(int newSpead);
	
	bool m_isTurnedOn;
	int m_speed;
	Car::Gear m_gear;
	std::string m_gearErrorReason;
	std::string m_speedErrorReason;
};