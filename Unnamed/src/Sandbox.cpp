#include "Sandbox.hpp"

Sandbox::Sandbox(std::shared_ptr<GameData>& data)
	:_data(data)
{}

Sandbox::~Sandbox()
{}

void Sandbox::Init()
{
	float width = float(_data->_window->getSize().x);
	float height = float(_data->_window->getSize().y);
	_boundary = sf::FloatRect(0.f, 0.f, width, height);
	_quadTree = std::make_unique<QuadTree>(_boundary);

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 1920);

	for (unsigned int i = 0; i < MAX_SIZE; i++)
	{
		Entity entity = CreateEntity("generic_enemy");
		entity.AddComponent<HealthComponent>(100.f);
		entity.AddComponent<SpeedComponent>(float(dist6(rng) % 500));
		entity.AddComponent<WayPointComponent>(_data->_pathMap.at("mRandom").get(), true);
		entity.AddComponent<SpriteComponent>(_data->_holder["Ship"]);
		entity.GetComponent<SpriteComponent>().sprite.setPosition(float(dist6(rng)), float(dist6(rng) % 1080));
		_quadTree->Insert(entity.GetHandle(), &_registry);
	}

	_player = CreateEntity("player");
	_player.AddComponent<HealthComponent>(1000.f);
	_player.AddComponent<SpeedComponent>(500.f);
	_player.AddComponent<SpriteComponent>(_data->_holder["Ship"]);
	_player.GetComponent<SpriteComponent>().sprite.setPosition(960, 1000);
	_quadTree->Insert(_player.GetHandle(), &_registry);
}

void Sandbox::ProcessEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::L)
		{
			auto position = _player.GetComponent<SpriteComponent>().sprite.getPosition();
			Entity entity = CreateEntity("shot_particle");
			entity.AddComponent<SpeedComponent>(2000.f);
			entity.AddComponent<WayPointComponent>(_data->_pathMap.at("mStraight").get());
			entity.AddComponent<DamageComponent>(100.f);
			entity.AddComponent<SpriteComponent>(_data->_holder["Shot"]);
			entity.GetComponent<SpriteComponent>().sprite.setPosition(position);
			_quadTree->Insert(entity.GetHandle(), &_registry);
		}
	}
}

void Sandbox::ProcessInput(const sf::Event& event)
{


}

void Sandbox::Update(const float& deltaTime)
{
	_quadTree->Insert(_player.GetHandle(), &_registry);

	TransformEntity(deltaTime);

	auto group = _registry.group<DamageComponent>(entt::get<TagComponent, SpriteComponent>);
	for (auto entity : group)
	{
		auto [dmg, tag, sp] = group.get<DamageComponent, TagComponent, SpriteComponent>(entity);

		if (tag.name == "shot_particle")
		{
			sf::FloatRect range = sp.sprite.getGlobalBounds();
			std::vector<entt::entity> found = _quadTree->QueryRange(range, &_registry);
			for (auto other : found)
			{
				if (_registry.get<TagComponent>(other).name != "shot_particle")
				{
					if (sp.sprite.getGlobalBounds().intersects(_registry.get<SpriteComponent>(other).sprite.getGlobalBounds()))
					{
						float hp = _registry.get<HealthComponent>(other).current - dmg.damage;
					}
				}
			}
		}
	}
	_quadTree = std::make_unique<QuadTree>(_boundary);
}

void Sandbox::Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation)
{
	auto view = _registry.view<SpriteComponent>();
	for (auto entity : view)
	{
		rw->draw(view.get<SpriteComponent>(entity).sprite);
	}

	_fps.Update();
	_fps.Render(rw);
}

void Sandbox::Pause()
{


}

void Sandbox::Resume()
{


}

entt::registry& Sandbox::GetRegistry()
{
	return _registry;
}

Entity Sandbox::CreateEntity(const std::string& name)
{
	Entity entity(_registry.create(), this);
	auto& tag = entity.AddComponent<TagComponent>();
	tag.name = name.empty() ? "Entity" : name;
	return entity;
}

void Sandbox::CheckBoundary(sf::Sprite& object)
{
	sf::Vector2f position = object.getPosition();
	sf::FloatRect rect = object.getGlobalBounds();
	sf::Vector2u bounds = _data->_window->getSize();

	if (position.x < 0)
		object.setPosition(sf::Vector2f(0.f, position.y));

	if (position.x + rect.width > bounds.x)
		object.setPosition(sf::Vector2f(bounds.x - rect.width, position.y));

	position = object.getPosition();

	if (position.y < 0)
		object.setPosition(sf::Vector2f(position.x, 0.f));

	if (position.y + rect.height > bounds.y)
		object.setPosition(sf::Vector2f(position.x, bounds.y - rect.height));
}


sf::Vector2f Sandbox::TraverseWayPoint(WayPointComponent& wpc, const float& speed, const float& deltaTime)
{
	if (wpc.movePattern == nullptr)
		return sf::Vector2f(0.f, 0.f);

	WayPoint* headPtr = wpc.currentPath;
	WayPoint* nextPtr = headPtr->_nextWP.get();

	if (nextPtr == nullptr)
	{
		if (wpc.repeat)
		{
			wpc.currentPath = wpc.movePattern;
			wpc.distance = 0.f;
			wpc.finish = false;
		}
		wpc.finish = true;
		return sf::Vector2f(0.f, 0.f);
	}

	wpc.distance += speed * deltaTime;
	if (wpc.distance > nextPtr->_distanceTotal)
		wpc.currentPath = nextPtr;

	sf::Vector2f unitDist;
	unitDist.x = (nextPtr->_location.x - headPtr->_location.x) / headPtr->_distanceToNext;
	unitDist.y = (nextPtr->_location.y - headPtr->_location.y) / headPtr->_distanceToNext;

	sf::Vector2f velocity;
	velocity.x = unitDist.x * speed * deltaTime;
	velocity.y = unitDist.y * speed * deltaTime;

	return velocity;
}

void Sandbox::TransformEntity(const float& deltaTime)
{
	auto group = _registry.group<WayPointComponent, SpeedComponent>(entt::get<TagComponent, SpriteComponent>);
	for (auto entity : group)
	{
		auto [wp, spd, tag, sp] = group.get<WayPointComponent, SpeedComponent, TagComponent, SpriteComponent>(entity);
		sp.sprite.move(TraverseWayPoint(wp, spd.current, deltaTime));

		if (tag.name == "shot_particle")
		{
			if (wp.finish)
			{
				_registry.destroy(entity);
				continue;
			}
		}
		else
		{
			CheckBoundary(sp.sprite);
		}
		_quadTree->Insert(entity, &_registry);
	}
}

