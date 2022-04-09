#pragma once

#include <assert.h>
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include "Particle.hpp"

typedef std::unique_ptr<sf::RenderWindow> RenderWindowRef;

template <class TObject>
class GameObjectPool
{
private:
	static const int POOL_SIZE = 10000;
	TObject* _firstAvailable;
	TObject  _entity[POOL_SIZE];

public:
	GameObjectPool();
	~GameObjectPool();
	void Create(sf::Vector2f pos);
	void Update(float deltaTime);
	void Render(RenderWindowRef& rw, float interpolation);
};

template<class TObject>
GameObjectPool<TObject>::GameObjectPool()
{
	_firstAvailable = &_entity[0];

	for (int i = 0; i < POOL_SIZE-1; i++)
	{
		_entity[i].SetNext(&_entity[i + 1]);
	}

	_entity[POOL_SIZE - 1].SetNext(nullptr);
}

template<class TObject>
GameObjectPool<TObject>::~GameObjectPool()
{}

template<class TObject>
void GameObjectPool<TObject>::Create(sf::Vector2f pos)
{
	assert(_firstAvailable != nullptr);

	TObject* newObject = _firstAvailable;
	_firstAvailable = _firstAvailable->next;
	newObject->Init();
}

template<class TObject>
void GameObjectPool<TObject>::Update(float deltaTime)
{
	for (unsigned int i = 0; i < POOL_SIZE; i++)
	{
		// if entity is in use, update animation and physics
		// once entity finished its lifetime return true and set unused entity as head and append to free-list
		// if entity is not in use skip update
		_entity[i].Update(deltaTime);
	}
}

template<class TObject>
void GameObjectPool<TObject>::Render(RenderWindowRef& rw, float interpolation)
{
	// Note: Animation is also updated in render
	for (unsigned int i = 0; i < POOL_SIZE; i++)
	{
		if (_entity[i].Render(rw, interpolation))
		{
			_entity[i].SetNext(_firstAvailable);
			_firstAvailable = &_entity[i];
		}
	}
}
