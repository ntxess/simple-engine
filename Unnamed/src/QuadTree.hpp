#pragma once
#include <memory>
#include <vector>

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "entt/entt.hpp"
#include "Component.hpp"

constexpr size_t MAX_DEPTH = 6;

class QuadTree
{
private:
	static const size_t QT_NODE_CAPACITY = 4;
	sf::FloatRect _boundary;
	size_t _depth;
	bool _divided;
	std::vector<entt::entity> _nodes;
	std::unique_ptr<QuadTree> _northWest;
	std::unique_ptr<QuadTree> _northEast;
	std::unique_ptr<QuadTree> _southWest;
	std::unique_ptr<QuadTree> _southEast;

	sf::RectangleShape _rectangle;

public:
	QuadTree(const sf::FloatRect& rect, const size_t depth = 0);
	~QuadTree();

	bool Insert(entt::entity entity, entt::registry& registry);
	void Subdivide();
	std::vector<entt::entity> QueryRange(const sf::FloatRect& range, entt::registry& registry);
	void Remove(entt::entity entity, entt::registry& registry);
	void Clear();
	void Render(const std::unique_ptr<sf::RenderWindow>& rw);
};

