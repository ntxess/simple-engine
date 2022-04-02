#include "PlayerPhysics.hpp"

PlayerPhysics::PlayerPhysics()
	: _previousPos(sf::Vector2u(0, 0))
{}

PlayerPhysics::~PlayerPhysics()
{}

void PlayerPhysics::Update(const Player& player, float deltaTime)
{
	// Execute any events triggered by the keys defined in PlayerInput
	CommandRef command = player._input->_command;
	if (command)
		command->Execute();
	
	// Calculate distance to travele and save as offset
	sf::Vector2f direction = player._input->_direction;
	direction.x = direction.x * deltaTime * player._currentStats.SPD;
	direction.y = direction.y * deltaTime * player._currentStats.SPD;

	// If the offset causes the player to go out of bounds reset the player position 
	// to the previous location
	if (direction != sf::Vector2f(0, 0))
	{
		_previousPos = player._graphics->_sprite.getPosition();
		player._graphics->_sprite.move(direction);
	}
}
