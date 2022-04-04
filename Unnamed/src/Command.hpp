#pragma once
#include <iostream>

class GameObject;
class PlayerInput;
class PlayerPhysics;
class PlayerGraphics;

class Command
{
public:
	virtual void Execute(const GameObject& object) = 0;
};