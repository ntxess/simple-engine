#pragma once
//#include <iostream>
//#include <string>
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include "Particle.hpp"

typedef std::unique_ptr<sf::RenderWindow> RenderWindowRef;

template <class TObject>
class GameObjectPool
{
private:
	static const int POOL_SIZE = 10000;
	TObject _particles[POOL_SIZE];
	bool _inUse[POOL_SIZE];
	TObject* _firstAvailable;

public:
	GameObjectPool(thor::ResourceHolder<sf::Texture, std::string>& holder, std::string ID);
	~GameObjectPool();
	void Create(sf::Vector2f pos);
	void Animate(float deltaTime);
	void Render(RenderWindowRef& rw, float interpolation);
};

template<class TObject>
inline GameObjectPool<TObject>::GameObjectPool(thor::ResourceHolder<sf::Texture, std::string>& holder, std::string ID)
{
	_firstAvailable = &_particles[0];

	for (int i = 0; i < POOL_SIZE-1; i++)
	{
		_inUse[i] = false;
		_particles[i].SetNext(&_particles[i + 1]);
	}

	_inUse[POOL_SIZE - 1] = false;
	_particles[POOL_SIZE - 1].SetNext(NULL);
}

template<class TObject>
inline GameObjectPool<TObject>::~GameObjectPool()
{}

template<class TObject>
inline void GameObjectPool<TObject>::Create(sf::Vector2f pos)
{
	assert(_firstAvailable != NULL);

	Particle* newObject = _firstAvailable;
	_firstAvailable = _firstAvailable->next;
	newObject->Init();

	//for (unsigned int i = 0; i < POOL_SIZE; i++)
	//{
	//	if (!_inUse[i])
	//	{
	//		_particles[i].Init();
	//		_inUse[i] = true;
	//		return;
	//	}
	//}
}

template<class TObject>
inline void GameObjectPool<TObject>::Animate(float deltaTime)
{

}

template<class TObject>
inline void GameObjectPool<TObject>::Render(RenderWindowRef& rw, float interpolation)
{
	for (unsigned int i = 0; i < POOL_SIZE; i++)
	{
		if (_inUse[i])
		{
			rw->draw(_particles[i]);
		}
	}
}
