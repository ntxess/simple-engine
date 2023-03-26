#include "SpriteManager.hpp"

SpriteManager::SpriteManager()
{
	ParseJsonData("resources/data/spritedata.json");
}

void SpriteManager::ParseJsonData(std::string filename)
{
	std::ifstream input(filename);
	std::stringstream ss;
	ss << input.rdbuf();
	std::string jsonStr = ss.str();

	rapidjson::Document doc;
	doc.Parse(jsonStr.c_str());

	const rapidjson::Value& entityDataArray = doc["entitydata"];

	for (rapidjson::SizeType i = 0; i < entityDataArray.Size(); i++)
	{
		std::string id = entityDataArray[i]["id"].GetString();
		std::string path = entityDataArray[i]["path"].GetString();

		if (!m_spriteMap[id].texture.loadFromFile(path))
			std::exit(EXIT_FAILURE);

		const rapidjson::Value& animationDataArray = entityDataArray[i]["animation"];
		if (!animationDataArray.Empty())
		{
			for (rapidjson::SizeType i = 0; i < animationDataArray.Size(); i++)
			{
				const rapidjson::Value& animationDataObj = animationDataArray[i];

				AnimationData animationData;

				animationData.id = animationDataObj["id"].GetString();
				animationData.totalFrames = animationDataObj["totalframe"].GetInt();

				const rapidjson::Value& frameBoxArray = animationDataObj["framebox"];
				for (rapidjson::SizeType j = 0; j < frameBoxArray.Size(); j++)
				{
					const rapidjson::Value& frameBoxArrayElem = frameBoxArray[j];
					std::vector<int> frameBox;

					for (rapidjson::SizeType k = 0; k < frameBoxArrayElem.Size(); k++)
						frameBox.push_back(frameBoxArrayElem[k].GetInt());

					animationData.frameBox.push_back(frameBox);
				}

				const rapidjson::Value& frameTimingArray = animationDataObj["frametiming"];

				for (rapidjson::SizeType j = 0; j < frameTimingArray.Size(); j++)
					animationData.frameTiming.push_back(frameTimingArray[j].GetFloat());

				thor::FrameAnimation animation;
				for (int x = 0; x < animationData.totalFrames; x++)
				{
					std::vector coords = animationData.frameBox[x];
					sf::IntRect frame(coords[0], coords[1], coords[2], coords[3]);
					animation.addFrame(animationData.frameTiming[x], frame);
				}

				float duration = animationDataObj["duration"].GetFloat();
				m_spriteMap[id].animator.addAnimation(animationData.id, animation, sf::seconds(duration));
			}
		}
	}

	input.close();
}

sf::Texture& SpriteManager::GetTexture(const std::string name)
{
	return m_spriteMap[name].texture;
}

thor::Animator<sf::Sprite, std::string> SpriteManager::GetAnimator(const std::string name)
{
	return m_spriteMap[name].animator;
}
