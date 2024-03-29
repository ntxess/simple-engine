#include "QuadTree.hpp"

QuadTree::QuadTree(const sf::FloatRect& rect, const size_t depth)
	: _boundary(rect)
	, _depth(depth)
	, _divided(false)
{
	_rectangle.setPosition(_boundary.left, _boundary.top);
	_rectangle.setSize(sf::Vector2f(_boundary.width, _boundary.height));
	_rectangle.setOutlineThickness(1.0f);
	_rectangle.setFillColor(sf::Color::Transparent);
	_rectangle.setOutlineColor(sf::Color(0, 150, 100));
}

QuadTree::~QuadTree()
{}

bool QuadTree::Insert(entt::registry& registry, entt::entity entity)
{
	// Ignore objects that do not belong in this quad tree
	if (!_boundary.contains(registry.get<SpriteComponent>(entity).sprite.getPosition()))
		return false;

	// If there is space in this quad tree and if doesn't have subdivisions, add the object here
	if (_nodes.size() < QT_NODE_CAPACITY)
	{
		_nodes.push_back(entity);
		return true;
	}

	// Otherwise, subdivide and then add the point to whichever node will accept it
	if (_depth + 1 < MAX_DEPTH)
	{
		if (!_divided)
			Subdivide();

		// We have to add the points/data contained into this quad array to the new quads if we only want
		// the last node to hold the data
		if (_northWest->Insert(registry, entity)) return true;
		if (_northEast->Insert(registry, entity)) return true;
		if (_southWest->Insert(registry, entity)) return true;
		if (_southEast->Insert(registry, entity)) return true;
	}
	else
	{
		_nodes.push_back(entity);
		return true;
	}

	// Otherwise, the point cannot be inserted for some unknown reason (this should never happen)
	return false;
}

void QuadTree::Subdivide()
{
	float x = _boundary.left;
	float y = _boundary.top;
	float width = _boundary.width;
	float height = _boundary.height;

	_northWest = std::make_unique<QuadTree>(sf::FloatRect(x, y, width / 2.0f, height / 2.0f), _depth + 1);
	_northEast = std::make_unique<QuadTree>(sf::FloatRect(x + width / 2.0f, y, width / 2.0f, height / 2.0f), _depth + 1);
	_southWest = std::make_unique<QuadTree>(sf::FloatRect(x, y + height / 2.0f, width / 2.0f, height / 2.0f), _depth + 1);
	_southEast = std::make_unique<QuadTree>(sf::FloatRect(x + width / 2.0f, y + height / 2.0f, width / 2.0f, height / 2.0f), _depth + 1);

	_divided = true;
}

std::vector<entt::entity> QuadTree::QueryRange(entt::registry& registry, const sf::FloatRect& range)
{
	std::vector<entt::entity> entityFound;

	if (!_boundary.intersects(range))
		return entityFound;

	for (auto entity : _nodes)
	{
		if (range.intersects(registry.get<SpriteComponent>(entity).sprite.getGlobalBounds()))
			entityFound.push_back(entity);
	}

	if (!_divided)
		return entityFound;

	std::vector<entt::entity> tempVec;

	tempVec = _northWest->QueryRange(registry, range);
	entityFound.insert(entityFound.end(), tempVec.begin(), tempVec.end());

	tempVec = _northEast->QueryRange(registry, range);
	entityFound.insert(entityFound.end(), tempVec.begin(), tempVec.end());

	tempVec = _southWest->QueryRange(registry, range);
	entityFound.insert(entityFound.end(), tempVec.begin(), tempVec.end());

	tempVec = _southEast->QueryRange(registry, range);
	entityFound.insert(entityFound.end(), tempVec.begin(), tempVec.end());

	return entityFound;
}

void QuadTree::Remove(entt::registry& registry, entt::entity entity)
{
	for (size_t i = 0; i < _nodes.size(); i++)
	{
		if (_nodes[i] == entity)
		{
			_nodes[i] = entt::null;
			return;
		}
	}

	if (!_divided)
		return;

	_northWest->Remove(registry, entity);
	_northEast->Remove(registry, entity);
	_southWest->Remove(registry, entity);
	_southEast->Remove(registry, entity);
}

void QuadTree::Clear()
{
	if (!_divided)
	{
		_nodes.clear();
		return;
	}
	else
	{
		_northWest->Clear();
		_northEast->Clear();
		_southWest->Clear();
		_southEast->Clear();
	}

	if (!_nodes.empty())
		_nodes.clear();
}

void QuadTree::Render(const std::unique_ptr<sf::RenderWindow>& rw)
{
	rw->draw(_rectangle);

	if (_divided)
	{
		_northWest->Render(rw);
		_northEast->Render(rw);
		_southWest->Render(rw);
		_southEast->Render(rw);
	}
}