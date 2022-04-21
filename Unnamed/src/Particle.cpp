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

void Particle::Init(sf::Texture& texture, WayPoint* wps, const sf::Vector2f emitterPos)
{
	_sprite.setTexture(texture);
	_sprite.setScale(sf::Vector2f(2, 2));
	_sprite.setPosition(emitterPos);
	_state.live.speed = 500;
	_state.live.movePattern = &*wps;
	_state.live.path = &*wps;
	_inUse = true;
}

void Particle::SetNext(Particle* next)
{
	_state.next = next;
}

sf::Vector2f Particle::TraversePattern(const float& speed, const float& deltaTime)
{
	if (!_inUse || _state.live.movePattern == nullptr)
	{
		_state.live.distance = 0.f;
		return sf::Vector2f(0.f, 0.f);
	}

	WayPoint* headPtr = _state.live.path;
	WayPoint* nextPtr = headPtr->_nextWP.get();

	if (nextPtr == nullptr)
	{
		_inUse = false;
		return sf::Vector2f(0.f, 0.f);
	}

	_state.live.distance += speed * deltaTime;
	if (_state.live.distance > nextPtr->_distanceTotal)
		_state.live.path = nextPtr;

	sf::Vector2f unitDist;
	unitDist.x = (nextPtr->_location.x - headPtr->_location.x) / headPtr->_distanceToNext;
	unitDist.y = (nextPtr->_location.y - headPtr->_location.y) / headPtr->_distanceToNext;

	sf::Vector2f velocity;
	velocity.x = unitDist.x * speed * deltaTime;
	velocity.y = unitDist.y * speed * deltaTime;

	return velocity;
}

void Particle::Update(const float& deltaTime)
{
	_sprite.move(TraversePattern(_state.live.speed, deltaTime));
}

bool Particle::Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation)
{
	if (!_inUse)
		return true;

	rw->draw(_sprite);

	return false;
}