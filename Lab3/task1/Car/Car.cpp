#include "Car.h"
#include <string>
#include <cmath>
#include <iostream>

Car::Car()
    :m_isTurnedOn(false),
    m_speed(0),
    m_gear(Gear::Neutral),
    m_errorReason("")
{};

bool Car::TurnOnEngine()
{
    if (!m_isTurnedOn)
    {
        m_speed = 0;
        m_gear = Gear::Neutral;
    } 
    m_isTurnedOn = true;
    return true;
}

bool Car::TurnOffEngine()
{
    if (m_speed == 0 && m_gear == Gear::Neutral)
    {
        m_isTurnedOn = false;
		m_errorReason = "";
        return true;
    }
	m_errorReason = "Unable to turn off";
    return false;
}

bool Car::SetGear(int gear)
{
    if (gear < static_cast<int>(Car::Gear::Reverse) || gear > static_cast<int>(Car::Gear::Five))
    {
        m_errorReason = "Gear number is out of range";
        return false;
    }
    Car::Gear newGear = static_cast<Car::Gear>(gear);
    std::map<Gear, SpeedLimits>::const_iterator it;
	it = Car::speedLimits.find(newGear);
	int minSpeed = it->second.Min;
	int maxSpeed = it->second.Max;

	//при выключенном двигателе можно переключиться только на нейтральную передачу
	if (!m_isTurnedOn && newGear != Car::Gear::Neutral)
	{
		m_errorReason = "Only neutral gear can be switched to while car's engine is turned off";
		return false;
	}
	//на задний ход можно переключиться только на нулевой скорости
	if (newGear == Car::Gear::Reverse && m_speed != 0)
	{
		m_errorReason = "Reverse gear can be switched to if only car has 0 speed";
		return false;
	}

	//на переднюю передачу можно переключиться только после остановки
    if (newGear == Car::Gear::One && m_speed < 0)
	{
		m_errorReason = "Forward gear can be switched to while riding on the back draft only after reducing speed to 0";
		return false;
	}

	//диапазон скоростей новой передачи включает текущую скорость
	if (m_speed < minSpeed || m_speed > maxSpeed)
	{
		m_errorReason = "Current speed is out of range of the new gear";
		return false;
	}
	m_gear = newGear;
    m_errorReason = "";
	return true;
}

bool Car::SetSpeed(int newSpeed)
{
	if (newSpeed < 0) 
    {
		m_errorReason = "Speed must be non negative number";
        return false;
    }
    if (m_speed < 0 || m_gear == Gear::Reverse)
    {
        newSpeed = -1 * abs(newSpeed);
    }
    
    if (!m_isTurnedOn)
	{
		m_errorReason = "The engine is turned off";
		return false;
	}

	std::map<Gear, SpeedLimits>::const_iterator it;
	it = Car::speedLimits.find(m_gear);

	int minSpeed = it->second.Min;
	int maxSpeed = it->second.Max;

	if (newSpeed < minSpeed || newSpeed > maxSpeed)
	{
		m_errorReason = "New speed is out of range";
		return false;
	}

	if (m_gear == Gear::Neutral && (fabs(newSpeed) >= fabs(m_speed)))
	{
		m_errorReason = "Speed can only drop while the gear is neutral";
		return false;
	}
	m_speed = newSpeed;
    m_errorReason = "";
	return true;
}

bool Car::IsTurnedOn() const
{
    return m_isTurnedOn;
}

Car::Direction Car::GetDirection() const
{
    std::string direction = "";
    if (m_speed == 0)
    {
		return Direction::Static;
    }
    else if (m_speed > 0)
    {
		return Direction::Forward;
    }
	else
    {
		return Direction::Backward;
    }
}

unsigned int Car::GetSpeed() const
{
    return abs(m_speed);
}

int Car::GetGear() const
{
    return static_cast<int>(m_gear);
}

const std::string& Car::GetErrorReason() const &
{
    return m_errorReason;
}

const std::string Car::GetErrorReason() const&&
{
	return std::move(m_errorReason);
}