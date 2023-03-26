#include "CommandDodge.hpp"

CommandDodge::CommandDodge()
	: _cooldownTime(sf::seconds(5.f).asSeconds())
	, _dodgeOffset(100.f)
{}

CommandDodge::~CommandDodge()
{}

float CommandDodge::GetTime() const
{
	return _timer.getElapsedTime().asSeconds();
}

float CommandDodge::GetMaxTime() const
{
	return _cooldownTime;
}

void CommandDodge::Execute(entt::registry& registry, entt::entity entity, std::shared_ptr<GameData>& data)
{
	auto controller = registry.get<PlayerInputComponent>(entity);
	auto& sp = registry.get<SpriteComponent>(entity);

	float currentTime = _timer.getElapsedTime().asSeconds();
	sf::Vector2f direction = controller.direction;

	if (direction != sf::Vector2f(0, 0) && currentTime > _cooldownTime)
	{
		direction.x *= _dodgeOffset;
		direction.y *= _dodgeOffset;

		sp.sprite.move(direction);
		_timer.restart();
	}
}