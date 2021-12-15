#pragma once
#include <iostream>
#include <vector>
#include "GameData.hpp"
#include "MainMenu.hpp"
#include "ResourceMonitor.hpp"
#include "GameObject.hpp"
#include "ShipAnimation.hpp"
#include "Player.hpp"
#include "ShotParticle.hpp"

typedef std::unique_ptr<GameObject> GameObjectRef;
typedef std::unique_ptr<Player> PlayerRef;

class DebugScene : public State
{
private:
	//static const uint16_t MAX_ENTITIES = 100000;
	std::shared_ptr<GameData> _data;

public:
	ResourceMonitor _fps;
	PlayerRef _player;
	GameObjectRef _background;
	//PhysicsComponent* _physicsComponent = new PhysicsComponent[MAX_ENTITIES];
	//std::vector<PhysicsComponent> _physicsComponent;
	//std::vector<GraphicsComponent> _graphicsComponent;

	std::vector<GameObjectRef> _assets;

	DebugScene(std::shared_ptr<GameData> &data);
	~DebugScene();
	void Init();
	void ProcessInput(sf::Event event);
	void Update(float deltaTime);
	void Render(RenderWindowRef& rw, float interpolation);
	void CheckBoundary(GameObjectRef& object);
	bool CheckCollision(GameObjectRef& player, GameObjectRef& object);
	void SpawnShotParticle();
	void Pause();
	void Resume();
};