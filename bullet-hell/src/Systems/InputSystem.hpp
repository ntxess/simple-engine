#pragma once
#include "../Component.hpp"
#include "../System.hpp"
#include <cmath>

class InputSystem : public System
{
public:
    void Update(const float& dt, entt::registry& reg, entt::entity ent = entt::null)
    {
		auto controller = reg.get<PlayerInput>(ent);
		auto& player = reg.get<AnimatedSprite>(ent).sprite;
		auto speed = reg.get<Speed>(ent).current;

		sf::Vector2f velocity = controller.direction;

		// Normalizing the vector to prevent diagonal movement from being faster than the cardinal directions
		float length = sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));

		if (length != 0.f)
		{
			velocity.x /= length;
			velocity.y /= length;
		}

		velocity *= speed * dt;
		//float theta = (atan2(velocity.y, velocity.x)) * (180.f / std::numbers::pi);
		//player.setRotation(theta + 90);
		player.move(velocity);
    }
};