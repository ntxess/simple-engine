#pragma once
#include <iostream>
#include "SFML/Window/Keyboard.hpp"
#include "Command.hpp"
#include "GameObject.hpp"

typedef std::shared_ptr<Command> CommandRef;

class InputHandler
{
private:
	CommandRef _buttonW;
	CommandRef _buttonA;
	CommandRef _buttonS;
	CommandRef _buttonD;

public:
	InputHandler();
	~InputHandler();
	void BindCommand();
	CommandRef HandleInput();
};