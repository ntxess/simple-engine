#include "GameActor.hpp"

GameActor::GameActor() : _name("Player1") {}

std::string GameActor::GetName()
{
	return _name;
}