#include "WaypointManager.hpp"

WaypointManager::WaypointManager()
{
	ParseJsonData("resources/data/waypointdata.json");
}

void WaypointManager::ParseJsonData(std::string filename)
{
	std::ifstream input(filename);
	std::stringstream ss;
	ss << input.rdbuf();
	std::string jsonStr = ss.str();

	rapidjson::Document doc;
	doc.Parse(jsonStr.c_str());

	const rapidjson::Value& waypointDataArray = doc["waypointdata"];

	std::vector<Waypoint> waypointDataList;
	for (rapidjson::SizeType i = 0; i < waypointDataArray.Size(); i++)
	{
		const rapidjson::Value& waypoints = waypointDataArray[i]["movement-coords"];
		std::string id = waypointDataArray[i]["id"].GetString();

		float head_x = waypoints[0][0].GetFloat();
		float head_y = waypoints[0][1].GetFloat();
		std::unique_ptr<Waypoint> waypoint = std::make_unique<Waypoint>(sf::Vector2f(head_x, head_y));
		
		Waypoint* current;
		current = waypoint.get();
		for (rapidjson::SizeType j = 1; j < waypoints.Size(); j++)
		{
			float x = waypoints[j][0].GetFloat();
			float y = waypoints[j][1].GetFloat();
			std::unique_ptr<Waypoint> point = std::make_unique<Waypoint>(sf::Vector2f(x, y));
			
			current->AddNext(std::move(point));
			current->nextWP->distanceTotal = current->distanceTotal + current->distanceToNext;
			current = current->nextWP.get();
		}

		waypointMap[id] = std::move(waypoint);
	}
}

Waypoint* WaypointManager::GetWaypoint(const std::string name)
{
	return waypointMap[name].get();
}