#include "PlayerPhysics.hpp"

PlayerPhysics::PlayerPhysics()
	: _previousPos(sf::Vector2u(0, 0))
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

	_previousPos = player._graphics->_sprite.getPosition();
	player._graphics->_sprite.move(direction);

	//sf::Vector2f dodge(0, 0);
	//PlayerInput::COMMAND command = player._input->_command;
	//if (command == PlayerInput::COMMAND::DODGE)
	//{
	//	std::cout << "Dodging in Update" << std::endl;
	//	dodge.x = 5.f;
	//	dodge.y = 5.f;
	//}

	//if (command == PlayerInput::COMMAND::EX_SKILL)
	//{

	//	std::cout << "Using EX_Skill in Update" << std::endl;
	//}

	//sf::Vector2f direction = player._input->_direction;
	//direction.x = (direction.x * deltaTime * player._currentStats.SPD) + (dodge.x * direction.x);
	//direction.y = (direction.y * deltaTime * player._currentStats.SPD) + (dodge.y * direction.y);

	//_previousPos = player._graphics->_sprite.getPosition();
	//player._graphics->_sprite.move(direction);
}
