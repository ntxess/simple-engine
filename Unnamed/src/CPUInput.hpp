#pragma once
#include <iostream>
#include "InputComponent.hpp"

class CPUInput : public InputComponent
{
public:
	CPUInput();
	void MoveUp();
	void MoveLeft();
	void MoveDown();
	void MoveRight();
};