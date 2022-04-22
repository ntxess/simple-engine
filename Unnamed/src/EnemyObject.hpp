#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>

#include "ObjectPool.hpp"

template <class TObject>
class ObjectPool;

class EnemyObject
{
	template <class TObject>
	friend class ObjectPool;

private:
	struct STATUS
	{
		float CURRENT_HP;
		float CURRENT_SPD;
		float CURRENT_ATTACK_SPEED;
		float DEFAULT_HP;
		float DEFAULT_SPD;
		float DEFAULT_ATTACK_SPEED;
	};

	union USTATE
	{
		struct
		{
			STATUS stats;
			WayPoint* movePattern;
			WayPoint* path;
			float distance;
			bool repeat;
		} live;

		EnemyObject* next;
	};

	bool _inUse;
	USTATE _state;
	sf::Sprite _sprite;

public:
	EnemyObject();
	~EnemyObject();

	void Init(sf::Texture& texture, WayPoint* wps, const sf::Vector2f spawnPos);
	EnemyObject* GetNext() const;
	void SetNext(EnemyObject* next);
	sf::Sprite& GetSprite();
	EnemyObject::STATUS GetStatus() const;
	void ResetStats();
	void SetHealth(const float& newHealth);
	void SetSpeed(const float& newSpeed);
	void SetAttackSpeed(const float& newAttackSpeed);
	void SetRepeatPath(const bool& repeat);
	sf::Vector2f TraversePattern(const float& deltaTime);
	bool Update(const float& deltaTime);
	void Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation);
};

