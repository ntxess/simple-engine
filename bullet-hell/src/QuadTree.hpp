#pragma once
#include "Component.hpp"
#include "entt/entt.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include <memory>
#include <vector>

constexpr size_t MAX_DEPTH = 6;

class QuadTree
{
private:
	static const size_t QT_NODE_CAPACITY = 4;
	sf::FloatRect m_boundary;
	size_t m_depth;
	bool m_divided;
	std::vector<entt::entity> m_nodes;
	std::unique_ptr<QuadTree> m_northWest;
	std::unique_ptr<QuadTree> m_northEast;
	std::unique_ptr<QuadTree> m_southWest;
	std::unique_ptr<QuadTree> m_southEast;

	sf::RectangleShape m_rectangle;

public:
	QuadTree(const sf::FloatRect& rect, const size_t depth = 0);
	~QuadTree() = default;

	bool Insert(entt::registry& registry, entt::entity entity);
	void Subdivide();
	std::vector<entt::entity> QueryRange(entt::registry& registry, const sf::FloatRect& range);
	void Remove(entt::registry& registry, entt::entity entity);
	void Clear();
	void Render(const std::unique_ptr<sf::RenderWindow>& rw);
};

