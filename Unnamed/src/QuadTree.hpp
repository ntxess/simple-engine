#pragma once
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics.hpp>

class QuadTree
{
private:
	const unsigned int QT_NODE_CAPACITY;
	bool _divided;
	sf::FloatRect _boundary;
	std::vector<sf::Sprite*> _objects;
	std::unique_ptr<QuadTree> _northWest;
	std::unique_ptr<QuadTree> _northEast;
	std::unique_ptr<QuadTree> _southWest;
	std::unique_ptr<QuadTree> _southEast;

public:
	QuadTree(const sf::FloatRect& rect, const unsigned int& capacity);
	~QuadTree();

	bool Insert(sf::Sprite* object);
	void Subdivide();
	std::vector<sf::Sprite*> QueryRange(const sf::FloatRect& range);
	void Clear();
	void DrawBox(const std::unique_ptr<sf::RenderWindow>& rw);
};

