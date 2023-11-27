#pragma once
#include "Scene.h"

class ScenePlay : public Scene
{
private:
    struct PlayerConfig
    {
        float X, Y, CX, CY, SPEED, MAXSPEED, JUMP, GRAVITY;
        std::string WEAPON;
    };

//protected:
public:
    PlayerConfig m_PlayerConfig;

    int m_PlayerDirection;
    float speed = 3.0f;

public:
    ScenePlay(GameEngine* GEngine, std::string ResourcePath, std::string EntityPath);
    void InitSceneKeyMap();
    void SpawnPlayer();
    void SpawnBullet();

    //void LoadLevel(const std::string& FileName);
    Vec2 GridToPixel(float GridX, float GridY, std::shared_ptr<Entity> entity);
    void update();
    void OnEnd();

    //Systems
    void sSpawnParticle(const std::shared_ptr<Entity>& e);
    void sAnimation();
    void sMovement(float dt);
    void sLifespan();
    void sEnemySpawner();
    void sRender();
    void sDoAction(const Action& action);
    void sDebug();
};

