#include "PlayerPhysics.hpp"

PlayerPhysics::PlayerPhysics()
{}

PlayerPhysics::~PlayerPhysics()
{}

void PlayerPhysics::Update(const Player& player, const float& deltaTime)
{
	// Execute any events triggered by the keys defined inside PlayerInput.Update()
	CommandRef command = player._input->_command;
	if (command)
		command->Execute(player);

	// Calculate distance to travel as offset
	sf::Vector2f direction = player._input->_direction;
	direction.x = direction.x * deltaTime * player._currentStats.SPD;
	direction.y = direction.y * deltaTime * player._currentStats.SPD;

	player._graphics->_sprite.move(direction);
}
