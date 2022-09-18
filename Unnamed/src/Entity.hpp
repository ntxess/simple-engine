#pragma once

#include "entt/entt.hpp"
#include "Scene.hpp"

class Entity
{
private:
	entt::entity _entityHandle;
	Scene* _scene;

public:
	Entity();
	Entity(entt::entity handle, Scene* scene);
	~Entity();
	Entity(const Entity& other) = default;

	entt::entity GetHandle();

	template<typename T, typename... Args>
	T& AddComponent(Args&&... args);

	template<typename T>
	T& GetComponent();

	template<typename T>
	bool HasComponent();

	template<typename T>
	void RemoveComponent();

	operator bool() const { return _entityHandle != (entt::entity)0; }
};

template<typename T, typename... Args>
inline T& Entity::AddComponent(Args&&... args)
{
	return _scene->GetRegistry().emplace<T>(_entityHandle, std::forward<Args>(args)...);
}

template<typename T>
inline T& Entity::GetComponent()
{
	return _scene->GetRegistry().get<T>(_entityHandle);
}

template<typename T>
inline bool Entity::HasComponent()
{
	return _scene->GetRegistry().all_of<T>(_entityHandle);
}

template<typename T>
inline void Entity::RemoveComponent()
{
	_scene->GetRegistry().remove<T>(_entityHandle);
}
