#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>

#include "ParticlePool.hpp"

template <class TObject>

class ParticlePool;

class Particle
{
	template <class TObject>
	friend class ParticlePool;

private:
	union UState
	{
		UState() {}
		struct 
		{
			WayPoint* movePattern;
			WayPoint* path;
			float distance;			
			float speed;
		} live;

		Particle* next;
	};
	
	bool _inUse;
	UState _state;
	sf::Sprite _sprite;

public:
	Particle();
	~Particle();
	Particle* GetNext() const;
	void Init(sf::Texture& texture, WayPoint* wps, const sf::Vector2f emitterPos);
	void SetNext(Particle* next);
	sf::Vector2f TraversePattern(const float& speed, const float& deltaTime);
	void Update(const float& deltaTime);
	bool Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation);
};