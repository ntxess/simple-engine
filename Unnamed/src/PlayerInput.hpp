#pragma once
#include <iostream>
#include "InputComponent.hpp"

class PlayerInput : public InputComponent
{
public:
	PlayerInput();
	void MoveUp();
	void MoveLeft();
	void MoveDown();
	void MoveRight();
};