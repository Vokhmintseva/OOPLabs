#include "pch.h"
#include "Cylinder.h"
#define _USE_MATH_DEFINES
#include <math.h>

Cylinder::Cylinder(double density, double radius, double height)
	: SolidBody(density)
	, m_baseRadius(radius)
	, m_height(height)
{
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

double Cylinder::GetVolume() const
{
	return M_PI * pow(m_baseRadius, 2) * m_height;
}

std::string Cylinder::ToString(int level) const
{
	std::string baseInfo = Body::ToString(level);
	std::ostringstream info;
	std::string shift;
	shift.insert(0, " ", level);
	info << std::fixed << std::setprecision(2);
	info << shift << "Height: " << GetHeight() << "\n";
	info << shift << "BaseRadius: " << GetBaseRadius() << "\n";
	std::string infoStr = info.str();
	return std::move(baseInfo.append(std::move(infoStr)));
}
