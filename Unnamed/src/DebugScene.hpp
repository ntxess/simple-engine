#pragma once
#include <iostream>
#include <vector>
#include "GameData.hpp"

#include "MainMenu.hpp"
#include "ResourceMonitor.hpp"
#include "GameObject.hpp"
#include "InputHandler.hpp"
#include "PlayerInput.hpp"
#include "CPUInput.hpp"

typedef std::unique_ptr<GameObject> GameObjectRef;

class DebugScene : public State
{
private:
	std::shared_ptr<GameData> _data;

public:
	ResourceMonitor _fps;
	InputHandler _inputHandler;
	GameObjectRef _player;
	std::vector<GameObjectRef> _assets;

	DebugScene(std::shared_ptr<GameData> &data);
	~DebugScene();
	void Init();
	void ProcessInput();
	void Update(float deltaTime);
	void Render(RenderWindowRef& rw, float interpolation);
	void CheckBoundary(GameObjectRef& object);
	void Pause();
	void Resume();
};