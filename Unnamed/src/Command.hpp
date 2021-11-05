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
		actor.GetInput()->Move(sf::Vector2f(0, -1));
	}
};

class CommandLeft : public Command
{
public:
	CommandLeft() {}
	~CommandLeft() {}
	void Execute(GameObject& actor)
	{
		actor.GetInput()->Move(sf::Vector2f(-1, 0));
	}
};

class CommandDown : public Command
{
public:
	CommandDown() {}
	~CommandDown() {}
	void Execute(GameObject& actor)
	{
		actor.GetInput()->Move(sf::Vector2f(0, 1));
	}
};

class CommandRight : public Command
{
public:
	CommandRight() {}
	~CommandRight() {}
	void Execute(GameObject& actor)
	{
		actor.GetInput()->Move(sf::Vector2f(1, 0));
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