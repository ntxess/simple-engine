#pragma once
#include <iostream>

class GameObject;

class Command
{
public:
	virtual void Execute(const GameObject& object) = 0;
};