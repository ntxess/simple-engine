#pragma once
#include "../../Thor/include/Thor/Animations.hpp"
#include <fstream>
#include <string>
#include <sstream>

class AnimationFactory
{
private:
	struct AnimationData
	{
		std::string name;

	};
	// std::unordered_map<std::string,   m_animationData;

public:
	AnimationFactory()
	{
		GetAnimationData();
	}

	~AnimationFactory() = default;

	void GetAnimationData()
	{

	}

	thor::FrameAnimation GenerateFrameData(const std::string name, const std::string animationName)
	{

	}
};