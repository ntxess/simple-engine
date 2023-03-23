#pragma once
#include "../Waypoint.hpp"
#include "rapidjson/document.h"
#include <fstream>
#include <sstream>
#include <unordered_map>

class WaypointManager
{
private:
	std::unordered_map<std::string, std::unique_ptr<Waypoint>> waypointMap;

public:
	WaypointManager();
	~WaypointManager() = default;

	void ParseJsonData(std::string filename);
	Waypoint* GetWaypoint(const std::string name);
};

