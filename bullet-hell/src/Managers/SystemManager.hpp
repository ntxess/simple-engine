#pragma once
#include "../System.hpp"
#include <typeindex>
#include <unordered_map>

class SystemManager
{
private:
    std::unordered_map<std::type_index, std::unique_ptr<System>> m_systems;

public:
    template<typename T, typename... Args>
    void AddSystem(Args&&... args)
    {
        m_systems.emplace(typeid(T), std::make_unique<T>(std::forward<Args>(args)...));
    }

    template<typename T>
    T* GetSystem() {
        auto it = m_systems.find(typeid(T));
        if (it != m_systems.end())
            return static_cast<T*>(it->second.get());
        return nullptr;
    }

    void Update(entt::registry& reg, const float& dt = 0.f, entt::entity ent = entt::null)
    {
        for (auto& system : m_systems)
            system.second->Update(reg, dt, ent);
    }
};

