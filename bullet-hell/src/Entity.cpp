#include "Entity.hpp"

Entity::Entity() 
	: m_entityHandle((entt::entity)0)
	, m_scene(nullptr)
{}

Entity::Entity(Scene* scene)
	: m_scene(scene)
{
	m_entityHandle = scene->GetRegistry().create();
}

Entity::Entity(entt::entity handle, Scene* scene)
	: m_entityHandle(handle)
	, m_scene(scene)
{}

Entity::~Entity()
{}

entt::entity Entity::GetHandle()
{
	return m_entityHandle;
}
