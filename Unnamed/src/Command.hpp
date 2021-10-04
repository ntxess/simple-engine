#pragma once
#include <iostream>
#include "Entity.hpp"

class Command
{
public:
	virtual ~Command() {};
	virtual void execute(Entity& actor) = 0;
};

class JumpCommand : public Command
{
public:
	void execute(Entity& actor)
	{
		std::cout << " Command called: JumpCommand" << std::endl;
	}
};

