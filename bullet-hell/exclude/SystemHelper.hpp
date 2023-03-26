#pragma once
#include <memory>
#include <string>
#include <numbers>

#include "SFML/Graphics/Sprite.hpp"
#include "entt/entt.hpp" 
#include "Component.hpp"
#include "QuadTree.hpp"
#include "Event.hpp"
#include "EventDispatcher.hpp"
#include "EventHandler.hpp"

namespace SystemHelper
{
	void InputMovementUpdate(entt::registry& reg, entt::entity ent, const float& dt);
	void CheckBoundary(const sf::Vector2u& boundary, sf::Sprite& obj);
	void FocusCameraOn(sf::View& vw, sf::Sprite& obj);
	void MobWaypointUpdate(entt::registry& reg, const float& dt);
	void MobTrackingUpdate(entt::registry& reg, entt::entity ent, const float& dt);
	std::unique_ptr<QuadTree> QuadTreeUpdate(entt::registry& reg, const sf::Vector2f& vwCenter, const sf::Vector2f& rwSize);
	void CollisionUpdate(entt::registry& reg, const std::unique_ptr<QuadTree>& qt);
	void DamageUpdate(entt::registry& reg, entt::entity inflictor, entt::entity inflicted);
	void CheckDestruction(entt::registry& reg);
	void PerformanceMetricUpdate(entt::registry& reg, entt::entity ent, const std::unique_ptr<sf::RenderWindow>& rw);
	void RotateTurretUpdate(entt::registry& reg, entt::entity ent, const float& dt);
	void VelocityUpdate(entt::registry& reg, entt::entity ent, const float& dt);
	void GravityUpdate(entt::registry& reg, entt::entity ent, const float& dt);
	void RotateTowards(entt::registry& reg, entt::entity ent, sf::Vector2f velocity);
	void ScrollBackground(entt::registry& reg, entt::entity current, entt::entity next, const float& dt);
}