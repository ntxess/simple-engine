#pragma once
#include "../AbstractFactory.hpp"

class NonInteractableFactory : public AbstractFactory
{
private:
	std::shared_ptr<GameData> m_data;
	Scene* m_currentScene;

public:
	NonInteractableFactory(std::shared_ptr<GameData> data, Scene* currentScene)
		: m_data(data), m_currentScene(currentScene) {}
	~NonInteractableFactory() = default;

	std::unique_ptr<Entity> CreateEntity(TYPE type, sf::Texture& texture) const override;
};

