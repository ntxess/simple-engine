#include "Particle.hpp"

Particle::Particle() 
	: _inUse(false)
{}

Particle::~Particle()
{}

Particle* Particle::GetNext() const
{
	return _state.next;
}

void Particle::Init(thor::ResourceHolder<sf::Texture, std::string>& holder, const std::string& spriteID,
					std::unordered_map<std::string, std::unique_ptr<WayPoint>> pathMap, const std::string& pathID,
					const sf::Vector2f emitterPos)
{
	sf::Texture& texture = holder[spriteID];
	_sprite.setTexture(texture);
	_sprite.setScale(sf::Vector2f(2, 2));
	_sprite.setPosition(emitterPos);
	_inUse = true;
}

void Particle::SetNext(Particle* next)
{
	_state.next = next;
}

bool Particle::TraversePattern(const float& speed, const float& deltaTime)
{
	//WayPoint* headPtr = _path;
	//WayPoint* nextPtr;

	//nextPtr = headPtr->_nextWP.get();
	//if (nextPtr == nullptr)
	//	return false;

	//_distance += speed * deltaTime;
	//if (_distance > nextPtr->_distanceTotal)
	//	_path = nextPtr;

	//nextPtr = headPtr->_nextWP.get();
	//sf::Vector2f unitDist;
	//unitDist.x = (nextPtr->_location.x - headPtr->_location.x) / headPtr->_distanceToNext;
	//unitDist.y = (nextPtr->_location.y - headPtr->_location.y) / headPtr->_distanceToNext;

	//sf::Vector2f velocity;
	//_velocity.x = unitDist.x * speed * deltaTime;
	//_velocity.y = unitDist.y * speed * deltaTime;

	//if (_repeat && _path->_distanceToNext == 0)
	//{
	//	_path = _movePattern;
	//	_distance = 0.f;
	//}

	return true;
}

void Particle::Update(const float& deltaTime)
{
	//if (TraversePattern(enemy.GetCurrentStats().SPD, deltaTime))
	//{
	//	enemy.GetGraphics()->GetSprite().move(_velocity);
	//}
}

bool Particle::Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation)
{
	return false;
}