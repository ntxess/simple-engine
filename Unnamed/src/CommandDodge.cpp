#include "CommandDodge.hpp"

CommandDodge::CommandDodge()
	: _cooldownTime(sf::seconds(5.f).asSeconds())
{}

CommandDodge::~CommandDodge()
{}

void CommandDodge::Execute(const Player& player)
{
	float currentTime = _timer.getElapsedTime().asSeconds();

	if (currentTime > _cooldownTime)
	{
		std::cout << "Dodging" << std::endl;
		_timer.restart();
	}
}