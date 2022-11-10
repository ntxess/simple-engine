#pragma once
#include <iostream>
#include <string>

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "WayPoint.hpp"
#include "CommandDodge.hpp"
#include "CommandExSkill.hpp"
#include "CommandBasic.hpp"

template<typename T>
struct DataComponent
{
	T value;

	DataComponent() = default;
	DataComponent(const DataComponent&) = default;
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

struct TextComponent
{
	sf::Text text;
	sf::Font font;

	TextComponent() = default;
	TextComponent(const std::string& pathToFont)
	{
		if (!font.loadFromFile(pathToFont))
		{
			std::cout << "FAILURE TO LOAD FONT TYPE!" << std::endl;
			exit(-1);
		}
		text.setFont(font);
		text.setCharacterSize(20);
		text.setFillColor(sf::Color::White);
		text.setPosition(sf::Vector2f(10.f, 5.f));
	}

	TextComponent(const TextComponent&) = default;
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

struct PlayerInputComponent
{
	sf::Vector2f direction;
	std::shared_ptr<Command> dodge;
	std::shared_ptr<Command> exSkill;
	std::shared_ptr<Command> attack;

	PlayerInputComponent() = default;
	PlayerInputComponent(std::shared_ptr<Command> dodge, std::shared_ptr<Command> exSkill, std::shared_ptr<Command> attack)
		: dodge(dodge), exSkill(exSkill), attack(attack) {}
	PlayerInputComponent(const PlayerInputComponent&) = default;
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
	BarComponent(const BarComponent&) = default;
};

struct ClockComponent
{
	sf::Clock clock;

	ClockComponent() = default;
	ClockComponent(const ClockComponent&) = default;
};

struct TopLayerTagComponent
{
	TopLayerTagComponent() = default;
	TopLayerTagComponent(const TopLayerTagComponent&) = default;
};

struct MidLayerTagComponent
{
	MidLayerTagComponent() = default;
	MidLayerTagComponent(const MidLayerTagComponent&) = default;
};

struct BotLayerTagComponent
{
	BotLayerTagComponent() = default;
	BotLayerTagComponent(const BotLayerTagComponent&) = default;
};

struct PlayerTagComponent
{
	PlayerTagComponent() = default;
	PlayerTagComponent(const PlayerTagComponent&) = default;
};

struct AllyTagComponent
{
	AllyTagComponent() = default;
	AllyTagComponent(const AllyTagComponent&) = default;
};

struct EnemyTagComponent
{
	EnemyTagComponent() = default;
	EnemyTagComponent(const EnemyTagComponent&) = default;
};

struct NeutralTagComponent
{
	NeutralTagComponent() = default;
	NeutralTagComponent(const NeutralTagComponent&) = default;
};

struct InteractableTagComponent
{
	InteractableTagComponent() = default;
	InteractableTagComponent(const InteractableTagComponent&) = default;
};

struct ParticleTagComponent
{
	ParticleTagComponent() = default;
	ParticleTagComponent(const ParticleTagComponent&) = default;
};

struct InterfaceTagComponent
{
	InterfaceTagComponent() = default;
	InterfaceTagComponent(const InterfaceTagComponent&) = default;
};

struct AttractionComponent
{
	union Power 
	{
		bool fullStrength;
		float level;
	};

	Power power;

	AttractionComponent() = default;
	AttractionComponent(const float& strength)
	{
		power.level = strength;
	}
	AttractionComponent(const bool& fullStrength)
	{
		power.fullStrength = fullStrength;
	}
	AttractionComponent(const AttractionComponent&) = default;
};

struct PerformanceMonitorComponent
{
	sf::Clock clock;
	float value;

	PerformanceMonitorComponent() = default;
	PerformanceMonitorComponent(const PerformanceMonitorComponent&) = default;
};

struct BackgroundComponent
{
	sf::Sprite sprite;

	BackgroundComponent() = default;
	BackgroundComponent(sf::Texture& texture, const sf::IntRect& bgCanvas)
	{
		texture.setRepeated(true);
		sprite.setTexture(texture);
		sprite.setTextureRect(bgCanvas);
	}
	BackgroundComponent(const BackgroundComponent&) = default;
};

struct RotateTurretComponent
{
	float degree;
	float speed;
	int flip;
	
	RotateTurretComponent() : degree(275.f), speed(1.f), flip(true) {};
	RotateTurretComponent(const float& speed) : degree(275.f), speed(speed), flip(true) {};
	RotateTurretComponent(const RotateTurretComponent&) = default;
};