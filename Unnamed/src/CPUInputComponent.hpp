#pragma once
#include <iostream>
#include "InputComponent.hpp"

class CPUInputComponent : public InputComponent
{
public:
	CPUInputComponent();
	void MoveUp();
	void MoveLeft();
	void MoveDown();
	void MoveRight();
};