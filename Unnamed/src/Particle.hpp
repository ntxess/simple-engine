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
			double x;
			double y;
			double xVel;
			double yVel;
			sf::Vector2f position;
		} live;

		Particle* next;
	};

	sf::Sprite _sprite;
	thor::Animator<sf::Sprite, std::string> _animator;
	UState _state;
	bool _inUse;

public:
	Particle();
	~Particle();
	Particle* GetNext() const;
	void Init(thor::ResourceHolder<sf::Texture, std::string>& holder, const std::string& ID, const sf::Vector2f emitterPos);
	void SetNext(Particle* next);
	void Update(const float& deltaTime);
	void Animator(const float& deltaTime);
	bool Render(const RenderWindowRef& rw, const float& deltaTime, const float& interpolation);
};