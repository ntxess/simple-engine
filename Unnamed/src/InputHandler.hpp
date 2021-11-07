#pragma once
#include <iostream>
#include "SFML/Window/Keyboard.hpp"
#include "GameObject.hpp"

class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	void HandleInput(GameObject& actor);
};