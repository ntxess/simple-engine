#pragma once
#include "SFML/Graphics/Texture.hpp"
#include "Thor/Resources.hpp"
#include "rapidjson/document.h"
#include <iostream>
#include <fstream>
#include <sstream>

class TextureManager
{
private:
	thor::ResourceHolder<sf::Texture, std::string> m_textureMap;

public:
	TextureManager();
	~TextureManager() = default;

	void ParseJsonData(std::string filename);
	sf::Texture& GetTexture(const std::string name);
};

