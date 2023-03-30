#include "QuadTree.hpp"

QuadTree::QuadTree(const sf::FloatRect& rect, const size_t depth)
	: m_boundary(rect)
	, m_depth(depth)
	, m_divided(false)
{
	m_rectangle.setPosition(m_boundary.left, m_boundary.top);
	m_rectangle.setSize(sf::Vector2f(m_boundary.width, m_boundary.height));
	m_rectangle.setOutlineThickness(1.0f);
	m_rectangle.setFillColor(sf::Color::Transparent);
	m_rectangle.setOutlineColor(sf::Color(0, 150, 100));
}

bool QuadTree::Insert(entt::registry& registry, entt::entity entity)
{
	// Ignore objects that do not belong in this quad tree
	if (!m_boundary.contains(registry.get<Sprite>(entity).sprite.getPosition()))
		return false;

	// If there is space in this quad tree and if doesn't have subdivisions, add the object here
	if (m_nodes.size() < QT_NODE_CAPACITY)
	{
		m_nodes.push_back(entity);
		return true;
	}

	// Otherwise, subdivide and then add the point to whichever node will accept it
	if (m_depth + 1 < MAX_DEPTH)
	{
		if (!m_divided)
			Subdivide();

		// We have to add the points/data contained into this quad array to the new quads if we only want
		// the last node to hold the data
		if (m_northWest->Insert(registry, entity)) return true;
		if (m_northEast->Insert(registry, entity)) return true;
		if (m_southWest->Insert(registry, entity)) return true;
		if (m_southEast->Insert(registry, entity)) return true;
	}
	else
	{
		m_nodes.push_back(entity);
		return true;
	}

	// Otherwise, the point cannot be inserted for some unknown reason (this should never happen)
	return false;
}

void QuadTree::Subdivide()
{
	float x = m_boundary.left;
	float y = m_boundary.top;
	float width = m_boundary.width;
	float height = m_boundary.height;

	m_northWest = std::make_unique<QuadTree>(sf::FloatRect(x, y, width / 2.0f, height / 2.0f), m_depth + 1);
	m_northEast = std::make_unique<QuadTree>(sf::FloatRect(x + width / 2.0f, y, width / 2.0f, height / 2.0f), m_depth + 1);
	m_southWest = std::make_unique<QuadTree>(sf::FloatRect(x, y + height / 2.0f, width / 2.0f, height / 2.0f), m_depth + 1);
	m_southEast = std::make_unique<QuadTree>(sf::FloatRect(x + width / 2.0f, y + height / 2.0f, width / 2.0f, height / 2.0f), m_depth + 1);

	m_divided = true;
}

std::vector<entt::entity> QuadTree::QueryRange(entt::registry& registry, const sf::FloatRect& range)
{
	std::vector<entt::entity> entityFound;

	if (!m_boundary.intersects(range))
		return entityFound;

	for (auto entity : m_nodes)
	{
		if (range.intersects(registry.get<Sprite>(entity).sprite.getGlobalBounds()))
			entityFound.push_back(entity);

		//if (range.intersects(registry.get<Hitbox>(entity).hitbox))
		//	entityFound.push_back(entity);
	}

	if (!m_divided)
		return entityFound;

	std::vector<entt::entity> tempVec;

	tempVec = m_northWest->QueryRange(registry, range);
	entityFound.insert(entityFound.end(), tempVec.begin(), tempVec.end());

	tempVec = m_northEast->QueryRange(registry, range);
	entityFound.insert(entityFound.end(), tempVec.begin(), tempVec.end());

	tempVec = m_southWest->QueryRange(registry, range);
	entityFound.insert(entityFound.end(), tempVec.begin(), tempVec.end());

	tempVec = m_southEast->QueryRange(registry, range);
	entityFound.insert(entityFound.end(), tempVec.begin(), tempVec.end());

	return entityFound;
}

void QuadTree::Remove(entt::registry& registry, entt::entity entity)
{
	for (size_t i = 0; i < m_nodes.size(); i++)
	{
		if (m_nodes[i] == entity)
		{
			m_nodes[i] = entt::null;
			return;
		}
	}

	if (!m_divided)
		return;

	m_northWest->Remove(registry, entity);
	m_northEast->Remove(registry, entity);
	m_southWest->Remove(registry, entity);
	m_southEast->Remove(registry, entity);
}

void QuadTree::Clear()
{
	if (!m_divided)
	{
		m_nodes.clear();
		return;
	}
	else
	{
		m_northWest->Clear();
		m_northEast->Clear();
		m_southWest->Clear();
		m_southEast->Clear();
	}

	if (!m_nodes.empty())
		m_nodes.clear();
}

void QuadTree::Render(const std::unique_ptr<sf::RenderWindow>& rw)
{
	rw->draw(m_rectangle);

	if (m_divided)
	{
		m_northWest->Render(rw);
		m_northEast->Render(rw);
		m_southWest->Render(rw);
		m_southEast->Render(rw);
	}
}