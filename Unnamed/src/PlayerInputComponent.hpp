#pragma once
#include <iostream>
#include "InputComponent.hpp"

class PlayerInputComponent : public InputComponent
{
public:
	PlayerInputComponent();
	void MoveUp();
	void MoveLeft();
	void MoveDown();
	void MoveRight();
};