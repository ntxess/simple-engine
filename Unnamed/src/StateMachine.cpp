#include "StateMachine.hpp"

StateMachine::StateMachine()
{}

StateMachine::~StateMachine()
{}

void StateMachine::AddState(std::unique_ptr<State> newState, bool isReplacing)
{
	_isAdding = true;
	_isReplacing = isReplacing;

	_newState = std::move(newState);
}

void StateMachine::RemoveState()
{
	_isRemoving = true;
}

void StateMachine::ProcessStateChange()
{
	if (_isRemoving && !_states.empty())
	{
		_states.pop();
		if (!_states.empty())
		{
			_states.top()->Resume();
		}
		_isRemoving = false;
	}

	if (_isAdding)
	{
		if (!_states.empty())
		{
			if (_isReplacing)
			{
				_states.pop();
			}
			else
			{
				_states.top()->Pause();
			}
		}
		_states.push(std::move(_newState));
		_states.top()->Init();
		_isAdding = false;
	}
}

std::unique_ptr<State>& StateMachine::GetActiveState()
{
	return _states.top();
}
