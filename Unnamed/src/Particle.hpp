#pragma once
#include <SFML/Graphics/Vertex.hpp>
#include <Thor/Animations.hpp>
#include "GameObjectPool.hpp"

class Particle
{
	friend class ParticlePool;

private:
	union UState
	{
		UState() {}
		struct
		{
			double x;
			double y;
			double xVel;
			double yVel;
			sf::Vector2f _position;
		} live;

		Particle* next;
	};

	UState _state;

public:
	Particle();
	void Init();
	void SetNext(Particle* next);
	Particle* GetNext() const;
};