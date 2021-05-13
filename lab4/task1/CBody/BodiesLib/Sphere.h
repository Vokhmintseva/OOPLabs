#pragma once
#include "SolidBody.h"

class Sphere :
    public SolidBody
{
public:
    Sphere(double density, double radius);
    double GetVolume() const override;
    std::string GetName() const override;
    std::string ToString(int level) const override;
    double GetRadius() const;
private:
    double m_radius;
};

