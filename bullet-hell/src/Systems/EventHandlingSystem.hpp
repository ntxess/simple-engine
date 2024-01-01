#pragma once
#include "../Component.hpp"
#include "../System.hpp"

class EventHandlingSystem : public System
{
public:
    void Update(entt::registry& reg, const float& dt = 0.f, entt::entity ent = entt::null)
    {
        IframeUpdate(reg, dt);
        HealthUpdate(reg);
        VelocityUpdate(reg);
        PossibleCleanUp(reg);
    }

    void IframeUpdate(entt::registry& reg, const float& dt)
    {
        auto view = reg.view<IFrameClock>();
        for (auto entity : view)
        {
            float& currentFrame = reg.get<IFrameClock>(entity).currentFrame;
            const float maxFrame = reg.get<IFrameClock>(entity).maxFrame;

            currentFrame += 1;

            std::cout << currentFrame << std::endl;
            if (reg.get<IFrameClock>(entity).currentFrame == maxFrame)
                reg.remove<IFrameClock>(entity);
        }
    }

    void HealthUpdate(entt::registry& reg)
    {
        auto group = reg.group<Health>(entt::get<CollidedTag>, entt::exclude<IFrameClock>);
        for (auto responderEntity : group)
        {
            auto colliderEntity = reg.get<CollidedTag>(responderEntity).collider;
            if (!reg.valid(colliderEntity))
                continue;

            auto colliderAtkDmg = reg.get<Attack>(colliderEntity).damage;

            if (reg.get<Health>(responderEntity).DecreaseHealth(colliderAtkDmg) <= 0.f) 
	            reg.emplace_or_replace<DestroyTag>(responderEntity);
        }
    }

    void VelocityUpdate(entt::registry& reg)
    {
        
    }

    void PossibleCleanUp(entt::registry& reg)
    {
        auto view = reg.view<DestroyTag>();
        for (auto entity : view)
            reg.destroy(entity);
    }
};