#include "Car.h"
#include <string>
#include <cmath>
#include <iostream>

Car::Car()
    :m_isTurnedOn(false),
    m_speed(0),
    m_gear(Gear::Neutral),
    m_gearErrorReason(""),
    m_speedErrorReason("")
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
        return true;
    }
    return false;
}

bool Car::SetGear(int gear)
{
    if (gear < static_cast<int>(Car::Gear::Reverse) || gear > static_cast<int>(Car::Gear::Five))
    {
        m_gearErrorReason = "Gear number is out of range";
        return false;
    }
    Car::Gear newGear = static_cast<Car::Gear>(gear);
    
    if (CanSwitchGear(newGear))
    {
        m_gear = newGear;
        return true;
    }
    return false;
}

bool Car::SetSpeed(int newSpeed)
{
    if (m_speed < 0 || m_gear == Gear::Reverse)
    {
        newSpeed = -1 * abs(newSpeed);
    }
    if (CanSetSpeed(newSpeed))
    {
        m_speed = newSpeed;
        return true;
    }
    return false;
}

bool Car::IsTurnedOn() const
{
    return m_isTurnedOn;
}

std::string Car::GetDirection() const
{
    std::string direction = "";
    if (m_speed == 0)
    {
        direction = "static";
    }
    if (m_speed > 0)
    {
        direction = "forward";
    }
    if (m_speed < 0)
    {
        direction = "backward";
    }
    return direction;
}

unsigned int Car::GetSpeed() const
{
    return abs(m_speed);
}

int Car::GetGear() const
{
    return static_cast<int>(m_gear);
}

bool Car::CanSwitchGear(Car::Gear newGear)
{
    /*if (m_gear == newGear)
    {
        m_gearErrorReason = "This gear is already set";
        return false;
    }*/
    std::map<Gear, SpeedLimits>::const_iterator it;
    it = Car::speedLimits.find(newGear);
    int minSpeed = it->second.Min;
    int maxSpeed = it->second.Max;

    //при выключенном двигателе можно переключиться только на нейтральную передачу
    if (!m_isTurnedOn && newGear != Car::Gear::Neutral)
    {
        m_gearErrorReason = "Only neutral gear can be switched to while car's engine is turned off";
        return false;
    }
    //на задний ход можно переключиться только на нулевой скорости
    if (newGear == Car::Gear::Reverse && m_speed != 0)
    {
        m_gearErrorReason = "Reverse gear can be switched to if only car has 0 speed";
        return false;
    }

    if (newGear == Car::Gear::One && m_speed < 0)
    {
        m_gearErrorReason = "Forward gear can be switched to while riding on the back draft only after reducing speed to 0";
        return false;
    }

    //диапазон скоростей новой передачи включает текущую скорость
    if (m_speed < minSpeed || m_speed > maxSpeed)
    {
        m_gearErrorReason = "Current speed is out of range of the new gear";
        return false;
    }
    //с заднего хода можно переключиться на первую передачу только на нулевой скорости
    /*if (m_gear == Car::Gear::Reverse && newGear == Car::Gear::One && m_speed != 0)
    {
        m_gearErrorReason = "The gear can be switched from reverse to first if only car has 0 speed";
        return false;
    }*/
    //на заднем ходу с нейтральной на ненулевой скорости переключиться на переднюю передачу можно только после остановки
    /*if (m_gear == Car::Gear::Neutral && newGear != Car::Gear::Reverse && newGear != Car::Gear::Neutral && m_direction == Direction::Backward)
    {
        m_gearErrorReason = "Forward gear can be switched to from neutral on the back draft at non zero speed only after stop";
        return false;
    }*/
    m_gearErrorReason = "";
    return true;
}

bool Car::CanSetSpeed(int newSpeed) 
{
    if (!m_isTurnedOn)
    {
        m_speedErrorReason = "The engine is turned off";
        return false;
    }
    
    std::map<Gear, SpeedLimits>::const_iterator it;
    it = Car::speedLimits.find(m_gear);

    int minSpeed = it->second.Min;
    int maxSpeed = it->second.Max;
   
    if (newSpeed < minSpeed || newSpeed > maxSpeed)
    {
        m_speedErrorReason = "New speed is out of range";
        return false;
    }

    if (m_gear == Gear::Neutral && (fabs(newSpeed) >= fabs(m_speed)))
    {
        m_speedErrorReason = "Speed can only drop while the gear is neutral";
        return false;
    }
    m_speedErrorReason = "";
    return true;
}

std::string Car::GetGearErrorReason() const
{
    return m_gearErrorReason;
}

std::string Car::GetSpeedErrorReason() const
{
    return m_speedErrorReason;
}







//SpeedLimits sl = Car::speedLimits[gear];