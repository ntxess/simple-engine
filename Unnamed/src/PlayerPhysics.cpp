#include "PlayerPhysics.hpp"

PlayerPhysics::PlayerPhysics()
{}

PlayerPhysics::~PlayerPhysics()
{}

sf::Vector2f PlayerPhysics::GetVelocity() const
{
	return _velocity;
}

void PlayerPhysics::Update(const Player& player, const float& deltaTime)
{
	// Execute any events triggered by the keys defined inside PlayerInput.Update()
	CommandRef command = player._input->_command;
	if (command)
		command->Execute(player);

	// Calculate distance to travel as offset
	sf::Vector2f direction = player._input->_direction;
	_velocity.x = direction.x * deltaTime * player._currentStats.SPD;
	_velocity.y = direction.y * deltaTime * player._currentStats.SPD;

	player._graphics->_sprite.move(_velocity);

	//sf::Vector2f direction = player._input->_direction;
	//_velocity = direction * deltaTime;

	//// Execute any events triggered by the keys defined inside PlayerInput.Update()
	//CommandRef command = player._input->_command;
	//if (command)
	//	command->Execute(player);

	//// Calculate distance to travel as offset
	//_velocity *= player._currentStats.SPD;
	//player._graphics->_sprite.move(_velocity);
}
