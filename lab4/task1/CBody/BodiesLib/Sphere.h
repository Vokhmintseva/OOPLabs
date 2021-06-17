#pragma once
#include "SolidBody.h"

class Sphere final:
    public SolidBody
{
public:
    Sphere(double density, double radius);
    double GetVolume() const override;
    std::string GetName() const override;
    double GetRadius() const;
private:
    void AppendProperties(std::ostream& strm, int level) const override;
    double m_radius;
};

