#pragma once
#include <iostream>
#include <vector>
#include "GameData.hpp"

#include "MainMenu.hpp"
#include "ResourceMonitor.hpp"
#include "Component.hpp"
#include "PlayerInput.hpp"
#include "RigidbodyBox.hpp"
#include "ShipAnimation.hpp"
#include "Player.hpp"
#include "Thor/Particles.hpp"

typedef std::unique_ptr<Component> ComponentRef;
typedef std::unique_ptr<Player> PlayerRef;

class DebugScene : public State
{
private:
	std::shared_ptr<GameData> _data;

public:
	ResourceMonitor _fps;
	PlayerRef _player;
	std::vector<ComponentRef> _assets;
	thor::ParticleSystem _particleSystem;

	DebugScene(std::shared_ptr<GameData> &data);
	~DebugScene();
	void Init();
	void ProcessInput(sf::Event event);
	void Update(float deltaTime);
	void Render(RenderWindowRef& rw, float interpolation);
	void CheckBoundary(ComponentRef& object);
	bool CheckCollision(ComponentRef& player, ComponentRef& object);
	void Pause();
	void Resume();
};