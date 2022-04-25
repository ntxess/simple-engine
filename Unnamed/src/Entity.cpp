#include "Entity.hpp"

Entity::Entity() 
	: _entityHandle((entt::entity)0)
	, _scene(nullptr)
{}

Entity::Entity(entt::entity handle, Scene* scene)
	: _entityHandle(handle)
	, _scene(scene)
{}

Entity::~Entity()
{}

entt::entity Entity::GetHandle()
{
	return _entityHandle;
}
