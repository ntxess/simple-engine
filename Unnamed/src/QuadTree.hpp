#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

class QuadTree
{
private:
	static const unsigned int QT_NODE_CAPACITY = 4;
	sf::FloatRect _boundary;
	bool _divided;
	std::vector<sf::Sprite*> _objects;
	std::unique_ptr<QuadTree> _northWest;
	std::unique_ptr<QuadTree> _northEast;
	std::unique_ptr<QuadTree> _southWest;
	std::unique_ptr<QuadTree> _southEast;

public:
	QuadTree(const sf::FloatRect& rect);
	~QuadTree();

	bool Insert(sf::Sprite* object);
	void Subdivide();
	std::vector<sf::Sprite*> QueryRange(const sf::FloatRect& range);
	void Clear();
};

