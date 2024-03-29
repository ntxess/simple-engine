#pragma once
#include "../Component.hpp"
#include "../System.hpp"
#include <numbers>

class TrackingSystem : public System
{
public:
    void Update(const float& dt, entt::registry& reg, entt::entity ent = entt::null)
    {
		auto view = reg.view<Attraction>();

		for (auto entity : view)
		{
			auto& tracker = reg.get<AnimatedSprite>(entity).sprite;
			auto target = reg.get<AnimatedSprite>(ent).sprite;

			auto attraction = reg.get<Attraction>(entity);
			auto speed = reg.get<Speed>(entity).current;

			float targetX = target.getPosition().x;
			float targetY = target.getPosition().y;
			float trackerX = tracker.getPosition().x;
			float trackerY = tracker.getPosition().y;

			float distance = sqrt((targetX - trackerX) * (targetX - trackerX) +
				(targetY - trackerY) * (targetY - trackerY));

			if (distance <= attraction.power.level || attraction.power.fullStrength)
			{
				sf::Vector2f unitDist;
				unitDist.x = (targetX - trackerX) / distance;
				unitDist.y = (targetY - trackerY) / distance;

				sf::Vector2f velocity;
				velocity.x = unitDist.x * speed * dt;
				velocity.y = unitDist.y * speed * dt;

				float theta = (atan2(velocity.y, velocity.x)) * (180.f / std::numbers::pi);
				tracker.setRotation(theta + 90);
				tracker.move(velocity);
			}
		}
    }
};