#pragma once
#include "Scene.hpp"
#include "entt/entt.hpp"
using namespace entt::literals;

class Entity
{
private:
	entt::entity m_entityHandle;
	Scene* m_scene;

public:
	Entity();
	Entity(Scene* scene);
	Entity(entt::entity handle, Scene* scene);
	~Entity() = default;
	Entity(const Entity& other) = default;

	entt::entity GetHandle();

	template<typename T>
	void AssignTag(entt::basic_hashed_string<char> tag);

	template<typename T, typename... Args>
	void AddComponent(Args&&... args);

	template<typename T>
	T& GetComponent();

	template<typename T>
	bool HasComponent();

	template<typename T>
	void RemoveComponent();

	operator bool() const { return m_entityHandle != (entt::entity)0; }
};

template<typename T>
inline void Entity::AssignTag(entt::basic_hashed_string<char> tag)
{
	m_scene->GetRegistry().emplace_or_replace<T>(m_entityHandle, tag);
}

template<typename T, typename... Args>
inline void Entity::AddComponent(Args&&... args)
{
	m_scene->GetRegistry().emplace<T>(m_entityHandle, std::forward<Args>(args)...);
}

template<typename T>
inline T& Entity::GetComponent()
{
	return m_scene->GetRegistry().get<T>(m_entityHandle);
}

template<typename T>
inline bool Entity::HasComponent()
{
	return m_scene->GetRegistry().all_of<T>(m_entityHandle);
}

template<typename T>
inline void Entity::RemoveComponent()
{
	m_scene->GetRegistry().remove<T>(m_entityHandle);
}
