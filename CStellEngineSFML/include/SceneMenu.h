#pragma once
#include"Scene.h"
#include<deque>

class SceneMenu :
	public Scene
{
protected:
	std::string m_Tittle;
	sf::Text m_MenuText;
	std::vector<std::string> m_MenuString;
	std::vector<std::string> m_LevelPath;
	size_t m_SelectedMenuIndex = 0;

	void init();
	void OnEnd();

public:
	explicit SceneMenu(GameEngine* GEngine);
	void update();
	void sDoAction(const Action& action);
	void sRender();
};
