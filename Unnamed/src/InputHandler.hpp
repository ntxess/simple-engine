#pragma once
#include <iostream>
#include "SFML/Window/Keyboard.hpp"
#include "Command.hpp"
#include "GameObject.hpp"

class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	void HandleInput(GameObject& actor);
};