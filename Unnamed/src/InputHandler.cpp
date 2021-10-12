#include "InputHandler.hpp"

InputHandler::InputHandler() 
{
	BindCommand();
}

InputHandler::~InputHandler()
{
	delete _buttonW;
	delete _buttonA;
	delete _buttonS;
	delete _buttonD;
}

Command* InputHandler::HandleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) return _buttonW;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) return _buttonA;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) return _buttonS;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) return _buttonD;
	return nullptr;
}

void InputHandler::BindCommand()
{
	_buttonW = new CMDMoveUp();
	_buttonA = new CMDMoveLeft();
	_buttonS = new CMDMoveDown();
	_buttonD = new CMDMoveRight();
}