#pragma once
#include <random>
#include "WayPoint.hpp"

struct MRandom
{
public:
	std::unique_ptr<WayPoint> head;

	MRandom()
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(100, 700);

		std::unique_ptr<WayPoint> pointA = std::make_unique<WayPoint>(sf::Vector2f(float(dist6(rng)), float(dist6(rng))));
		std::unique_ptr<WayPoint> pointB = std::make_unique<WayPoint>(sf::Vector2f(float(dist6(rng)), float(dist6(rng))));
		std::unique_ptr<WayPoint> pointC = std::make_unique<WayPoint>(sf::Vector2f(float(dist6(rng)), float(dist6(rng))));
		std::unique_ptr<WayPoint> pointD = std::make_unique<WayPoint>(sf::Vector2f(float(dist6(rng)), float(dist6(rng))));
		std::unique_ptr<WayPoint> pointE = std::make_unique<WayPoint>(sf::Vector2f(float(dist6(rng)), float(dist6(rng))));
		std::unique_ptr<WayPoint> pointF = std::make_unique<WayPoint>(sf::Vector2f(float(dist6(rng)), float(dist6(rng))));
		std::unique_ptr<WayPoint> pointG = std::make_unique<WayPoint>(sf::Vector2f(float(dist6(rng)), float(dist6(rng))));
		std::unique_ptr<WayPoint> pointH = std::make_unique<WayPoint>(sf::Vector2f(float(dist6(rng)), float(dist6(rng))));
		std::unique_ptr<WayPoint> pointI = std::make_unique<WayPoint>(sf::Vector2f(float(dist6(rng)), float(dist6(rng))));
		std::unique_ptr<WayPoint> pointJ = std::make_unique<WayPoint>(sf::Vector2f(float(dist6(rng)), float(dist6(rng))));

		pointI->AddNext(std::move(pointJ));
		pointH->AddNext(std::move(pointI));
		pointG->AddNext(std::move(pointH));
		pointF->AddNext(std::move(pointG));
		pointE->AddNext(std::move(pointF));
		pointD->AddNext(std::move(pointE));
		pointC->AddNext(std::move(pointD));
		pointB->AddNext(std::move(pointC));
		pointA->AddNext(std::move(pointB));

		head = std::move(pointA);

		WayPoint* headPtr = head.get();
		WayPoint* next;
		while (headPtr->_nextWP.get() != NULL)
		{
			next = headPtr->_nextWP.get();
			headPtr->_nextWP.get()->_distanceTotal = headPtr->_distanceTotal + headPtr->_distanceToNext;
			headPtr = next;
		}
	}

	~MRandom()
	{}
};