#pragma once
#include <list>
#include "Scene.hpp"

class SceneManager
{
protected:
	Scene* _currentScene;
	Scene* _nextScene;
	std::list<Scene*> _sceneList;

public:
	SceneManager();
	~SceneManager();
	Scene* GetScene();
	Scene* GetNextScene();
	void LoadScene();
	void LoadNextScene();
	void AddScene(Scene* newScene);
	void SwitchScene();
	void SwitchScene(Scene* scene);
	void RemoveScene();
};