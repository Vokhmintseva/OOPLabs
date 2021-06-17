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

void Cylinder::AppendProperties(std::ostream& strm, int level) const
{
	std::string shift(level, (char)0x20);
	strm << shift << "Height: " << GetHeight() << "\n";
	strm << shift << "BaseRadius: " << GetBaseRadius() << "\n";
}