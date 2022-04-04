#include "CommandDodge.hpp"

CommandDodge::CommandDodge()
	: _cooldownTime(sf::seconds(5.f).asSeconds())
	, _dodgeOffset(100.f)
{}

CommandDodge::~CommandDodge()
{}

void CommandDodge::Execute(const GameObject& object)
{
	float currentTime = _timer.getElapsedTime().asSeconds();
	sf::Vector2f direction = object.GetInput()->GetDirection();

	if (direction != sf::Vector2f(0, 0) && currentTime > _cooldownTime)
	{
		direction.x *= _dodgeOffset;
		direction.y *= _dodgeOffset;

		object.GetGraphics()->GetSprite().move(direction);
		_timer.restart();
	}
}