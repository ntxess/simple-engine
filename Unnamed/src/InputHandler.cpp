#include "InputHandler.hpp"


InputHandler::InputHandler() 
{}

InputHandler::~InputHandler()
{}

void InputHandler::HandleInput(GameObject& actor)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) actor.Input()->MoveUp();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) actor.Input()->MoveLeft();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) actor.Input()->MoveDown();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) actor.Input()->MoveRight();
}