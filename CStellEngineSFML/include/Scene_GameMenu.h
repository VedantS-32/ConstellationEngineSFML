#pragma once

#include "Scene.h"

class Scene_GameMenu : public Scene
{
public:
	Scene_GameMenu(GameEngine* GEngine, std::string ResourcePath, std::string EntityPath);
	void InitSceneKeyMap();
	virtual ~Scene_GameMenu();

	void update();
	void OnEnd();

    //Systems
    void sSpawnPlayer();
    void sAnimation();
    void sMovement(float dt);
    void sLifespan();
    void sRender();
    void sDoAction(const Action& action);
    void sDebug();
};
