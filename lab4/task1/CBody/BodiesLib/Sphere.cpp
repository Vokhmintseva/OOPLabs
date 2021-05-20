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

std::string Sphere::ToString(int level) const
{
	std::string baseInfo = Body::ToString(level);
	std::ostringstream info;
	std::string shift(level, (char)0x20);
	info << std::fixed << std::setprecision(2);
	info << shift << "Radius: " << GetRadius() << "\n";
	std::string infoStr = info.str();
	return baseInfo.append(std::move(infoStr));
}