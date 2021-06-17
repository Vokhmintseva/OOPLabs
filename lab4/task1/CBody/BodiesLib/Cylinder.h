#pragma once
#include "SolidBody.h"

class Cylinder final:
    public SolidBody
{
public:
    Cylinder(double density, double baseRadius, double height);
    std::string GetName() const override;
    double GetVolume() const override;
    double GetHeight() const;
    double GetBaseRadius() const;
private:
    void AppendProperties(std::ostream& strm, int level) const override;
    double m_height;
    double m_baseRadius;
};

