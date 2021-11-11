#include "InputHandler.hpp"

InputHandler::InputHandler()
{}

InputHandler::~InputHandler() 
{}

void InputHandler::HandleInput(GameObject& actor)
{
	float horizontal = 0, vertical = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		vertical = -1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		horizontal = -1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		vertical = 1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		horizontal = 1;

	if(horizontal || vertical)
		actor.GetInput()->Move(sf::Vector2f(horizontal, vertical));
}