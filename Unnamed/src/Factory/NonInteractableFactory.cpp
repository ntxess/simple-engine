#include "NonInteractableFactory.hpp"

std::unique_ptr<Entity> NonInteractableFactory::CreateEntity(TYPE type) const
{
	entt::entity handle = m_currentScene->GetRegistry().create();
	std::unique_ptr<Entity> entity = std::make_unique<Entity>(handle, m_currentScene);

	switch (type)
	{
	case TYPE::BACKGROUND:
		entity->AddComponent<Sprite>(
			m_data->textureManager["BG_Space"],
			m_data->window.getSize().x,
			m_data->window.getSize().y,
			true);
		break;
	case TYPE::OBJECT:
		entity->AddComponent<Sprite>(m_data->textureManager["Object"]);
		break;
	default:
		// TODO:
		break;
	}
	return std::move(entity);
}
