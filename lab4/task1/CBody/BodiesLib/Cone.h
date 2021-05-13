#pragma once
#include "SolidBody.h"

class Cone :
    public SolidBody
{
public:
    Cone(double density, double baseRadius, double height);
    std::string GetName() const override;
    std::string ToString(int level) const override;
    double GetVolume() const override;
    double GetHeight() const;
    double GetBaseRadius() const;
private:
    double m_baseRadius;
    double m_height;
};
