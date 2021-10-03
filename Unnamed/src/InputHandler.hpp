#pragma once
#include "SFML/Window/Keyboard.hpp"

#include "Command.hpp"

class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	Command* HandleInput();
	void BindCommand();

private:
	Command* _buttonW;
	Command* _buttonS;
	Command* _buttonA;
	Command* _buttonD;
	Command* _buttonSpace;
	//Command* _button;
	//Command* _button;
	//Command* _button;
};