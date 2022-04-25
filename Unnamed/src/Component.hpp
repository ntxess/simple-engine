#pragma once
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "WayPoint.hpp"

class TagComponent
{
	std::string nametag;

	TagComponent() = default;
	TagComponent(const std::string& name)
		: nametag(name) {}
	TagComponent(const TagComponent&) = default;
};

struct SpriteComponent
{
	sf::Sprite sprite;

	SpriteComponent() = default;
	SpriteComponent(sf::Texture& texture)
	{
		sprite.setTexture(texture);
		sprite.setOrigin(float(texture.getSize().x / 2), float(texture.getSize().y / 2));
	}
	SpriteComponent(const SpriteComponent&) = default;
};

struct HealthComponent
{
	float max;
	float current;

	HealthComponent() = default;
	HealthComponent(const float& health)
		: max(health), current(health) {}
	HealthComponent(const HealthComponent&) = default;
};

struct SpeedComponent
{
	float max;
	float current;

	SpeedComponent() = default;
	SpeedComponent(const float& speed)
		: max(speed), current(speed) {}
	SpeedComponent(const SpeedComponent&) = default;
};

struct DamageComponent
{
	float damage;

	DamageComponent() = default;
	DamageComponent(const float& damage)
		: damage(damage) {}
	DamageComponent(const DamageComponent&) = default;
};

struct WayPointComponent
{
	WayPoint* movePattern;
	WayPoint* currentPath;
	float distance;
	bool repeat;

	WayPointComponent() = default;
	WayPointComponent(WayPoint* wp, const bool& repeat = false)
		: movePattern(&*wp), currentPath(&*wp), distance(0.0f), repeat(repeat) {}
	WayPointComponent(const WayPointComponent&) = default;
};
