#pragma once
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "Thor/Animations/FrameAnimation.hpp"
#include "Thor/Animations/Animator.hpp"
#include "rapidjson/document.h"
#include <fstream>
#include <sstream>
#include <unordered_map>

class SpriteManager
{
private:
	struct SpriteData
	{
		sf::Texture texture;
		thor::Animator<sf::Sprite, std::string> animator;
	};

	struct AnimationData
	{
		std::string id;
		int totalFrames;
		std::vector<std::vector<int>> frameBox;
		std::vector<float> frameTiming;
	};

	std::unordered_map<std::string, SpriteData> m_spriteMap;

public:
	SpriteManager();
	~SpriteManager() = default;

	void ParseJsonData(std::string filename);
	sf::Texture& GetTexture(const std::string name);
	thor::Animator<sf::Sprite, std::string> GetAnimator(const std::string name);
};

