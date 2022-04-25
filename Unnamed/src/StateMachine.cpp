#include "StateMachine.hpp"

StateMachine::StateMachine()
{}

StateMachine::~StateMachine()
{}

void StateMachine::AddState(std::unique_ptr<Scene> newState, bool isReplacing)
{
	_isAdding = true;
	_isReplacing = isReplacing;

	_newScene = std::move(newState);
}

void StateMachine::RemoveState()
{
	_isRemoving = true;
}

void StateMachine::ProcessStateChange()
{
	if (_isRemoving && !_scenes.empty())
	{
		_scenes.pop();
		if (!_scenes.empty())
		{
			_scenes.top()->Resume();
		}
		_isRemoving = false;
	}

	if (_isAdding)
	{
		if (!_scenes.empty())
		{
			if (_isReplacing)
			{
				_scenes.pop();
			}
			else
			{
				_scenes.top()->Pause();
			}
		}
		_scenes.push(std::move(_newScene));
		_scenes.top()->Init();
		_isAdding = false;
	}
}

std::unique_ptr<Scene>& StateMachine::GetActiveState()
{
	return _scenes.top();
}
