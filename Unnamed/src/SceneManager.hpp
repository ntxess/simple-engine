#pragma once
#include "Scene.hpp"
#include <memory>
#include <stack>

class SceneManager
{
private:
	std::stack<std::unique_ptr<Scene>> m_scenes;
	std::unique_ptr<Scene> m_newScene;
	bool m_isRemoving;
	bool m_isAdding;
	bool m_isReplacing;

public:
	SceneManager();
	~SceneManager() = default;
	void AddScene(std::unique_ptr<Scene> newScene, bool isReplacing = true);
	void RemoveScene();
	void ProcessSceneChange();
	std::unique_ptr<Scene>& GetActiveScene();
};