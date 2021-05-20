#pragma once
#include "SolidBody.h"

class Cylinder final:
    public SolidBody
{
public:
    Cylinder(double density, double baseRadius, double height);
    std::string GetName() const override;
    std::string ToString(int level) const override;
    double GetVolume() const override;
    double GetHeight() const;
    double GetBaseRadius() const;
private:
    double m_height;
    double m_baseRadius;
};

