#include "pch.h"
#include "Compound.h"

std::string Compound::GetName() const
{
	return "Compound";
}

std::weak_ptr<Body> Compound::GetParentPtr() const
{
	return m_parent_ptr;
}

void Compound::SetParentPtr(std::shared_ptr<Body> parentPtr)
{
	m_parent_ptr = parentPtr;
}

bool Compound::AddChildBody(std::shared_ptr<Body> child)
{
	if (child->GetName() == "Compound")
	{
		if (child.get() == this)
		{
			return false;
		}
		std::weak_ptr<Body> parentPtr = this->GetParentPtr();
		while (parentPtr.lock() != nullptr)
		{
			if (child == parentPtr.lock())
			{
				return false;
			}
			std::shared_ptr<Compound> parentCompoundPtr = std::dynamic_pointer_cast<Compound>(parentPtr.lock());
			parentPtr = parentCompoundPtr->GetParentPtr();
		}
		std::shared_ptr<Compound> childCompoundPtr = std::dynamic_pointer_cast<Compound>(child);
		childCompoundPtr->SetParentPtr(shared_from_this());
	}
	m_childs.push_back(child);
	return true;
}

double Compound::GetDensity() const
{
	double densityAvg = 0;
	double volumeTotal = GetVolume();
	if (volumeTotal)
	{
		densityAvg = GetMass() / volumeTotal;
	}
	return densityAvg;
}

double Compound::GetVolume() const
{
	double volumeTotal = 0;
	std::for_each(m_childs.rbegin(), m_childs.rend(), [&](auto& child) { volumeTotal += child->GetVolume(); });
	return volumeTotal;
}

double Compound::GetMass() const
{
	double massTotal = 0;
	std::for_each(m_childs.rbegin(), m_childs.rend(), [&](auto& child) { massTotal += child->GetMass(); });
	return massTotal;
}

std::string Compound::ToString(int level) const
{
	std::string baseInfo = Body::ToString(level);
	std::string infoTotal = "BEGIN_BODIES_IN_COMPOUND:\n";
	infoTotal.insert(0, " ", level);
	std::string shift;
	shift.insert(0, " ", level);
	level = level + 2;
	std::for_each(m_childs.rbegin(), m_childs.rend(), [level, &infoTotal](auto& child) { infoTotal += child->ToString(level) + '\n'; });
	infoTotal.append(shift);
	infoTotal.append("END_BODIES_IN_COMPOUND\n");
	return baseInfo.append(std::move(infoTotal));
}