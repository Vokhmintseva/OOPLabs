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

std::string Cone::ToString(int level) const
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
