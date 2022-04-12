#include "CommandDodge.hpp"

CommandDodge::CommandDodge()
	: _cooldownTime(sf::seconds(5.f).asSeconds())
	, _dodgeOffset(100.f)
{}

CommandDodge::~CommandDodge()
{}

void CommandDodge::Execute(const PlayerObject& player)
{
	float currentTime = _timer.getElapsedTime().asSeconds();
	sf::Vector2f direction = player.GetInput()->GetDirection();

	if (direction != sf::Vector2f(0, 0) && currentTime > _cooldownTime)
	{
		direction.x *= _dodgeOffset;
		direction.y *= _dodgeOffset;

		player.GetGraphics()->GetSprite().move(direction);
		_timer.restart();
	}
}