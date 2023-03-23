#pragma once
#include "Thor/Animations/FrameAnimation.hpp"
#include "rapidjson/document.h"
#include <fstream>
#include <sstream>
#include <unordered_map>

struct AnimationData
{
	std::string name;
	int totalFrames;
	std::vector<std::vector<int>> frameBox;
	std::vector<float> frameTiming;
};

class AnimationManager
{
private:
	std::unordered_map<std::string, thor::FrameAnimation> animationMap;

public:
	AnimationManager();
	~AnimationManager() = default;

	void ParseJsonData(std::string filename);
	thor::FrameAnimation GetAnimation(const std::string name);
};

