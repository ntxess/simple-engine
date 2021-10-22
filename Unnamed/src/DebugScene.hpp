#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "InputHandler.hpp"
#include "GameObject.hpp"
#include "FPSTracker.hpp"
#include "PlayerInput.hpp"
#include "CPUInput.hpp"
#include "Sprite.hpp"
#include "MusicNote.hpp"

typedef std::shared_ptr<GameObject> GameObjectRef;

class DebugScene : public State
{
public:
	InputHandler _inputHandler;
	GameObjectRef _currentFocus;
	std::vector<GameObjectRef> _entityAll;
	std::vector<GameObjectRef> _entityLive;

	DebugScene();
	~DebugScene();
	void Init();
	void ProcessInput();
	void Update(double deltaTime);
	void Render(sf::RenderWindow* rt, double interpolation);
	void Pause();
	void Resume();
};