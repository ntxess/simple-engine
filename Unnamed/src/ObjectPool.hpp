#pragma once
#include <assert.h>
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>

#include "GameData.hpp"

template <class TObject>
class ObjectPool
{
public:
	static const unsigned int POOL_SIZE = 100; // Upper limit - 15000@~60fps

private:
	TObject* _firstAvailable;
	TObject _entity[POOL_SIZE];

public:
	ObjectPool();
	~ObjectPool();
	TObject& GetObject(const unsigned int& position);
	void Create(sf::Texture& texture, WayPoint* wps, const sf::Vector2f spawnPos);
	void Update(const float& deltaTime);
	void Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation);
};

template<class TObject>
ObjectPool<TObject>::ObjectPool()
{
	// Free-list implementation
	_firstAvailable = &_entity[0];

	for (int i = 0; i < POOL_SIZE - 1; i++)
	{
		_entity[i].SetNext(&_entity[i + 1]);
	}

	_entity[POOL_SIZE - 1].SetNext(nullptr);
}

template<class TObject>
ObjectPool<TObject>::~ObjectPool()
{}

template<class TObject>
TObject& ObjectPool<TObject>::GetObject(const unsigned int& position)
{
	return _entity[position];
}

template<class TObject>
void ObjectPool<TObject>::Create(sf::Texture& texture, WayPoint* wps, const sf::Vector2f spawnPos)
{
	assert(_firstAvailable != nullptr);

	TObject* newObject = _firstAvailable;
	_firstAvailable = _firstAvailable->_state.next;
	newObject->Init(texture, wps, spawnPos);
}

template<class TObject>
void ObjectPool<TObject>::Update(const float& deltaTime)
{
	// If entity is in use, update animation and physics
	// Once entity finished its lifetime return true and set unused entity as head and append to free-list
	// If entity is not in use skip update
	for (unsigned int i = 0; i < POOL_SIZE; i++)
	{
		if (_entity[i].Update(deltaTime))
		{
			_entity[i].SetNext(_firstAvailable);
			_firstAvailable = &_entity[i];
		}
	}
}

template<class TObject>
void ObjectPool<TObject>::Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation)
{
	for (unsigned int i = 0; i < POOL_SIZE; i++)
	{
		_entity[i].Render(rw, deltaTime, interpolation);
	}
}