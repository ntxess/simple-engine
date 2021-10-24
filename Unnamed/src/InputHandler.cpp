#include "InputHandler.hpp"

InputHandler::InputHandler()
{
	BindCommand();
}

InputHandler::~InputHandler()
{}

void InputHandler::BindCommand()
{
	_buttonW = std::make_shared<CommandUp>();
	_buttonA = std::make_shared<CommandLeft>();
	_buttonS = std::make_shared<CommandDown>();
	_buttonD = std::make_shared<CommandRight>();
}

CommandRef InputHandler::HandleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) return _buttonW;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) return _buttonA;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) return _buttonS;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) return _buttonD;
}