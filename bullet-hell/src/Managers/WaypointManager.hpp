#pragma once
#include "../Waypoint.hpp"
#include "rapidjson/document.h"
#include "entt/entt.hpp"
#include <fstream>
#include <sstream>
#include <unordered_map>

class WaypointManager
{
private:
	std::unordered_map<entt::hashed_string::hash_type, std::unique_ptr<Waypoint>> waypointMap;

public:
	WaypointManager();
	~WaypointManager() = default;

	void ParseJsonData(std::string filename);
	Waypoint* GetWaypoint(entt::hashed_string::hash_type id);
};

