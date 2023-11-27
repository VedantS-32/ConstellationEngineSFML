//#pragma once
//
////#include "Entity.h"
//#include "EntityManager.h"
//
//#include <SFML/Graphics.hpp>
//
//#define log(x) std::cout<<x<<std::endl
//#define PI 3.14159265
//
//struct WindowConfig { float W, H; int FPS; float FS; };
//struct FontConfig { std::string FP; int S, FR, FB, FG; };
//struct PlayerConfig { float SR; int CR; float FR, FG, FB, FA; int OR, OG, OB, OT, V; float S; };
//struct EnemyConfig { int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX; };
//struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float L, S; };
//
//class Game
//{
//	sf::RenderWindow m_Window;
//	EntityManager m_Entities;
//	sf::Font m_Font;
//	sf::Text m_Text;
//	sf::Text m_BenchMark;
//	sf::Text m_GameState;
//	sf::Event ListenEvent;
//	sf::Clock m_DeltaClock;
//	WindowConfig m_WindowConfig;
//	FontConfig m_FontConfig;
//	PlayerConfig m_PlayerConfig;
//	EnemyConfig m_EnemyConfig;
//	BulletConfig m_BulletConfig;
//	long unsigned int m_Score;
//	int m_CurrentFrame = 0;
//	int m_LastEnemySpawnTime = 0;
//	bool m_Paused = false;			//Whether we update game logic
//	bool m_Running = false;			//Whether the game is running
//	bool m_SpecialAttackPause = false;
//	bool m_GameOver = false;
//
//	float m_PlayerRadius;
//	float m_PlayerColor[4];
//
//	//Setting
//	sf::ContextSettings m_Setting;
//
//	std::shared_ptr<Entity> m_Player;
//
//	void init(const std::string& Config); //Initialize the GameState with a config filepath
//	void setPaused();		  //Pause the Game
//
//	void sMovement();
//	void sUserInput();
//	void sLifespan();
//	void sRender();
//	void sEnemySpawner();
//	void sCollision();
//	void sWallCollision();
//
//	void AddScore(std::shared_ptr<Entity> Entity);
//	void CheckGameState();
//	void SetGameOver();
//	void RestartGame();
//
//	void SpawnPlayer();
//	void SpawnEnemy();
//	void SpawnSmallEnemies(std::shared_ptr<Entity> Entity);
//	void SpawnBullet(std::shared_ptr<Entity> Entity, const Vec2& MousePos);
//	void SpawnSpecialWeapon();
//
//public:
//	Game(const std::string& config); //Constructor reads config file
//	~Game();
//
//	float RandomNumberGen(float Min, float Max);
//
//	void run();
//};