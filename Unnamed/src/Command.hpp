#pragma once
#include <iostream>

class PlayerObject;

class Command
{
public:
	virtual void Execute(const PlayerObject& player) = 0;
};