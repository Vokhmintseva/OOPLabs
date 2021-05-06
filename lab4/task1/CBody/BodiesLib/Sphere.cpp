#include "pch.h"
#include "Sphere.h"
#define _USE_MATH_DEFINES
#include <math.h>

Sphere::Sphere(double density, double volume)
	: Body(density, volume)
	, m_radius(std::cbrt((3 * volume) / M_PI) / 2.0)
{}

Body::BodyType Sphere::GetType()
{
	return Body::BodyType::Sphere;
}

std::string Sphere::GetName() const
{
	return "Sphere";
}

double Sphere::GetRadius() const
{
	return m_radius;
}

std::string Sphere::ToString() const
{
	std::string baseInfo = Body::ToString();
	std::ostringstream info;
	info << std::fixed << std::setprecision(2);
	info << "Radius: " << GetRadius() << "\n";
	std::string infoStr = info.str();
	return baseInfo.append(std::move(infoStr));
}