#include "InputHandler.hpp"

InputHandler::InputHandler()
{}

InputHandler::~InputHandler() 
{}

void InputHandler::HandleInput(Component& actor)
{
	float horizontal = 0, vertical = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		vertical = -1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		horizontal = -1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		vertical = 1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		horizontal = 1;

	if(horizontal || vertical)
		actor.GetInput()->Move(sf::Vector2f(horizontal, vertical));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		actor.GetInput()->Shoot(true);
}