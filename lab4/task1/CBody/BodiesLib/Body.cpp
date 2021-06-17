#include "pch.h"
#include "Body.h"

std::string Body::ToString(int level) const
{
	std::string shift(level, (char)0x20);
	std::ostringstream info;
	info << std::fixed << std::setprecision(2);
	info << shift << GetName() << '\n';
	info << shift << "Density: " << GetDensity() << '\n';
	info << shift << "Volume: " << GetVolume() << '\n';
	info << shift << "Mass: " << GetMass() << '\n';
	AppendProperties(info, level);
	return info.str();
}
