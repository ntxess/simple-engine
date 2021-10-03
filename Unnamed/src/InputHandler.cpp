#include "InputHandler.hpp"

InputHandler::InputHandler() 
{
	BindCommand();
}

InputHandler::~InputHandler()
{
	delete _buttonW;
	delete _buttonS;
	delete _buttonA;
	delete _buttonD;
	delete _buttonSpace;
}

Command* InputHandler::HandleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) return _buttonW;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) return _buttonS;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) return _buttonA;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) return _buttonD;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) return _buttonSpace;
}

void InputHandler::BindCommand()
{
	_buttonSpace = new JumpCommand();
}