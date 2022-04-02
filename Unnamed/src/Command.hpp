#pragma once
#include <iostream>

class Command
{
public:
	virtual void Execute() = 0;
};

class CommandDodge : public Command
{
public:
	CommandDodge() {}
	~CommandDodge() {}

	void Execute()
	{
		std::cout << "DODGING" << std::endl;
	}
};

class CommandEXSkill : public Command
{
public:
	CommandEXSkill() {}
	~CommandEXSkill() {}

	void Execute()
	{
		std::cout << "USING EX SKILL" << std::endl;
	}
};