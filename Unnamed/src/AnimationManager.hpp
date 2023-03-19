#pragma once
#include "Thor/Animations.hpp"
#include "rapidjson/document.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>

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

	void ParseJsonData(std::string filename);
	void ProcessData(const std::vector<AnimationData>& data);
public:
	AnimationManager();
	~AnimationManager() = default;

	thor::FrameAnimation GetAnimation(const std::string name);
};

