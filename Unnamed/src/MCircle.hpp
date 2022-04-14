#pragma once

#include "WayPoint.hpp"

struct MCircle
{
public:
	WayPoint* wps;
	WayPoint* head;

	MCircle()
	{
		WayPoint* pointA = new WayPoint(sf::Vector2f(120.0f, 80.0f));
		WayPoint* pointB = new WayPoint(sf::Vector2f(210.0f, 30.0f));
		WayPoint* pointC = new WayPoint(sf::Vector2f(260.0f, 120.0f));
		WayPoint* pointD = new WayPoint(sf::Vector2f(180.0f, 190.0f));
		WayPoint* pointE = new WayPoint(sf::Vector2f(80.0f, 140.0f));

		pointA->AddNext(pointB);
		pointB->AddNext(pointC);
		pointC->AddNext(pointD);
		pointD->AddNext(pointE);

		wps = pointA;
		head = pointA;
	}

	~MCircle()
	{
		WayPoint* temp;
		while (head)
		{
			temp = head;
			head = head->_nextWP;
			delete temp;
		}
	}
};