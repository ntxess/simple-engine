#pragma once
#include <random>
#include "WayPoint.hpp"

struct MRandom
{
public:
	WayPoint* wps;
	WayPoint* head;

	MRandom()
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(100, 700);

		WayPoint* pointA = new WayPoint(sf::Vector2f(float(dist6(rng)), float(dist6(rng))));
		WayPoint* pointB = new WayPoint(sf::Vector2f(float(dist6(rng)), float(dist6(rng))));
		WayPoint* pointC = new WayPoint(sf::Vector2f(float(dist6(rng)), float(dist6(rng))));
		WayPoint* pointD = new WayPoint(sf::Vector2f(float(dist6(rng)), float(dist6(rng))));
		WayPoint* pointE = new WayPoint(sf::Vector2f(float(dist6(rng)), float(dist6(rng))));
		WayPoint* pointF = new WayPoint(sf::Vector2f(float(dist6(rng)), float(dist6(rng))));
		WayPoint* pointG = new WayPoint(sf::Vector2f(float(dist6(rng)), float(dist6(rng))));
		WayPoint* pointH = new WayPoint(sf::Vector2f(float(dist6(rng)), float(dist6(rng))));
		WayPoint* pointI = new WayPoint(sf::Vector2f(float(dist6(rng)), float(dist6(rng))));
		WayPoint* pointJ = new WayPoint(sf::Vector2f(float(dist6(rng)), float(dist6(rng))));

		pointA->AddNext(pointB);
		pointB->AddNext(pointC);
		pointC->AddNext(pointD);
		pointD->AddNext(pointE);
		pointE->AddNext(pointF);
		pointF->AddNext(pointG);
		pointG->AddNext(pointH);
		pointH->AddNext(pointI);
		pointI->AddNext(pointJ);
													 
		wps = pointA;
		head = pointA;
	}

	~MRandom()
	{
		WayPoint* next;
		while (head != NULL)
		{
			next = head->_nextWP;
			delete head;
			head = next;
		}
	}
};