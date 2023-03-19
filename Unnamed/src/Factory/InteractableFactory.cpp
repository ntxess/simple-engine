#include "InteractableFactory.hpp"

std::unique_ptr<Entity> InteractableFactory::CreateEntity(TYPE type, sf::Texture& texture) const
{
	entt::entity handle = m_currentScene->GetRegistry().create();
	std::unique_ptr<Entity> entity = std::make_unique<Entity>(handle, m_currentScene);

	switch (type)
	{
	case TYPE::PLAYER:
		entity->AddComponent<AnimatedSprite>(texture);
		entity->AddComponent<Health>(100.f);
		entity->AddComponent<Speed>(20.f);
		entity->AddComponent<Attack>(10.f);
		entity->GetComponent<AnimatedSprite>().animator.addAnimation(
			"playerIdle", 
			m_data->animationManager.GetAnimation("player_idle"), 
			sf::seconds(1.f)
		);
		break;
	case TYPE::ENEMY:
		entity->AddComponent<AnimatedSprite>(texture);
		entity->AddComponent<Health>(200.f);
		entity->AddComponent<Speed>(10.f);
		entity->AddComponent<Attack>(5.f);
		break;
	case TYPE::FRIENDLY:
		entity->AddComponent<AnimatedSprite>(texture);
		entity->AddComponent<Health>(100.f);
		entity->AddComponent<Speed>(20.f);
		entity->AddComponent<Attack>(10.f);
		break;
	case TYPE::OBJECT:
		entity->AddComponent<Sprite>(texture);
		entity->AddComponent<Health>(100.f);
		break;
	default:
		// TODO:
		break;
	}
	return std::move(entity);
}
