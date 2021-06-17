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
	m_parent_ptr = std::move(parentPtr);
}

bool Compound::AddChildBody(std::shared_ptr<Body> child)
{
	if (child->GetName() == "Compound")
	{
		if (child.get() == this)
		{
			return false;
		}

		auto childCompoundPtr = std::dynamic_pointer_cast<Compound>(child);
		if (childCompoundPtr)
		{
			if (childCompoundPtr->GetParentPtr().lock())
			{
				return false;
			}
		}
		else
		{
			return false;
		}

		std::shared_ptr<Body> parentPtr = GetParentPtr().lock();
		while (parentPtr != nullptr)
		{
			if (child == parentPtr)
			{
				return false;
			}
			auto parentCompoundPtr = std::dynamic_pointer_cast<Compound>(parentPtr);
			if (parentCompoundPtr)
			{
				parentPtr = parentCompoundPtr->GetParentPtr().lock();
			}
			else
			{
				return false;
			}
		}
		childCompoundPtr->SetParentPtr(shared_from_this());
	}
	m_children.emplace_back(std::move(child));
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
	return std::accumulate(m_children.begin(), m_children.end(), 0.0f,
		[](double volumeTotal, const std::shared_ptr<Body>& child) { return volumeTotal + child->GetVolume(); });
}

double Compound::GetMass() const
{
	return std::accumulate(m_children.begin(), m_children.end(), 0.0f,
		[](double volumeTotal, const std::shared_ptr<Body>& child) { return volumeTotal + child->GetMass(); });
}

void Compound::AppendProperties(std::ostream& strm, int level) const
{
	std::string shift(level, (char)0x20);
	strm << shift << "BEGIN_BODIES_IN_COMPOUND:\n";
	level += 2;
	std::string nestedBodiesInfo = std::accumulate(m_children.begin(), m_children.end(), std::string{},
		[level](std::string infoTotal, const std::shared_ptr<Body>& child) { return infoTotal += child->ToString(level) + '\n'; });
	strm << nestedBodiesInfo;
	strm << shift << "END_BODIES_IN_COMPOUND\n";
}