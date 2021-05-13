#include "pch.h"
#include "SolidBody.h"

SolidBody::SolidBody(double density)
	: m_density(density)
{
}

double SolidBody::GetDensity() const
{
	return m_density;
}

double SolidBody::GetMass() const
{
	return GetDensity() * GetVolume();
}
