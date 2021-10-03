#pragma once
#include <iostream>
#include "GameActor.hpp"

class Command
{
public:
	virtual ~Command() {};
	virtual void execute(GameActor& actor) = 0;
};

class JumpCommand : public Command
{
public:
	void execute(GameActor& actor)
	{
		std::cout << actor.GetName() << " called: JumpCommand" << std::endl;
	}
};

