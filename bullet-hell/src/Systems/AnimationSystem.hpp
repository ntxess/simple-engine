#pragma once
#include "../Component.hpp"
#include "../System.hpp"
#include "SFML/System/Time.hpp"

class AnimationSystem : public System
{
public:
	void Update(const float& dt, entt::registry& reg, entt::entity ent = entt::null)
	{
		auto view = reg.view<AnimatedSprite>();
		for (auto entity : view)
		{
			auto& animator = view.get<AnimatedSprite>(entity).animator;
			auto& sprite = view.get<AnimatedSprite>(entity).sprite;
			animator.update(sf::seconds(dt));
			animator.animate(sprite);
		}
	}

	void DetermineAnimation(entt::registry& reg)
	{
		//auto view = reg.view<AnimatedSprite>();
		//for (auto entity : view)
		//{
		//	entity
		//}
	}

	//void Animate(const float& dt, entt::registry& reg, entt::entity ent = entt::null)
	//{
	//	auto view = reg.view<AnimatedSprite>();
	//	for (auto entity : view)
	//	{
	//		auto& animator = view.get<AnimatedSprite>(entity).animator;
	//		auto& sprite = view.get<AnimatedSprite>(entity).sprite;
	//		animator.animate(sprite);
	//	}
	//}
};