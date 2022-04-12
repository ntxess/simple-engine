#include "PlayerPhysics.hpp"

PlayerPhysics::PlayerPhysics()
{}

PlayerPhysics::~PlayerPhysics()
{}

sf::Vector2f PlayerPhysics::GetVelocity() const
{
	return _velocity;
}

void PlayerPhysics::Update(const PlayerObject& player, const float& deltaTime)
{
	// Execute any events triggered by the keys defined inside PlayerInput.Update()
	std::shared_ptr<Command> command = player.GetInput()->GetCommand();
	if (command)
		command->Execute(player);

	// Calculate distance to travel as offset
	sf::Vector2f direction = player.GetInput()->GetDirection();
	_velocity.x = direction.x * deltaTime * player.GetCurrentStats().SPD;
	_velocity.y = direction.y * deltaTime * player.GetCurrentStats().SPD;

	player.GetGraphics()->GetSprite().move(_velocity);
}
