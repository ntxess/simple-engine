#pragma once
#include <iostream>
#include <vector>
#include "GameData.hpp"

#include "DebugScene.hpp"
#include "ResourceMonitor.hpp"
#include "GameObject.hpp"
#include "Background.hpp"

typedef std::shared_ptr<GameObject> GameObjectRef;

class MainMenu : public State
{
private:
    std::shared_ptr<GameData> _data;

public:
	ResourceMonitor _fps;
	std::vector<GameObjectRef> _assets;

	MainMenu(std::shared_ptr<GameData>& data);
	~MainMenu();
	void Init();
	void ProcessInput();
	void Update(float deltaTime);
	void Render(RenderWindowRef& rw, float interpolation);
	void Pause();
	void Resume();
};