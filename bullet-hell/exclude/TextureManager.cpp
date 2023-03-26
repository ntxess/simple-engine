#include "TextureManager.hpp"

TextureManager::TextureManager()
{
	ParseJsonData("resources/data/texturedata.json");
}

void TextureManager::ParseJsonData(std::string filename)
{
	std::ifstream input(filename);
	std::stringstream ss;
	ss << input.rdbuf();
	std::string jsonStr = ss.str();

	rapidjson::Document doc;
	doc.Parse(jsonStr.c_str());

	const rapidjson::Value& textureDataArray = doc["texturedata"];

	for (rapidjson::SizeType i = 0; i < textureDataArray.Size(); i++)
	{
		std::string id = textureDataArray[i]["id"].GetString();
		std::string path = textureDataArray[i]["path"].GetString();
		bool reuse = textureDataArray[i]["reuse"].GetBool();
		try
		{
			thor::Resources::KnownIdStrategy strategy;
			if (reuse)
				strategy = thor::Resources::KnownIdStrategy::Reuse;
			else
				strategy = thor::Resources::KnownIdStrategy::AssumeNew;
			m_textureMap.acquire(id, thor::Resources::fromFile<sf::Texture>(path), strategy);
		}
		catch (thor::ResourceLoadingException& e)
		{
			std::cerr << "An error occurred: " << e.what() << '\n';
			std::exit(EXIT_FAILURE);
		}
	}
}

sf::Texture& TextureManager::GetTexture(const std::string name)
{
	return m_textureMap[name];
}
