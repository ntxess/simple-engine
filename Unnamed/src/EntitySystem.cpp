//#include "EntitySystem.hpp"
//
//void EntitySystem::CheckBoundary(sf::Sprite& object)
//{
//	sf::Vector2f position = object.getPosition();
//	sf::FloatRect rect = object.getGlobalBounds();
//	sf::Vector2u bounds = _data->_window->getSize();
//
//	if (position.x < 0)
//		object.setPosition(sf::Vector2f(0.f, position.y));
//
//	if (position.x + rect.width > bounds.x)
//		object.setPosition(sf::Vector2f(bounds.x - rect.width, position.y));
//
//	position = object.getPosition();
//
//	if (position.y < 0)
//		object.setPosition(sf::Vector2f(position.x, 0.f));
//
//	if (position.y + rect.height > bounds.y)
//		object.setPosition(sf::Vector2f(position.x, bounds.y - rect.height));
//}
//
//void EntitySystem::PlayerUpdate(const float& deltaTime)
//{
//	auto controller = _registry.get<PlayerInputComponent>(_player);
//	auto& sp = _registry.get<SpriteComponent>(_player);
//	auto speed = _registry.get<SpeedComponent>(_player);
//
//	sf::Vector2f direction = controller.direction;
//	direction *= deltaTime * speed.current;
//
//	sp.sprite.move(direction);
//	CheckBoundary(sp.sprite);
//}
//
//void EntitySystem::WayPointUpdate(const float& deltaTime)
//{
//	auto group = _registry.group<WayPointComponent, SpeedComponent>(entt::get<SpriteComponent>);
//	for (auto entity : group)
//	{
//		auto [wpc, spd, sp] = group.get<WayPointComponent, SpeedComponent, SpriteComponent>(entity);
//
//		WayPoint* headPtr = wpc.currentPath;
//		WayPoint* nextPtr = headPtr->_nextWP.get();
//
//		if (nextPtr == nullptr)
//		{
//			if (wpc.repeat)
//			{
//				wpc.currentPath = wpc.movePattern;
//				wpc.distance = 0.f;
//			}
//			continue;
//		}
//
//		wpc.distance += spd.current * deltaTime;
//		if (wpc.distance > nextPtr->_distanceTotal)
//			wpc.currentPath = nextPtr;
//
//		sf::Vector2f unitDist;
//		unitDist.x = (nextPtr->_location.x - headPtr->_location.x) / headPtr->_distanceToNext;
//		unitDist.y = (nextPtr->_location.y - headPtr->_location.y) / headPtr->_distanceToNext;
//
//		sf::Vector2f velocity;
//		velocity.x = unitDist.x * spd.current * deltaTime;
//		velocity.y = unitDist.y * spd.current * deltaTime;
//
//		sp.sprite.move(velocity);
//	}
//}
//
//void EntitySystem::QuadTreeUpdate()
//{
//	_quadTree = std::make_unique<QuadTree>(_boundary);
//	auto view = _registry.view<HealthComponent>();
//	for (auto entity : view)
//	{
//		if (_registry.get<TagComponent>(entity).affiliation != TagComponent::AFFILIATION::Ally)
//			_quadTree->Insert(entity, &_registry);
//	}
//}
//
//void EntitySystem::CheckCollision()
//{
//	// Focus on Components that do damage and take damage
//	// Collisions that do not have either of these two component are ignored
//	auto view = _registry.view<DamageComponent>();
//	for (auto inflictor : view)
//	{
//		auto [inflictorTag, inflictorSp] = _registry.get<TagComponent, SpriteComponent>(inflictor);
//		sf::FloatRect range = inflictorSp.sprite.getGlobalBounds();
//		std::vector<entt::entity> found = _quadTree->QueryRange(range, &_registry);
//
//		for (auto inflicted : found)
//		{
//			auto [inflictedTag, inflictedSp] = _registry.get<TagComponent, SpriteComponent>(inflicted);
//			if (inflictorSp.sprite.getGlobalBounds().intersects(inflictedSp.sprite.getGlobalBounds()))
//			{
//				DamageUpdate(inflictor, inflicted);
//			}
//		}
//	}
//}
//
//void EntitySystem::DamageUpdate(const entt::entity& inflictor, const entt::entity& inflicted)
//{
//	if (!_registry.valid(inflictor) || !_registry.valid(inflicted))
//		return;
//
//	auto dmg = _registry.get<DamageComponent>(inflictor);
//	auto& hp = _registry.get<HealthComponent>(inflicted);
//	hp.current -= dmg.damage;
//	_registry.destroy(inflictor);
//}
//
//void EntitySystem::CheckDestruction()
//{
//	auto viewHp = _registry.view<HealthComponent>();
//	for (auto entity : viewHp)
//	{
//		auto health = _registry.get<HealthComponent>(entity);
//		if (health.current <= 0.f)
//		{
//			_registry.destroy(entity);
//		}
//	}
//
//	auto viewWp = _registry.view<WayPointComponent>();
//	for (auto entity : viewWp)
//	{
//		auto wp = _registry.get<WayPointComponent>(entity);
//		auto tag = _registry.get<TagComponent>(entity);
//
//		if (tag.type == TagComponent::TYPE::Particle && wp.currentPath->_distanceToNext == 0.f && !wp.repeat)
//		{
//			_registry.destroy(entity);
//		}
//	}
//}
//
//void EntitySystem::RenderEntities(const std::unique_ptr<sf::RenderWindow>& rw)
//{
//	auto view = _registry.view<SpriteComponent>();
//	for (auto entity : view)
//		rw->draw(view.get<SpriteComponent>(entity).sprite);
//}