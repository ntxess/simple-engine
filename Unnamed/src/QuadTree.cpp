#include "QuadTree.hpp"

QuadTree::QuadTree(const sf::FloatRect& rect)
	: _boundary(rect)
	, _divided(false)
{}

QuadTree::~QuadTree()
{}

bool QuadTree::Insert(sf::Sprite* object)
{
	// Ignore objects that do not belong in this quad tree
	if (!_boundary.contains(object->getPosition()))
		return false;

	// If there is space in this quad tree and if doesn't have subdivisions, add the object here
	if (_objects.size() < QT_NODE_CAPACITY)
	{
		_objects.push_back(object);
		return true;
	}

	// Otherwise, subdivide and then add the point to whichever node will accept it
	if (!_divided)
		Subdivide();

	// We have to add the points/data contained into this quad array to the new quads if we only want
	// the last node to hold the data
	if (_northWest->Insert(object)) return true;
	if (_northEast->Insert(object)) return true;
	if (_southWest->Insert(object)) return true;
	if (_southEast->Insert(object)) return true;
	
	// Otherwise, the point cannot be inserted for some unknown reason (this should never happen)
	return false;
}

void QuadTree::Subdivide()
{
	float x = _boundary.left;
	float y = _boundary.top;
	float width = _boundary.width;
	float height = _boundary.height;

	_northWest = std::make_unique<QuadTree>(sf::FloatRect(x, y, width / 2.0f, height / 2.0f));
	_northEast = std::make_unique<QuadTree>(sf::FloatRect(x + width / 2.0f, y, width / 2.0f, height / 2.0f));
	_southWest = std::make_unique<QuadTree>(sf::FloatRect(x, y + height / 2.0f, width / 2.0f, height / 2.0f));
	_southEast = std::make_unique<QuadTree>(sf::FloatRect(x + width / 2.0f, y + height / 2.0f, width / 2.0f, height / 2.0f));

	_divided = true;
}

std::vector<sf::Sprite*> QuadTree::QueryRange(const sf::FloatRect& range)
{
	std::vector<sf::Sprite*> objectsFound;

	if (!_boundary.intersects(range))
		return objectsFound;

	for (int i = 0; i < _objects.size(); i++)
	{
		if (range.contains(_objects[i]->getPosition()))
			objectsFound.push_back(_objects[i]);
	}

	if (!_divided)
		return objectsFound;

	std::vector<sf::Sprite*> tempVec;

	tempVec = _northWest->QueryRange(range);
	objectsFound.insert(objectsFound.end(), tempVec.begin(), tempVec.end());

	tempVec = _northEast->QueryRange(range);
	objectsFound.insert(objectsFound.end(), tempVec.begin(), tempVec.end());

	tempVec = _southWest->QueryRange(range);
	objectsFound.insert(objectsFound.end(), tempVec.begin(), tempVec.end());

	tempVec = _southEast->QueryRange(range);
	objectsFound.insert(objectsFound.end(), tempVec.begin(), tempVec.end());

	return objectsFound;
}

void QuadTree::Clear()
{
	if (!_divided)
	{
		_objects.clear();
		return;
	}
	else
	{
		_northWest->Clear();
		_northEast->Clear();
		_southWest->Clear();
		_southEast->Clear();
	}

	if (!_objects.empty())
		_objects.clear();
}