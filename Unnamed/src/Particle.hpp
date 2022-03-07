#pragma once
#include <SFML/Graphics.hpp>
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
	bool _inUse;

public:
	Particle();
	void Init();
	void SetNext(Particle* next);
	void Update(float deltaTime);
	bool Animate(float deltaTime);
	bool Render(RenderWindowRef& rw, float interpolation);
	Particle* GetNext() const;
};