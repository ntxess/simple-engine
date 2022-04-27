#pragma once
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "WayPoint.hpp"
#include "CommandDodge.hpp"
#include "CommandExSkill.hpp"

struct TagComponent
{
	std::string name;

	TagComponent() = default;
	TagComponent(const std::string& nametag)
		: name(nametag) {}
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
	bool finish;

	WayPointComponent() = default;
	WayPointComponent(WayPoint* wp, const bool& repeat = false)
		: movePattern(&*wp), currentPath(&*wp), distance(0.0f), repeat(repeat), finish(false) {}
	WayPointComponent(const WayPointComponent& other) = default;
};

struct PlayerInputComponent
{
	sf::Vector2f direction;
	std::shared_ptr<Command> command;
	std::shared_ptr<Command> KeyLShift;
	std::shared_ptr<Command> KeyRShift;

	PlayerInputComponent() = default;
	PlayerInputComponent(std::shared_ptr<Command> lshift, std::shared_ptr<Command> rshift)
		: KeyLShift(lshift), KeyRShift(rshift) {}
	PlayerInputComponent(const PlayerInputComponent& other) = default;
};