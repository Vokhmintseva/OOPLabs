#include "pch.h"
#include "Body.h"

std::string Body::ToString(int level) const
{
	std::string shift;
	shift.insert(0, " ", level);
	std::ostringstream info;
	info << std::fixed << std::setprecision(2);
	info << shift << GetName() << '\n';
	info << shift << "Density: " << GetDensity() << '\n';
	info << shift << "Volume: " << GetVolume() << '\n';
	info << shift << "Mass: " << GetMass() << '\n';
	return info.str();
}
