#include "AnimationManager.hpp"

AnimationManager::AnimationManager()
{
	ParseDataFromFile("resources/framedata/data.txt");
}

void AnimationManager::ParseDataFromFile(std::string filename)
{
	std::ifstream input(filename);
	std::vector<std::unique_ptr<AnimationData>> animationData;
	std::string line;
	while (std::getline(input, line)) 
	{
		if (line.empty() || line[0] == '#' || line == "END")
			continue; 

		if (line == "START")
		{
			std::getline(input, line);
			std::unique_ptr<AnimationData> data = std::make_unique<AnimationData>();
			std::stringstream ssLine(line);
			std::string token;

			ssLine >> token;
			if (token == "Name:")
				ssLine >> data->name;
			
			ssLine.clear();
			std::getline(input, line);
			ssLine.str(line);

			ssLine >> token;
			if (token == "TotalFrame:")
				ssLine >> token;
			data->totalFrames = (stoi(token));
			
			ssLine.clear();
			std::getline(input, line);
			ssLine.str(line);

			ssLine >> token;
			if (token == "FrameBox:")
			{
				for (int i = 0; i < data->totalFrames; ++i)
				{
					ssLine.clear();
					std::getline(input, line);
					ssLine.str(line);
					std::vector<int> points;
					while (getline(ssLine, token, ','))
						points.push_back(int(stoi(token)));
					data->frameBox.push_back(points);
				}
			}

			ssLine.clear();
			std::getline(input, line);
			ssLine.str(line);

			ssLine >> token;
			if (token == "FrameTiming:")
			{
				ssLine.clear();
				std::getline(input, line);
				ssLine.str(line);
				for (int i = 0; i < data->totalFrames; ++i)
				{
					ssLine >> token;
					data->frameTiming.push_back(stoi(token));
				}
			}

			animationData.push_back(std::move(data));
		}
	}
	input.close();

	ProcessData(animationData);
}

void AnimationManager::ProcessData(const std::vector<std::unique_ptr<AnimationData>>& data)
{
	for (auto& frameData : data)
	{
		thor::FrameAnimation animation;
		for (int i = 0; i < frameData->totalFrames; ++i)
		{
			std::vector coords = frameData->frameBox[i];
			sf::IntRect frame(coords[0], coords[1], coords[2], coords[3]);
			animation.addFrame(frameData->frameTiming[i], frame);
		}
		animationMap[frameData->name] = animation;
	}
}

thor::FrameAnimation AnimationManager::GetAnimation(const std::string id)
{
	return animationMap[id];
}
