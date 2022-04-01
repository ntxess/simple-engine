#pragma once

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

	}
};

class CommandEXSkill : public Command
{
public:
	CommandEXSkill() {}
	~CommandEXSkill() {}

	void Execute()
	{

	}
};