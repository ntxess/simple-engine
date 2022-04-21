#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>

#include "ParticlePool.hpp"

template <class TObject>
class ParticlePool;

class ShotParticle
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

		ShotParticle* next;
	};

	bool _inUse;
	UState _state;
	sf::Sprite _sprite;

public:
	ShotParticle();
	~ShotParticle();
	void Init(const GameData& data, const sf::Vector2f& emitterPos);
	ShotParticle* GetNext() const;
	void SetNext(ShotParticle* next);
	sf::Vector2f TraversePattern(const float& deltaTime);
	bool Update(const float& deltaTime);
	void Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation);
};