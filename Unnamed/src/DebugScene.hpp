#pragma once
#include <iostream>
#include <vector>
#include "GameData.hpp"

#include "MainMenu.hpp"
#include "ResourceMonitor.hpp"
#include "GameObject.hpp"
#include "InputHandler.hpp"
#include "PlayerInput.hpp"
#include "RigidbodyBox.hpp"
#include "ShipAnimation.hpp"
#include "PlayerIdentity.hpp"
#include "ProjectilePhysics.hpp"

typedef std::unique_ptr<Component> ComponentRef;
typedef std::unique_ptr<Player> PlayerRef;

class DebugScene : public State
{
private:
	std::shared_ptr<GameData> _data;

public:
	InputHandler _inputHandler;
	ResourceMonitor _fps;
	PlayerRef _player;

	std::vector<ComponentRef> _assets;

	DebugScene(std::shared_ptr<GameData> &data);
	~DebugScene();
	void Init();
	void ProcessInput();
	void Update(float deltaTime);
	void Render(RenderWindowRef& rw, float interpolation);
	void CheckBoundary(ComponentRef& object);
	bool CheckCollision(ComponentRef& player, ComponentRef& object);
	void Pause();
	void Resume();
};