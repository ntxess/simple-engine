#pragma once
#include "../Component.hpp"
#include "../System.hpp"
#include <numbers>

class WaypointSystem : public System
{
public:
    void Update(entt::registry& reg, const float& dt = 0.f, entt::entity ent = entt::null)
    {
        auto group = reg.group<MovementPattern, Speed>(entt::get<Sprite>);
        for (auto entity : group)
        {
            auto [wpc, spd, sp] = group.get<MovementPattern, Speed, Sprite>(entity);

            Waypoint* headPtr = wpc.currentPath;
            Waypoint* nextPtr = headPtr->nextWP.get();

            if (nextPtr == nullptr)
            {
                if (wpc.repeat)
                {
                    wpc.currentPath = wpc.movePattern;
                    wpc.distance = 0.f;
                }
                continue;
            }

            wpc.distance += spd.current * dt;
            if (wpc.distance > nextPtr->distanceTotal)
                wpc.currentPath = nextPtr;

            sf::Vector2f unitDist;
            unitDist.x = (nextPtr->location.x - headPtr->location.x) / headPtr->distanceToNext;
            unitDist.y = (nextPtr->location.y - headPtr->location.y) / headPtr->distanceToNext;

            sf::Vector2f velocity;
            velocity.x = unitDist.x * spd.current * dt;
            velocity.y = unitDist.y * spd.current * dt;

            float theta = (atan2(velocity.y, velocity.x)) * (180.f / float(std::numbers::pi));
            sp.sprite.setRotation(theta + 90);
            sp.sprite.move(velocity);
        }
    }
};