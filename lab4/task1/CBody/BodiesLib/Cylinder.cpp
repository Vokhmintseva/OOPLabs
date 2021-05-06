#include "pch.h"
#include "Cylinder.h"
#define _USE_MATH_DEFINES
#include <math.h>

Cylinder::Cylinder(double density, double volume, double height)
	: Body(density, volume)
	, m_height(height)
	, m_baseRadius(sqrt(volume / (height * M_PI)))
{}

Body::BodyType Cylinder::GetType()
{
	return Body::BodyType::Cylinder;
}

std::string Cylinder::GetName() const
{
	return "Cylinder";
}

double Cylinder::GetHeight() const
{
	return m_height;
}

double Cylinder::GetBaseRadius() const
{
	return m_baseRadius;
}

std::string Cylinder::ToString() const
{
	std::string baseInfo = Body::ToString();
	std::ostringstream info;
	info << std::fixed << std::setprecision(2);
	info << "Height: " << GetHeight() << "\n";
	info << "BaseRadius: " << GetBaseRadius() << "\n";
	std::string infoStr = info.str();
	return std::move(baseInfo.append(std::move(infoStr)));
}
