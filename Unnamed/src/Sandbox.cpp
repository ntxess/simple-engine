#include "Sandbox.hpp"

Sandbox::Sandbox(std::shared_ptr<GameData>& data)
	:_data(data)
{}

Sandbox::~Sandbox()
{}

void Sandbox::Init()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 1920);

	for (unsigned int i = 0; i < MAX_SIZE; i++)
	{
		entt::entity generic_enemy = _registry.create();
		SpriteComponent& sprite = _registry.emplace<SpriteComponent>(generic_enemy, _data->_holder["Ship"]);
		sprite.sprite.setPosition(sf::Vector2f(float(dist6(rng)), float(dist6(rng) % 1080)));

		_registry.emplace<HealthComponent>(generic_enemy, 100.f);
		_registry.emplace<SpeedComponent>(generic_enemy, float(dist6(rng) % 500));
		_registry.emplace<WayPointComponent>(generic_enemy, _data->_pathMap.at("mRandom").get(), true);
	}

	entt::entity player = _registry.create();
	_registry.emplace<SpriteComponent>(player, _data->_holder["Ship"]);
	_registry.emplace<HealthComponent>(player, 1000.f);

	float width = float(_data->_window->getSize().x);
	float height = float(_data->_window->getSize().y);
	_boundary = sf::FloatRect(0.f, 0.f, width, height);
	_quadTree = std::make_unique<QuadTree>(_boundary);
}

void Sandbox::ProcessEvent(const sf::Event& event)
{


}

void Sandbox::ProcessInput(const sf::Event& event)
{


}

void Sandbox::Update(const float& deltaTime)
{
	_quadTree = std::make_unique<QuadTree>(_boundary);
	auto group = _registry.group<WayPointComponent, SpeedComponent, SpriteComponent>();
	for (auto entity : group)
	{
		auto [wp, spd, sp] = group.get<WayPointComponent, SpeedComponent, SpriteComponent>(entity);
		sp.sprite.move(TraverseWayPoint(wp, spd.current, deltaTime));
		CheckBoundary(sp.sprite);
		_quadTree->Insert(&sp.sprite);
	}
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
		}
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
