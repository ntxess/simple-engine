#include "EnemyObject.hpp"

EnemyObject::EnemyObject()
	: _inUse(false)
{}

EnemyObject::~EnemyObject()
{}

void EnemyObject::Init(sf::Texture& texture, WayPoint* wps, const sf::Vector2f spawnPos)
{
	_sprite.setTexture(texture);
	_sprite.setScale(1.f, 1.f);
	_sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	_sprite.setPosition(spawnPos);
	_state.live.stats.DEFAULT_HP = 100.f;
	_state.live.stats.DEFAULT_SPD = 500.f;
	_state.live.stats.DEFAULT_ATTACK_SPEED = 1.f;
	_state.live.movePattern = &*wps;
	_state.live.path = &*wps;
	_inUse = true;

	ResetStats();
}

EnemyObject* EnemyObject::GetNext() const
{
	return _state.next;
}

void EnemyObject::SetNext(EnemyObject* next)
{
	_state.next = next;
}

sf::Sprite& EnemyObject::GetSprite()
{
	if (_inUse)
		return _sprite;
}

EnemyObject::STATUS EnemyObject::GetStatus() const
{
	return _state.live.stats;
}

void EnemyObject::ResetStats()
{
	_state.live.stats.CURRENT_HP = _state.live.stats.DEFAULT_HP;
	_state.live.stats.CURRENT_SPD = _state.live.stats.DEFAULT_SPD;
	_state.live.stats.CURRENT_ATTACK_SPEED = _state.live.stats.DEFAULT_ATTACK_SPEED;
}

void EnemyObject::SetHealth(const float& newHealth)
{
	_state.live.stats.DEFAULT_HP = newHealth;
}

void EnemyObject::SetSpeed(const float& newSpeed)
{
	_state.live.stats.DEFAULT_SPD = newSpeed;
}

void EnemyObject::SetAttackSpeed(const float& newAttackSpeed)
{
	_state.live.stats.DEFAULT_ATTACK_SPEED = newAttackSpeed;
}

void EnemyObject::SetRepeatPath(const bool& repeat)
{
	_state.live.repeat = repeat;
}

sf::Vector2f EnemyObject::TraversePattern(const float& deltaTime)
{
	if (_state.live.movePattern == nullptr)
		return sf::Vector2f(0.f, 0.f);

	WayPoint* headPtr = _state.live.path;
	WayPoint* nextPtr = headPtr->_nextWP.get();

	if (nextPtr == nullptr)
	{
		if (_state.live.repeat)
		{
			_state.live.path = _state.live.movePattern;
			_state.live.distance = 0.f;
		}
		return sf::Vector2f(0.f, 0.f);
	}

	_state.live.distance += _state.live.stats.CURRENT_SPD * deltaTime;
	if (_state.live.distance > nextPtr->_distanceTotal)
		_state.live.path = nextPtr;

	sf::Vector2f unitDist;
	unitDist.x = (nextPtr->_location.x - headPtr->_location.x) / headPtr->_distanceToNext;
	unitDist.y = (nextPtr->_location.y - headPtr->_location.y) / headPtr->_distanceToNext;

	sf::Vector2f velocity;
	velocity.x = unitDist.x * _state.live.stats.CURRENT_SPD * deltaTime;
	velocity.y = unitDist.y * _state.live.stats.CURRENT_SPD * deltaTime;

	return velocity;
}

bool EnemyObject::Update(const float& deltaTime)
{
	if (!_inUse)
		return false;

	_sprite.move(TraversePattern(deltaTime));

	return _state.live.stats.CURRENT_HP == 0.f;
}

void EnemyObject::Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation)
{
	if (_inUse)
		rw->draw(_sprite);
}
