#pragma once
#include<string>

class Action
{
private:
	std::string m_Name = "Default";
	std::string m_Type = "Default";

public:
	Action();
	Action(const std::string& Name, const std::string& Type);

	const std::string& Name() const;
	const std::string& Type() const;
	std::string ToString() const;
};
