#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>

#include "ObjectPool.hpp"

template <class TObject>
class ObjectPool;

class ShotParticle
{
	template <class TObject>
	friend class ObjectPool;

private:
	union USTATE
	{
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
	USTATE _state;
	sf::Sprite _sprite;

public:
	ShotParticle();
	~ShotParticle();
	void Init(sf::Texture& texture, WayPoint* wps, const sf::Vector2f spawnPos);
	ShotParticle* GetNext() const;
	sf::Sprite& GetSprite();
	void SetNext(ShotParticle* next);
	sf::Vector2f TraversePattern(const float& deltaTime);
	bool Update(const float& deltaTime);
	void Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation);
};