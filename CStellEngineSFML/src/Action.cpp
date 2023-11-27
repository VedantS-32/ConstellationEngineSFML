#include "Action.h"

Action::Action()
{
}

Action::Action(const std::string& Name, const std::string& Type) :
	m_Name(Name), m_Type(Type)
{
}

const std::string& Action::Name() const
{
	return m_Name;
}

const std::string& Action::Type() const
{
	return m_Type;
}

std::string Action::ToString() const
{
	return std::string();
}
