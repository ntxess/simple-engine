#pragma once
#include "../System.hpp"
#include <vector>

class SystemManager 
{
private:
    std::vector<std::unique_ptr<System>> m_systems;

public:
    template<typename T, typename... Args>
    void AddSystem(Args&&... args) 
    {
        m_systems.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
    }

    template<typename T>
    T* GetSystem() {
        for (auto& system : m_systems) 
        {
            if (typeid(*system) == typeid(T)) 
            {
                return static_cast<T*>(system.get());
            }
        }
        return nullptr;
    }

    void Update(const float& dt, entt::registry& reg)
    {
        for (auto& system : m_systems) 
        {
            system->Update(dt, reg);
        }
    }
};


