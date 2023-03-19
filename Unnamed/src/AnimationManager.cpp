#include "AnimationManager.hpp"

AnimationManager::AnimationManager()
{
	ParseJsonData("resources/data/framedata.json");
}

void AnimationManager::ParseJsonData(std::string filename)
{
	std::ifstream input(filename);
	std::stringstream ss;
	ss << input.rdbuf();
	std::string jsonStr = ss.str();

	rapidjson::Document doc;
	doc.Parse(jsonStr.c_str());

	const rapidjson::Value& animationDataArray = doc["animationdata"];

	std::vector<AnimationData> animationDataList;
	for (rapidjson::SizeType i = 0; i < animationDataArray.Size(); i++)
	{
		const rapidjson::Value& animationDataObj = animationDataArray[i];

		AnimationData animationData;

		animationData.name = animationDataObj["id"].GetString();
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

		animationDataList.push_back(animationData);
	}

	ProcessData(animationDataList);
}

void AnimationManager::ProcessData(const std::vector<AnimationData>& data)
{
	for (auto frameData : data)
	{
		thor::FrameAnimation animation;
		for (int i = 0; i < frameData.totalFrames; ++i)
		{
			std::vector coords = frameData.frameBox[i];
			sf::IntRect frame(coords[0], coords[1], coords[2], coords[3]);
			animation.addFrame(frameData.frameTiming[i], frame);
		}
		animationMap[frameData.name] = animation;
	}
}

thor::FrameAnimation AnimationManager::GetAnimation(const std::string id)
{
	return animationMap[id];
}
