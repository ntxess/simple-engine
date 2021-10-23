#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "ResourceMonitor.hpp"
#include "StateMachine.hpp"
#include "InputHandler.hpp"

#include "GameObject.hpp"
#include "PlayerInput.hpp"
#include "CPUInput.hpp"
#include "MusicNote.hpp"

typedef std::shared_ptr<GameObject> GameObjectRef;

class DebugScene : public State
{
public:
	ResourceMonitor _fps;
	InputHandler _inputHandler;
	GameObjectRef _currentFocus;
	std::vector<GameObjectRef> _entityAll;
	std::vector<GameObjectRef> _entityLive;

	DebugScene();
	~DebugScene();
	void Init();
	void ProcessInput();
	void Update(float deltaTime);
	void Render(sf::RenderWindow &rw, float interpolation);
	void Pause();
	void Resume();
};