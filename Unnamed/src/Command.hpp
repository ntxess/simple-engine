#pragma once
#include "GameObject.hpp"

class Command
{
public:
	virtual void Execute(GameObject& actor) = 0;
};

class CommandUp : public Command
{
public:
	CommandUp() {}
	~CommandUp() {}
	void Execute(GameObject& actor)
	{
		actor.GetInput()->MoveUp();
	}
};

class CommandLeft : public Command
{
public:
	CommandLeft() {}
	~CommandLeft() {}
	void Execute(GameObject& actor)
	{
		actor.GetInput()->MoveLeft();
	}
};

class CommandDown : public Command
{
public:
	CommandDown() {}
	~CommandDown() {}
	void Execute(GameObject& actor)
	{
		actor.GetInput()->MoveDown();
	}
};

class CommandRight : public Command
{
public:
	CommandRight() {}
	~CommandRight() {}
	void Execute(GameObject& actor)
	{
		actor.GetInput()->MoveRight();
	}
};

class CommandEnter : public Command
{
public:
	CommandEnter() {}
	~CommandEnter() {}
	void Execute(GameObject& actor)
	{
		//actor.Input()->Enter();
	}
};