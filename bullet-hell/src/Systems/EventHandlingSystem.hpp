#pragma once
#include "../Component.hpp"
#include "../System.hpp"

class EventHandlingSystem : public System
{
public:
    void Update(entt::registry& reg, const float& dt = 0.f, entt::entity ent = entt::null)
    {
        HealthUpdate(reg);
        IframeUpdate(reg);
        VelocityUpdate(reg);
        PossibleCleanUp(reg);
    }

    void HealthUpdate(entt::registry& reg)
    {
        auto group = reg.group<Health>(entt::get<CollidedTag>);
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

    void IframeUpdate(entt::registry& reg)
    {

    }

    void PossibleCleanUp(entt::registry& reg)
    {
        auto view = reg.view<DestroyTag>();
        for (auto entity : view)
            reg.destroy(entity);
    }
};