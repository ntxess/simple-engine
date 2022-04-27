#include "Sandbox.hpp"

Sandbox::Sandbox(std::shared_ptr<GameData>& data)
	:_data(data)
{}

Sandbox::~Sandbox()
{}

void Sandbox::Init()
{
	std::cout << "Sandbox" << std::endl;

	float width = float(_data->_window->getSize().x);
	float height = float(_data->_window->getSize().y);
	_boundary = sf::FloatRect(0.f, 0.f, width, height);
	_quadTree = std::make_unique<QuadTree>(_boundary);

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 1920);

	for (unsigned int i = 0; i < MAX_SIZE; i++)
	{
		entt::entity entity = _registry.create();
		_registry.emplace<TagComponent>(entity, "generic_enemy");
		_registry.emplace<HealthComponent>(entity, 100.f);
		_registry.emplace<SpeedComponent>(entity, float(dist6(rng) % 500));
		_registry.emplace<WayPointComponent>(entity, _data->_pathMap.at("mRandom").get(), true);
		_registry.emplace<SpriteComponent>(entity, _data->_holder["Ship"]);
		_registry.get<SpriteComponent>(entity).sprite.setPosition(float(dist6(rng)), float(dist6(rng) % 1080));
	}

	_player = _registry.create();
	_registry.emplace<TagComponent>(_player, "player");
	_registry.emplace<HealthComponent>(_player, 1000.f);
	_registry.emplace<SpeedComponent>(_player, 500.f);
	_registry.emplace<PlayerInputComponent>(_player, std::make_shared<CommandDodge>(), std::make_shared<CommandExSkill>());
	_registry.emplace<SpriteComponent>(_player, _data->_holder["Ship"]);
	_registry.get<SpriteComponent>(_player).sprite.setPosition(960, 1000);

	_dummy = _registry.create();
	_registry.emplace<TagComponent>(_dummy, "dummy");
	_registry.emplace<HealthComponent>(_dummy, 1000.f);
	_registry.emplace<SpeedComponent>(_dummy, 500.f);
	_registry.emplace<SpriteComponent>(_dummy, _data->_holder["Ship"]);
	_registry.get<SpriteComponent>(_dummy).sprite.setPosition(960, 400);
}

void Sandbox::ProcessEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::L)
		{
			auto position = _registry.get<SpriteComponent>(_player).sprite.getPosition();
			entt::entity entity = _registry.create();
			_registry.emplace<TagComponent>(entity, "shot_particle");
			_registry.emplace<SpeedComponent>(entity, 2000.f);
			_registry.emplace<WayPointComponent>(entity, _data->_pathMap.at("mStraight").get(), true);
			_registry.emplace<DamageComponent>(entity, 100.f);
			_registry.emplace<SpriteComponent>(entity, _data->_holder["Shot"]);
			_registry.get<SpriteComponent>(entity).sprite.setPosition(position);
			_registry.get<SpriteComponent>(entity).sprite.setScale(2.f, 2.f);
		}

		auto controller = _registry.get<PlayerInputComponent>(_player);
		controller.command = NULL;

		if (event.key.code == sf::Keyboard::LShift)
			controller.command = controller.KeyLShift;

		if (event.key.code == sf::Keyboard::RShift)
			controller.command = controller.KeyRShift;

		if (controller.command)
			controller.command->Execute(_player, &_registry);
	}
}

void Sandbox::ProcessInput(const sf::Event& event)
{
	auto& controller = _registry.get<PlayerInputComponent>(_player);

	const float input = 1.f;
	controller.direction = sf::Vector2f(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		controller.direction.y -= input;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		controller.direction.x -= input;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		controller.direction.y += input;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		controller.direction.x += input;
}

void Sandbox::Update(const float& deltaTime)
{
	PlayerUpdate(deltaTime);
	WayPointUpdate(deltaTime);
	QuadTreeUpdate();

	//auto group = _registry.group<DamageComponent>(entt::get<SpriteComponent>);
	//for (auto entity : group)
	//{
	//	auto [dmg, sp] = group.get<DamageComponent, SpriteComponent>(entity);
	//	sf::FloatRect range = sp.sprite.getGlobalBounds();
	//	std::vector<entt::entity> found = _quadTree->QueryRange(range, &_registry);

	//	for (auto other : found)
	//	{
	//		if (sp.sprite.getGlobalBounds().intersects(_registry.get<SpriteComponent>(other).sprite.getGlobalBounds()))
	//		{
	//			//float hp = _registry.get<HealthComponent>(other).current;
	//			//std::cout << "HIT" << std::endl;
	//			//if (hp <= 0)
	//			//{
	//			//	_registry.destroy(other);
	//			//}
	//		}
	//	}
	//}
}

void Sandbox::Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation)
{
	RenderEntities(rw);

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

void Sandbox::PlayerUpdate(const float& deltaTime)
{
	auto controller = _registry.get<PlayerInputComponent>(_player);
	auto& sp = _registry.get<SpriteComponent>(_player);
	auto speed = _registry.get<SpeedComponent>(_player);

	sf::Vector2f direction = controller.direction;
	direction *= deltaTime * speed.current;

	sp.sprite.move(direction);
}

void Sandbox::WayPointUpdate(const float& deltaTime)
{
	auto group = _registry.group<WayPointComponent, SpeedComponent>(entt::get<SpriteComponent>);
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
				wpc.finish = false;
			}
			wpc.finish = true;
			continue;
		}

		wpc.distance += spd.current * deltaTime;
		if (wpc.distance > nextPtr->_distanceTotal)
			wpc.currentPath = nextPtr;

		sf::Vector2f unitDist;
		unitDist.x = (nextPtr->_location.x - headPtr->_location.x) / headPtr->_distanceToNext;
		unitDist.y = (nextPtr->_location.y - headPtr->_location.y) / headPtr->_distanceToNext;

		sf::Vector2f velocity;
		velocity.x = unitDist.x * spd.current * deltaTime;
		velocity.y = unitDist.y * spd.current * deltaTime;

		sp.sprite.move(velocity);
	}
}

void Sandbox::QuadTreeUpdate()
{	
	_quadTree = std::make_unique<QuadTree>(_boundary);
	auto view = _registry.view<SpriteComponent>();
	for (auto entity : view)
		_quadTree->Insert(entity, &_registry);
}

void Sandbox::RenderEntities(const std::unique_ptr<sf::RenderWindow>& rw)
{
	auto view = _registry.view<SpriteComponent>();
	for (auto entity : view)
		rw->draw(view.get<SpriteComponent>(entity).sprite);
}
