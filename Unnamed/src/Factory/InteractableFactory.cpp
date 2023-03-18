#include "InteractableFactory.hpp"

std::unique_ptr<Entity> InteractableFactory::CreateEntity(TYPE type) const
{
	entt::entity handle = m_currentScene->GetRegistry().create();
	std::unique_ptr<Entity> entity = std::make_unique<Entity>(handle, m_currentScene);

	switch (type)
	{
	case TYPE::PLAYER:
		entity->AddComponent<AnimatedSprite>(m_data->textureManager["SP_Player"]);
		entity->AddComponent<Health>(100.f);
		entity->AddComponent<Speed>(20.f);
		entity->AddComponent<Attack>(10.f);
		//entity->AddComponent<PlayerTag>();
		break;
	case TYPE::ENEMY:
		entity->AddComponent<Sprite>(m_data->textureManager["SP_Enemy"]);
		entity->AddComponent<Health>(200.f);
		entity->AddComponent<Speed>(10.f);
		entity->AddComponent<Attack>(5.f);
		//entity->AddComponent<EnemyTag>();
		break;
	case TYPE::FRIENDLY:
		// TODO:
		break;
	default:
		// TODO:
		break;
	}
	return std::move(entity);
}
