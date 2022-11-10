#include "SystemHelper.hpp"

void SystemHelper::InputMovementUpdate(entt::registry& reg, entt::entity ent, const float& dt)
{
	auto controller = reg.get<PlayerInputComponent>(ent);
	auto& player = reg.get<SpriteComponent>(ent).sprite;
	auto speed = reg.get<SpeedComponent>(ent).current;

	sf::Vector2f direction = controller.direction;

	float length = sqrt((direction.x * direction.x) + (direction.y * direction.y));

	if (length != 0.f)
	{
		direction.x = direction.x / length;
		direction.y = direction.y / length;
	}

	direction *= speed * dt;
	player.move(direction);
}

void SystemHelper::CheckBoundary(const sf::Vector2u& boundary, sf::Sprite& obj)
{
	sf::Vector2f position = obj.getPosition();
	sf::FloatRect rect = obj.getGlobalBounds();

	if (position.x < 0 + (rect.width / 2))
		obj.setPosition(sf::Vector2f(0.f + (rect.width / 2), position.y));

	if (position.x + (rect.width / 2) > boundary.x) 
		obj.setPosition(sf::Vector2f(boundary.x - (rect.width / 2), position.y));

	position = obj.getPosition();

	if (position.y < 0 + (rect.height / 2))
		obj.setPosition(sf::Vector2f(position.x, 0.f + (rect.height / 2)));

	if (position.y + rect.height/2 > boundary.y)
		obj.setPosition(sf::Vector2f(position.x, boundary.y - (rect.height / 2)));
}

void SystemHelper::FocusCameraOn(sf::View& vw, sf::Sprite& obj)
{
	vw.setCenter(obj.getPosition());
}

void SystemHelper::MobWaypointUpdate(entt::registry& reg, const float& dt)
{
	auto group = reg.group<WayPointComponent, SpeedComponent>(entt::get<SpriteComponent>);
	for (auto entity : group)
	{
		auto [wpc, spd, sp] = group.get<WayPointComponent, SpeedComponent, SpriteComponent>(entity);

		WayPoint* headPtr = wpc.currentPath;
		WayPoint* nextPtr = headPtr->_nextWP.get();

		if (nextPtr == nullptr)
		{
			if (wpc.repeat)
			{
				wpc.currentPath = wpc.movePattern;
				wpc.distance = 0.f;
			}
			continue;
		}

		wpc.distance += spd.current * dt;
		if (wpc.distance > nextPtr->_distanceTotal)
			wpc.currentPath = nextPtr;

		sf::Vector2f unitDist;
		unitDist.x = (nextPtr->_location.x - headPtr->_location.x) / headPtr->_distanceToNext;
		unitDist.y = (nextPtr->_location.y - headPtr->_location.y) / headPtr->_distanceToNext;

		sf::Vector2f velocity;
		velocity.x = unitDist.x * spd.current * dt;
		velocity.y = unitDist.y * spd.current * dt;

		sp.sprite.move(velocity);
	}
}

void SystemHelper::MobTrackingUpdate(entt::registry& reg, entt::entity ent, const float& deltaTime)
{
	auto view = reg.view<AttractionComponent>();

	for (auto entity : view)
	{
		auto& tracker = reg.get<SpriteComponent>(entity).sprite;
		auto target = reg.get<SpriteComponent>(ent).sprite;

		auto attraction = reg.get<AttractionComponent>(entity);
		auto speed = reg.get<SpeedComponent>(entity).current;

		float targetX = target.getPosition().x;
		float targetY = target.getPosition().y;
		float trackerX = tracker.getPosition().x;
		float trackerY = tracker.getPosition().y;

		float distance = sqrt((targetX - trackerX) * (targetX - trackerX) +
			(targetY - trackerY) * (targetY - trackerY));

		if (distance <= attraction.power.level || attraction.power.fullStrength)
		{
			sf::Vector2f unitDist;
			unitDist.x = (targetX - trackerX) / distance;
			unitDist.y = (targetY - trackerY) / distance;

			sf::Vector2f velocity;
			velocity.x = unitDist.x * speed * deltaTime;
			velocity.y = unitDist.y * speed * deltaTime;

			tracker.move(velocity);
		}
	}
}

std::unique_ptr<QuadTree> SystemHelper::QuadTreeUpdate(entt::registry& reg, const sf::Vector2f& vwCenter, const sf::Vector2f& rwSize)
{
	float left = vwCenter.x - (rwSize.x / 2);
	float top  = vwCenter.y - (rwSize.y / 2);

	sf::FloatRect boundary = sf::FloatRect(left, top, rwSize.x, rwSize.y);
	std::unique_ptr<QuadTree> qt = std::make_unique<QuadTree>(boundary);

	auto view = reg.view<HealthComponent, EnemyTagComponent>();

	for (auto entity : view)
		qt->Insert(reg, entity);

	return qt;
}

void SystemHelper::CollisionUpdate(entt::registry& reg, const std::unique_ptr<QuadTree>& qt)
{
	auto view = reg.view<DamageComponent>();
	for (auto inflictor : view)
	{
		auto& inflictorSp = reg.get<SpriteComponent>(inflictor);
		sf::FloatRect range = inflictorSp.sprite.getGlobalBounds();
		std::vector<entt::entity> found = qt->QueryRange(reg, range);

		for (auto inflicted : found)
		{
			auto& inflictedSp = reg.get<SpriteComponent>(inflicted);
			if (inflictorSp.sprite.getGlobalBounds().intersects(inflictedSp.sprite.getGlobalBounds()))
			{
				//std::unique_ptr<Event> collisionEvent = std::make_unique<CollisionEvent>(inflictor, inflicted);
				//std::unique_ptr<CollisionHandler> collisionHandler = std::make_unique<CollisionHandler>();
				//_dispatcher->Dispatch(collisionEvent.get(), collisionHandler.get(), &CollisionHandler::OnEvent);

				SystemHelper::DamageUpdate(reg, inflictor, inflicted);
			}
		}
	}
}

void SystemHelper::DamageUpdate(entt::registry& reg, entt::entity inflictor, entt::entity inflicted)
{
	if (!reg.valid(inflictor) || !reg.valid(inflicted))
		return;

	auto dmg = reg.get<DamageComponent>(inflictor);
	auto& hp = reg.get<HealthComponent>(inflicted);
	hp.current -= dmg.damage;
	reg.destroy(inflictor);
}

void SystemHelper::CheckDestruction(entt::registry& reg)
{
	auto viewHp = reg.view<HealthComponent>();
	for (auto entity : viewHp)
	{
		auto health = reg.get<HealthComponent>(entity);
		if (health.current <= 0.f)
		{
			reg.destroy(entity);

			//std::unique_ptr<Event> destructionEvent = std::make_unique<DestructionEvent>(entity);
			//std::unique_ptr<DestructionHandler> destructionHandler = std::make_unique<DestructionHandler>();
			//_dispatcher->Dispatch(destructionEvent.get(), destructionHandler.get(), &DestructionHandler::OnEvent);
		}
	}

	auto viewWp = reg.view<WayPointComponent>();
	for (auto entity : viewWp)
	{
		auto wp = reg.get<WayPointComponent>(entity);

		if (reg.all_of<ParticleTagComponent, WayPointComponent>(entity) &&
			wp.currentPath->_distanceToNext == 0.f && !wp.repeat)
		{
			reg.destroy(entity);
		}
	}
}

void SystemHelper::PerformanceMetricUpdate(entt::registry& reg, entt::entity ent, const std::unique_ptr<sf::RenderWindow>& rw)
{
	auto& clock = reg.get<PerformanceMonitorComponent>(ent).clock;
	auto& fps = reg.get<PerformanceMonitorComponent>(ent).value;
	if (clock.getElapsedTime().asSeconds() >= 1.f)
	{
		std::string title = "Engine 9 | Ver 0.30.4 | FPS: ";
		title += std::to_string(int(fps));
		title += " | ";
		title += std::to_string(1000 / fps);
		title += "m/s";
		rw->setTitle(title);

		fps = 0.f;
		clock.restart();
	}
	++fps;
}

void SystemHelper::RotateTurretUpdate(entt::registry& reg, entt::entity ent, const float& dt)
{
	auto& currentDegree = reg.get<RotateTurretComponent>(ent).degree;
	auto speed = reg.get<RotateTurretComponent>(ent).speed;
	auto& currentOrientation = reg.get<RotateTurretComponent>(ent).flip;

	auto& sprite = reg.get<SpriteComponent>(ent).sprite;

	if (currentOrientation)
		currentDegree += dt * speed;
	else
		currentDegree -= dt * speed;

	if (currentDegree >= 370)
		currentOrientation = false;

	if (currentDegree <= 280)
		currentOrientation = true;

	sprite.setRotation(currentDegree);
}
