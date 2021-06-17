#include "pch.h"
#include "Sphere.h"

Sphere::Sphere(double density, double radius)
	: SolidBody(density)
	, m_radius(radius)
{
}

std::string Sphere::GetName() const
{
	return "Sphere";
}

double Sphere::GetRadius() const
{
	return m_radius;
}

double Sphere::GetVolume() const
{
	return (4 * M_PI * pow(m_radius, 3)) / 3;
}

void Sphere::AppendProperties(std::ostream& strm, int level) const
{
	std::string shift(level, (char)0x20);
	strm << shift << "Radius: " << GetRadius() << "\n";
}