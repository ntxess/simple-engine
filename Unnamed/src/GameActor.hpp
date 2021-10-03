#pragma once
#include <string>

class GameActor
{
private:
	std::string _name;

public:
	GameActor();
	std::string GetName();
};