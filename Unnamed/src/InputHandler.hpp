#pragma once
#include "SFML/Window/Keyboard.hpp"
#include "Command.hpp"

class InputHandler
{
private:
	Command* _buttonW;
	Command* _buttonA;
	Command* _buttonS;
	Command* _buttonD;
public:
	InputHandler();
	~InputHandler();
	Command* HandleInput();
	void BindCommand();
};