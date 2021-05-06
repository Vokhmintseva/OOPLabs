#include "pch.h"
#include "Cone.h"
#define _USE_MATH_DEFINES
#include <math.h>

Cone::Cone(double density, double volume, double height)
	: Body(density, volume)
	, m_height(height)
	, m_baseRadius(std::sqrt((3.0 * volume) / (M_PI * height)))
{}

Body::BodyType Cone::GetType()
{
	return Body::BodyType::Cone;
}

std::string Cone::GetName() const
{
	return "Cone";
}

double Cone::GetHeight() const
{
	return m_height;
}

double Cone::GetBaseRadius() const
{
	return m_baseRadius;
}

std::string Cone::ToString() const
{
	std::string baseInfo = Body::ToString();
	std::ostringstream info;
	info << std::fixed << std::setprecision(2);
	info << "Height: " << GetHeight() << "\n";
	info << "BaseRadius: " << GetBaseRadius() << "\n";
	std::string infoStr = info.str();
	return std::move(baseInfo.append(std::move(infoStr)));
}
