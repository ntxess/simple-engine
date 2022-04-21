#include "ShotParticle.hpp"

ShotParticle::ShotParticle()
	: _inUse(false)
{}

ShotParticle::~ShotParticle()
{}

void ShotParticle::Init(sf::Texture& texture, WayPoint* wps, const sf::Vector2f spawnPos)
{
	_sprite.setTexture(texture);
	_sprite.setScale(sf::Vector2f(2, 2));
	_sprite.setPosition(spawnPos);
	_state.live.speed = 2000;
	_state.live.movePattern = &*wps;
	_state.live.path = &*wps;
	_inUse = true;
}

ShotParticle* ShotParticle::GetNext() const
{
	return _state.next;
}

void ShotParticle::SetNext(ShotParticle* next)
{
	_state.next = next;
}

sf::Vector2f ShotParticle::TraversePattern(const float& deltaTime)
{
	WayPoint* headPtr = _state.live.path;
	WayPoint* nextPtr = headPtr->_nextWP.get();

	if (nextPtr == nullptr)
	{
		_inUse = false;
		_state.live.path = _state.live.movePattern;
		_state.live.distance = 0.f;
		return sf::Vector2f(0.f, 0.f);
	}

	_state.live.distance += _state.live.speed * deltaTime;
	if (_state.live.distance > nextPtr->_distanceTotal)
		_state.live.path = nextPtr;

	sf::Vector2f unitDist;
	unitDist.x = (nextPtr->_location.x - headPtr->_location.x) / headPtr->_distanceToNext;
	unitDist.y = (nextPtr->_location.y - headPtr->_location.y) / headPtr->_distanceToNext;

	sf::Vector2f velocity;
	velocity.x = unitDist.x * _state.live.speed * deltaTime;
	velocity.y = unitDist.y * _state.live.speed * deltaTime;

	return velocity;
}

bool ShotParticle::Update(const float& deltaTime)
{
	if (!_inUse)
		return false;

	_sprite.move(TraversePattern(deltaTime));

	return _state.live.path->_distanceToNext == 0.f;
}

void ShotParticle::Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation)
{
	if (_inUse)
		rw->draw(_sprite);
}