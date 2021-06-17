#pragma once
#include "SolidBody.h"

class Cone final:
    public SolidBody
{
public:
    Cone(double density, double baseRadius, double height);
    std::string GetName() const override;
    double GetVolume() const override;
    double GetHeight() const;
    double GetBaseRadius() const;
private:
    void AppendProperties(std::ostream& strm, int level) const override;
    double m_baseRadius;
    double m_height;
};
