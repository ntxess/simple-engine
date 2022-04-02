#include "PlayerPhysics.hpp"

PlayerPhysics::PlayerPhysics()
{}

PlayerPhysics::~PlayerPhysics()
{}

void PlayerPhysics::Update(Player& player, float deltaTime)
{
	CommandRef command = player._input->_command;
	if (command)
		command->Execute();
	
	sf::Vector2f direction = player._input->_direction;
	direction.x = direction.x * deltaTime * player._currentStats.SPD;
	direction.y = direction.y * deltaTime * player._currentStats.SPD;

	if (direction != sf::Vector2f(0, 0))
		player._graphics->_sprite.move(direction);
}
