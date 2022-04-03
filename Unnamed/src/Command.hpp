#pragma once
#include <iostream>

class Player;
class PlayerInput;
class PlayerPhysics;
class PlayerGraphics;

class Command
{
public:
	virtual void Execute(const Player& player) = 0;
};