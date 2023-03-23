#pragma once
#include "../GameData.hpp"
#include "../Component.hpp"
#include "../Entity.hpp"
#include "../AbstractFactory.hpp"
#include "../Factory/InteractableFactory.hpp"
#include "../Factory/NonInteractableFactory.hpp"
#include "../../SFML-imgui/imgui.h"
#include "../../SFML-imgui/imgui-SFML.h"
#include <numbers>

class EmptyScene : public Scene
{
private:
	std::shared_ptr<GameData> m_data;
	std::unordered_map<std::string, std::unique_ptr<Entity>> m_entity;
	entt::registry m_reg;
	
public:
	EmptyScene(std::shared_ptr<GameData>& data);
	~EmptyScene();

	void Init();
	void ProcessEvent(const sf::Event& event);
	void ProcessInput();
	void Update(const float& deltaTime);
	void Render(sf::RenderWindow& rw, const float& deltaTime, const float& interpolation);
	void Pause();
	void Resume();
	entt::registry& GetRegistry();

	void LoadResources();
	void BuildEntities();
	void SetupScene();
	void WaypointUpdate(const float& dt);
};
