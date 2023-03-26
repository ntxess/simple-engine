#pragma once
#include "../Component.hpp"
#include "../System.hpp"
#include "SFML/System/Time.hpp"

class DebugSystem : public System
{
public:
	void Update(const float& dt, entt::registry& reg, entt::entity ent = entt::null)
	{
		auto& clock = reg.get<PerformanceMonitor>(ent).clock;
		auto& fps = reg.get<PerformanceMonitor>(ent).value;
		if (clock.getElapsedTime().asSeconds() >= 1.f)
		{
			std::string title = "Engine 9 | Ver 0.4.0 | FPS: ";
			title += std::to_string(int(fps));
			title += " | ";
			title += std::to_string(1000 / fps);
			title += "m/s";

			reg.get<PerformanceMonitor>(ent).rw->setTitle(title);
			fps = 0.f;
			clock.restart();
		}
		++fps;
	}
};

