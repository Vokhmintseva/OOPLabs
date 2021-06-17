#include "pch.h"
#include "Cone.h"

Cone::Cone(double density, double radius, double height)
	: SolidBody(density)
	, m_baseRadius(radius)
	, m_height(height)
{
}

std::string Cone::GetName() const
{
	return "Cone";
}

double Cone::GetHeight() const
{
	return m_height;
}

double Cone::GetVolume() const
{
	return M_PI * pow(m_baseRadius, 2) * m_height / 3;
}

double Cone::GetBaseRadius() const
{
	return m_baseRadius;
}

void Cone::AppendProperties(std::ostream& strm, int level) const
{
	std::string shift(level, (char)0x20);
	strm << shift << "Height: " << GetHeight() << "\n";
	strm << shift << "BaseRadius: " << GetBaseRadius() << "\n";
}
