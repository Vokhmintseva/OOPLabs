#include "pch.h"
#include "Body.h"

Body::Body(double density, double volume)
	: m_density(density)
	, m_volume(volume)
{
	m_mass = density * volume;
};

std::string Body::GetName() const
{
	return "Body";
}

double Body::GetDensity() const
{
	return m_density;
}

double Body::GetVolume() const
{
	return m_volume;
}

double Body::GetMass() const
{
	return m_mass;
}

std::string Body::ToString() const
{
	std::ostringstream info;
	info << std::fixed << std::setprecision(2);
	info << GetName() << '\n';
	info << "Density: " << GetDensity() << '\n';
	info << "Volume: " << GetVolume() << '\n';
	info << "Mass: " << GetMass() << '\n';
	return info.str();
}
