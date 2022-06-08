#include "CommandBasic.hpp"

CommandBasic::CommandBasic()
	: _cooldownTime(sf::seconds(5.f).asSeconds())
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

void CommandBasic::Execute(entt::entity entity, entt::registry& registry)
{
	float currentTime = _timer.getElapsedTime().asSeconds();

	if (currentTime > _cooldownTime)
	{
		//auto position = registry->get<SpriteComponent>(entity).sprite.getPosition();
		//entt::entity particle = registry->create();
		//registry->emplace<TagComponent>(particle, "shot_particle", TagComponent::AFFILIATION::Ally, TagComponent::TYPE::Particle);
		//registry->emplace<SpeedComponent>(particle, 2000.f);
		//registry->emplace<WayPointComponent>(particle, _data->_pathMap.at("mStraight").get(), false);
		//registry->emplace<DamageComponent>(particle, 100.f);
		//registry->emplace<SpriteComponent>(particle, _data->_holder["Shot"]);
		//registry->get<SpriteComponent>(particle).sprite.setPosition(position);
		//registry->get<SpriteComponent>(particle).sprite.setScale(2.f, 2.f);
		_timer.restart();
	}
}
