#pragma once
#include <iostream>
#include "GameObject.hpp"

class Command
{
public:
	virtual ~Command() {};
	virtual void execute(GameObject& actor) = 0;
};
 
class CMDMoveUp : public Command
{
public:
	CMDMoveUp() {}
	~CMDMoveUp() {}
	void execute(GameObject& actor)
	{
		actor.Input()->MoveUp();
	}
};
 
class CMDMoveLeft : public Command
{
public:
	CMDMoveLeft() {}
	~CMDMoveLeft() {}
	void execute(GameObject& actor)
	{
		actor.Input()->MoveLeft();
	}
};

class CMDMoveDown : public Command
{
public:
	CMDMoveDown() {}
	~CMDMoveDown() {}
	void execute(GameObject& actor)
	{
		actor.Input()->MoveDown();
	}
};

class CMDMoveRight : public Command
{
public:
	CMDMoveRight() {}
	~CMDMoveRight() {}
	void execute(GameObject& actor)
	{
		actor.Input()->MoveRight();
	}
};