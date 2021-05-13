#pragma once

class Body
{
public:
	virtual double GetDensity() const = 0;
	virtual double GetVolume() const = 0;
	virtual double GetMass() const = 0;
	virtual std::string GetName() const = 0;
	virtual std::string ToString(int level) const;
	virtual ~Body() = default;
};
