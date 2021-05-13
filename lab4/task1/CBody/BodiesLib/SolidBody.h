#pragma once
#include "Body.h"

class SolidBody :
	public Body
{
public:
	SolidBody(double density);
	virtual ~SolidBody() = default;
	double GetDensity() const override;
	double GetMass() const override;
private:
	double m_density;
};
