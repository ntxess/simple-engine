#pragma once
#include <assert.h>
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>

typedef std::unique_ptr<sf::RenderWindow> RenderWindowRef;

template <class TObject>
class ParticlePool
{
private:
	static const int POOL_SIZE = 10;
	TObject* _firstAvailable;
	TObject _entity[POOL_SIZE];

public:
	ParticlePool();
	~ParticlePool();
	void Create(thor::ResourceHolder<sf::Texture, std::string>& holder, const std::string& ID, const sf::Vector2f emitterPos);
	void Update(const float& deltaTime);
	void Render(const RenderWindowRef& rw, const float& deltaTime, const float& interpolation);
};

template<class TObject>
ParticlePool<TObject>::ParticlePool()
{
	_firstAvailable = &_entity[0];

	for (int i = 0; i < POOL_SIZE - 1; i++)
	{
		_entity[i].SetNext(&_entity[i + 1]);
	}

	_entity[POOL_SIZE - 1].SetNext(nullptr);
}

template<class TObject>
ParticlePool<TObject>::~ParticlePool()
{}

template<class TObject>
void ParticlePool<TObject>::Create(thor::ResourceHolder<sf::Texture, std::string>& holder, const std::string& ID, const sf::Vector2f emitterPos)
{
	assert(_firstAvailable != nullptr);

	TObject* newObject = _firstAvailable;
	_firstAvailable = _firstAvailable->_state.next;
	newObject->Init(holder, ID, emitterPos);
}

template<class TObject>
void ParticlePool<TObject>::Update(const float& deltaTime)
{
	for (unsigned int i = 0; i < POOL_SIZE; i++)
	{
		_entity[i].Update(deltaTime);
	}
}

template<class TObject>
void ParticlePool<TObject>::Render(const RenderWindowRef& rw, const float& deltaTime, const float& interpolation)
{
	// If entity is in use, update animation and physics
	// Once entity finished its lifetime return true and set unused entity as head and append to free-list
	// If entity is not in use skip update
	for (unsigned int i = 0; i < POOL_SIZE; i++)
	{
		if (_entity[i].Render(rw, deltaTime, interpolation))
		{
			_entity[i].SetNext(_firstAvailable);
			_firstAvailable = &_entity[i];
			std::cout << "Particle Freed" << std::endl;
		}
	}
}