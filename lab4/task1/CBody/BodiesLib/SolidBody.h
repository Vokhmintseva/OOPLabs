#pragma once
#include "Body.h"

class SolidBody :
	public Body
{
public:
	double GetDensity() const override final;
	double GetMass() const override final;
protected:
	explicit SolidBody(double density);
private:
	double m_density;
};
