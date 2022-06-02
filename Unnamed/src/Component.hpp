#pragma once
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "WayPoint.hpp"
#include "CommandDodge.hpp"
#include "CommandExSkill.hpp"
#include "CommandBasic.hpp"

struct TagComponent
{
	enum class AFFILIATION
	{
		Ally,
		Enemy, 
		Neutral,
		None
	};

	enum class TYPE
	{
		Interactable,
		Particle,
		UI,
		None
	};

	std::string name;
	AFFILIATION affiliation;
	TYPE type;

	TagComponent() = default;
	TagComponent(const std::string& nametag, const AFFILIATION& af, const TYPE& ty)
		: name(nametag) , affiliation(af), type(ty) {}
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
	WayPointComponent(const WayPointComponent& other) = default;
};

struct PlayerInputComponent
{
	sf::Vector2f direction;
	std::shared_ptr<Command> dash;
	std::shared_ptr<Command> exSkill;

	PlayerInputComponent() = default;
	PlayerInputComponent(std::shared_ptr<Command> dash, std::shared_ptr<Command> exskill)
		: dash(dash), exSkill(exskill) {}
	PlayerInputComponent(const PlayerInputComponent& other) = default;
};

struct ScoreBoardComponent
{
	size_t score;
	size_t distance;
	size_t enemiesFelled;
};

struct BarComponent
{
	sf::Sprite sprite;

	BarComponent() = default;
	BarComponent(sf::Texture& texture)
	{
		sprite.setTexture(texture);
		sprite.setScale(sf::Vector2f(0.0f, 0.0f));
	}
	BarComponent(const BarComponent& other) = default;
};

struct DestructionTagComponent
{
	DestructionTagComponent() = default;
	DestructionTagComponent(const DestructionTagComponent&) = default;
};