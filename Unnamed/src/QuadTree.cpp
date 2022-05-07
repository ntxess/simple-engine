#include "QuadTree.hpp"

QuadTree::QuadTree(const sf::FloatRect& rect, const size_t depth)
	: _boundary(rect)
	, _depth(depth)
	, _divided(false)
{}

QuadTree::~QuadTree()
{}

bool QuadTree::Insert(const entt::entity& entity, entt::registry* registry)
{
	// Ignore objects that do not belong in this quad tree
	if (!_boundary.contains(registry->get<SpriteComponent>(entity).sprite.getPosition()))
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
		if (_northWest->Insert(entity, registry)) return true;
		if (_northEast->Insert(entity, registry)) return true;
		if (_southWest->Insert(entity, registry)) return true;
		if (_southEast->Insert(entity, registry)) return true;
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

std::vector<entt::entity> QuadTree::QueryRange(const sf::FloatRect& range, entt::registry* registry)
{
	std::vector<entt::entity> entityFound;

	if (!_boundary.intersects(range))
		return entityFound;

	for (auto entity : _nodes)
	{
		if (range.contains(registry->get<SpriteComponent>(entity).sprite.getPosition()))
			entityFound.push_back(entity);
	}

	if (!_divided)
		return entityFound;

	std::vector<entt::entity> tempVec;

	tempVec = _northWest->QueryRange(range, registry);
	entityFound.insert(entityFound.end(), tempVec.begin(), tempVec.end());

	tempVec = _northEast->QueryRange(range, registry);
	entityFound.insert(entityFound.end(), tempVec.begin(), tempVec.end());

	tempVec = _southWest->QueryRange(range, registry);
	entityFound.insert(entityFound.end(), tempVec.begin(), tempVec.end());

	tempVec = _southEast->QueryRange(range, registry);
	entityFound.insert(entityFound.end(), tempVec.begin(), tempVec.end());

	return entityFound;
}

void QuadTree::Remove(const entt::entity& entity, entt::registry* registry)
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

	_northWest->Remove(entity, registry);
	_northEast->Remove(entity, registry);
	_southWest->Remove(entity, registry);
	_southEast->Remove(entity, registry);
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