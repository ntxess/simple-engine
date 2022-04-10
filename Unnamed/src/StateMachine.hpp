#pragma once
#include <memory>
#include <stack>
#include "State.hpp"

class StateMachine
{
private:
	std::stack<std::unique_ptr<State>> _states;
	std::unique_ptr<State> _newState;

	bool _isRemoving;
	bool _isAdding;
	bool _isReplacing;

public:
	StateMachine();
	~StateMachine();
	void AddState(std::unique_ptr<State> newState, bool isReplacing = true);
	void RemoveState();
	void ProcessStateChange();
	std::unique_ptr<State>& GetActiveState();
};