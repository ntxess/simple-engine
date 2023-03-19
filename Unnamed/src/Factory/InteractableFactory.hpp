#pragma once
#include "AbstractFactory.hpp"

class InteractableFactory : public AbstractFactory
{
private:
	std::shared_ptr<GameData> m_data;
	Scene* m_currentScene;

public:
	InteractableFactory(std::shared_ptr<GameData> data, Scene* currentScene)
		: m_data(data), m_currentScene(currentScene) {}
	~InteractableFactory() = default;

	std::unique_ptr<Entity> CreateEntity(TYPE type, sf::Texture& texture) const override;
};

