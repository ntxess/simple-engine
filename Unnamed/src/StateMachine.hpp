#pragma once
#include <memory>
#include <stack>
#include "Scene.hpp"

class StateMachine
{
private:
	std::stack<std::unique_ptr<Scene>> _scenes;
	std::unique_ptr<Scene> _newScene;

	bool _isRemoving;
	bool _isAdding;
	bool _isReplacing;

public:
	StateMachine();
	~StateMachine();
	void AddState(std::unique_ptr<Scene> newState, bool isReplacing = true);
	void RemoveState();
	void ProcessStateChange();
	std::unique_ptr<Scene>& GetActiveState();
};