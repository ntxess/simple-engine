#include "CommandBasic.hpp"

CommandBasic::CommandBasic()
	: _cooldownTime(sf::seconds(0.1f).asSeconds())
{}

CommandBasic::~CommandBasic()
{}

float CommandBasic::GetTime() const
{
	return _timer.getElapsedTime().asSeconds();
}

float CommandBasic::GetMaxTime() const
{
	return _cooldownTime;
}

void CommandBasic::Execute(entt::registry& registry, entt::entity entity, std::shared_ptr<GameData>& data)
{
	float currentTime = _timer.getElapsedTime().asSeconds();

	if (currentTime > _cooldownTime)
	{
		entt::entity attackParticle = registry.create();
		registry.emplace<AllyTagComponent>(attackParticle);
		registry.emplace<ParticleTagComponent>(attackParticle);
		registry.emplace<MidLayerTagComponent>(attackParticle);
		registry.emplace<SpeedComponent>(attackParticle, 2000.f);
		registry.emplace<WayPointComponent>(attackParticle, data->_pathMap.at("mStraight").get(), false);
		registry.emplace<DamageComponent>(attackParticle, 100.f);
		registry.emplace<SpriteComponent>(attackParticle, data->_holder["Shot"]);

		sf::Vector2f position = registry.get<SpriteComponent>(entity).sprite.getPosition();
		position.x += registry.get<SpriteComponent>(entity).sprite.getGlobalBounds().width / 2;
		position.x -= registry.get<SpriteComponent>(attackParticle).sprite.getGlobalBounds().width;
		registry.get<SpriteComponent>(attackParticle).sprite.setPosition(position);
		registry.get<SpriteComponent>(attackParticle).sprite.setScale(2.f, 2.f);

		_timer.restart();
	}
}
