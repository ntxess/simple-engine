#include "PlayerPhysics.hpp"

PlayerPhysics::PlayerPhysics()
	: _bounds(sf::Vector2u(1920, 1080))
{}

PlayerPhysics::~PlayerPhysics()
{}

bool PlayerPhysics::OutOfBounds(const Player& player)
{
	sf::Vector2f position = player._graphics->_sprite.getPosition();
	sf::FloatRect rect = player._graphics->_sprite.getGlobalBounds();

	if ((position.x < 0) || 
		(position.y < 0) ||
		(position.x + rect.width  > _bounds.x) ||
		(position.y + rect.height > _bounds.y))
	{
		return true;
	}

	return false;
}

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
		sf::Vector2f previousPos = player._graphics->_sprite.getPosition();
		player._graphics->_sprite.move(direction);
		
		if(OutOfBounds(player))
			player._graphics->_sprite.setPosition(previousPos);
	}
}
