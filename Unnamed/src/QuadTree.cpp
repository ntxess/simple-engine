#include "QuadTree.hpp"

QuadTree::QuadTree(const sf::FloatRect& rect, const unsigned int& capacity)
	: QT_NODE_CAPACITY(capacity)
	, _divided(false)
	, _boundary(rect)
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

	_northWest = std::make_unique<QuadTree>(sf::FloatRect(x, y, width / 2.0f, height / 2.0f), QT_NODE_CAPACITY);
	_northEast = std::make_unique<QuadTree>(sf::FloatRect(x + width / 2.0f, y, width / 2.0f, height / 2.0f), QT_NODE_CAPACITY);
	_southWest = std::make_unique<QuadTree>(sf::FloatRect(x, y + height / 2.0f, width / 2.0f, height / 2.0f), QT_NODE_CAPACITY);
	_southEast = std::make_unique<QuadTree>(sf::FloatRect(x + width / 2.0f, y + height / 2.0f, width / 2.0f, height / 2.0f), QT_NODE_CAPACITY);

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
	//if (!_divided)
	//{
	//	_objects.clear();
	//	return;
	//}
	//else
	//{
	//	_northWest->Clear();
	//	_northEast->Clear();
	//	_southWest->Clear();
	//	_southEast->Clear();
	//}

	//if (!_objects.empty())
	//	_objects.clear();
}

void QuadTree::DrawBox(const std::unique_ptr<sf::RenderWindow>& rw)
{
	sf::RectangleShape rectangle;
	rectangle.setPosition(_boundary.left, _boundary.top);
	rectangle.setSize(sf::Vector2f(_boundary.width, _boundary.height));
	rectangle.setOutlineThickness(1.0f);
	rectangle.setFillColor(sf::Color(0, 0, 0));
	rectangle.setOutlineColor(sf::Color(0, 150, 100));

	//sf::Text text;
	//sf::Font font;
	//if (!font.loadFromFile("resources/font/VCR_OSD_MONO_1.001.ttf"))
	//{
	//	std::cout << "FAILURE TO LOAD FONT TYPE!" << std::endl;
	//	exit(-1);
	//}
	//text.setFont(font);
	//text.setCharacterSize(20);
	//text.setFillColor(sf::Color::White);
	//text.setPosition(sf::Vector2f(_boundary.left, _boundary.top));

	//std::stringstream ss;
	//ss << _objects.size();
	//std::string numObjectsStr = ss.str();
	//text.setString(numObjectsStr);
	//rw->draw(text);

	rw->draw(rectangle);
	//rw->draw(text);

	if (_divided)
	{
		_northWest->DrawBox(rw);
		_northEast->DrawBox(rw);
		_southWest->DrawBox(rw);
		_southEast->DrawBox(rw);
	}
}
