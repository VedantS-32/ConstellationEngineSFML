//#include <random>
//
//#include "Game.h"
//#include "imgui.h"
//#include "imgui-SFML.h"
//
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <format>
//#include <vector>
//
//#include <chrono>
//
//
//void Game::init(const std::string& Config)
//{
//	std::fstream GameConfig;
//	std::string Line;
//	std::string Attribute;
//	GameConfig.open(Config);
//
//	while (std::getline(GameConfig, Line))
//	{
//		std::istringstream ss(Line);
//		ss >> Attribute;
//
//		if (Attribute == "Window")
//			ss >> m_WindowConfig.W >> m_WindowConfig.H >> m_WindowConfig.FPS 
//			>> m_WindowConfig.FS;
//		if (Attribute == "Font")
//			ss >> m_FontConfig.FP >> m_FontConfig.S >> m_FontConfig.FR 
//			>> m_FontConfig.FG >> m_FontConfig.FB;
//		if (Attribute == "Player")
//			ss >> m_PlayerConfig.SR >> m_PlayerConfig.CR >> m_PlayerConfig.S 
//			>> m_PlayerConfig.FR >> m_PlayerConfig.FG >> m_PlayerConfig.FB 
//			>> m_PlayerConfig.OR >> m_PlayerConfig.OG >> m_PlayerConfig.OB 
//			>> m_PlayerConfig.OT >> m_PlayerConfig.V;
//		if (Attribute == "Enemy")
//			ss >> m_EnemyConfig.SR >> m_EnemyConfig.CR >> m_EnemyConfig.SMIN
//			>> m_EnemyConfig.SMAX >> m_EnemyConfig.OR >> m_EnemyConfig.OG 
//			>> m_EnemyConfig.OB >> m_EnemyConfig.OT >> m_EnemyConfig.VMIN
//			>> m_EnemyConfig.VMAX >> m_EnemyConfig.L >> m_EnemyConfig.SI;
//		if (Attribute == "Bullet")
//			ss >> m_BulletConfig.SR >> m_BulletConfig.CR >> m_BulletConfig.S
//			>> m_BulletConfig.FR >> m_BulletConfig.FG >> m_BulletConfig.FB 
//			>> m_BulletConfig.OR >> m_BulletConfig.OG >> m_BulletConfig.OB 
//			>> m_BulletConfig.OT >> m_BulletConfig.V >> m_BulletConfig.L;
//	}
//	GameConfig.close();
//
//	m_PlayerConfig.FA = 255.f;
//	m_PlayerColor[0] = m_PlayerConfig.FR / 255;
//	m_PlayerColor[1] = m_PlayerConfig.FG / 255;
//	m_PlayerColor[2] = m_PlayerConfig.FB / 255;
//	m_PlayerColor[3] = m_PlayerConfig.FA / 255;
//
//	m_Font.loadFromFile(m_FontConfig.FP);
//	m_Text.setFont(m_Font);
//	m_GameState = m_Text;
//	m_GameState.setFillColor(sf::Color(255, 0, 0));
//	m_GameState.setPosition(m_WindowConfig.W / 2, m_WindowConfig.H / 2);
//	m_GameState.setCharacterSize(60);
//	m_GameState.setOrigin(120, 45);
//
//	m_Text.setFillColor(sf::Color(m_FontConfig.FR, m_FontConfig.FG, m_FontConfig.FB));
//	m_BenchMark = m_Text;
//	m_BenchMark.setPosition(1000, 680);
//	m_BenchMark.setString("00");
//	m_Text.setCharacterSize(m_FontConfig.S);
//	m_Text.setString(std::format("Score: {}", m_Score));
//
//	m_Setting.antialiasingLevel = 8;
//	m_Window.create(sf::VideoMode(m_WindowConfig.W, m_WindowConfig.H), "CStellSFML", sf::Style::Default, m_Setting);
//	ImGui::SFML::Init(m_Window);
//	m_Window.setFramerateLimit(m_WindowConfig.FPS);
//
//	SpawnPlayer();
//}
//
//void Game::setPaused()
//{
//	if (!m_Paused)
//		m_Paused = true;
//	else
//		m_Paused = false;
//}
//
//void Game::sMovement()
//{
//	m_Player->cTransform->velocity = { 0, 0 };
//
//	// Player Movement
//	if (m_Player->cInput->up)
//		m_Player->cTransform->velocity.y = -5;
//	if (m_Player->cInput->down)
//		m_Player->cTransform->velocity.y = 5;
//	if (m_Player->cInput->left)
//		m_Player->cTransform->velocity.x = -5;
//	if (m_Player->cInput->right)
//		m_Player->cTransform->velocity.x = 5;
//
//	// Update Player Velocity
//	m_Player->cTransform->pos.x += m_Player->cTransform->velocity.x;
//	m_Player->cTransform->pos.y += m_Player->cTransform->velocity.y;
//
//	// Update Enemy Velocity
//	for (auto& e : m_Entities.GetEntities("Enemy"))
//	{
//		e->cTransform->pos.x += e->cTransform->velocity.x;
//		e->cTransform->pos.y += e->cTransform->velocity.y;
//	}
//
//	// Update Bullet Velocity
//	
//	for (auto& b : m_Entities.GetEntities("Bullet"))
//	{
//		b->cTransform->pos.x += (b->cTransform->velocity.x * cos(b->cTransform->vectorDirection * (PI / 180)));
//		b->cTransform->pos.y += (b->cTransform->velocity.y * sin(b->cTransform->vectorDirection * (PI / 180)));
//	}
//
//	// Update Dead Enemy Particles
//
//	for (auto& e : m_Entities.GetEntities("EnemyParticle"))
//	{
//		e->cTransform->pos.x += (3 * cos(e->cTransform->vectorDirection * (PI / 180)));
//		e->cTransform->pos.y += (3 * sin(e->cTransform->vectorDirection * (PI / 180)));
//	}
//
//}
//
//void Game::sUserInput()
//{
//	sf::Event event;
//	while (m_Window.pollEvent(event))
//	{
//		ImGui::SFML::ProcessEvent(event);
//		if (event.type == sf::Event::Closed)
//			m_Running = false;
//
//		if (event.type == sf::Event::KeyPressed)
//		{
//			switch (event.key.code)
//			{
//			case sf::Keyboard::W:
//				m_Player->cInput->up = true;
//				break;
//			case sf::Keyboard::A:
//				m_Player->cInput->left = true;
//				break;
//			case sf::Keyboard::S:
//				m_Player->cInput->down = true;
//				break;
//			case sf::Keyboard::D:
//				m_Player->cInput->right = true;
//				break;
//			default: break;
//			}
//		}
//
//		if (event.type == sf::Event::KeyReleased)
//		{
//			switch (event.key.code)
//			{
//			case sf::Keyboard::W:
//				m_Player->cInput->up = false;
//				break;
//			case sf::Keyboard::A:
//				m_Player->cInput->left = false;
//				break;
//			case sf::Keyboard::S:
//				m_Player->cInput->down = false;
//				break;
//			case sf::Keyboard::D:
//				m_Player->cInput->right = false;
//				break;
//			case sf::Keyboard::P:
//				if (!m_SpecialAttackPause)
//					setPaused();
//				break;
//			case sf::Keyboard::E:
//				SpawnSpecialWeapon();
//				break;
//			case sf::Keyboard::Escape:
//				if (!m_SpecialAttackPause)
//					setPaused();
//				break;
//			case sf::Keyboard::R:
//				if (m_GameOver)
//					RestartGame();
//				break;
//			default: break;
//			}
//		}
//
//		if (event.type == sf::Event::MouseButtonPressed)
//		{
//			if (event.mouseButton.button == sf::Mouse::Left && !m_Paused && !m_GameOver)
//			{
//				//log("LeftMouseClick x: " << event.mouseButton.x << " " << "y: " << event.mouseButton.y);
//				// Spawn Bullet
//				SpawnBullet(m_Player, Vec2(event.mouseButton.x, event.mouseButton.y));
//			}
//
//			if (event.mouseButton.button == sf::Mouse::Right)
//			{
//				// Call Special Weapon
//				if (!m_SpecialAttackPause)
//					m_SpecialAttackPause = true;
//				else
//					m_SpecialAttackPause = false;
//			}
//		}
//	}
//}
//
//void Game::sLifespan()
//{
//	for (auto& e : m_Entities.GetEntities())
//	{
//		if(e->tag() != "Player" && e->tag() != "Enemy")
//		{
//			e->cLifespan->remaining -= 1;
//			sf::Color sColor = e->cShape->circle.getFillColor();
//			sf::Color sOutlineColor = e->cShape->circle.getOutlineColor();
//			float temp = (1 / float(e->cLifespan->total)) * 255;
//			int alpha = e->cShape->circle.getFillColor().a;
//			e->cShape->circle.setFillColor(sf::Color(sColor.r, sColor.g, sColor.b, (alpha - temp)));
//			e->cShape->circle.setOutlineColor(sf::Color(sOutlineColor.r, sOutlineColor.g, sOutlineColor.b, (alpha - temp)));
//			//log(int(e->cShape->circle.getFillColor().a));
//
//			if (e->cShape->circle.getFillColor().a <= 1.0f)
//			{
//				//SpawnSmallEnemies(e);
//				e->destroy();
//			}
//		}
//		
//	}
//}
//
//void Game::sRender()
//{
//	m_Window.clear(sf::Color(137, 142, 140, 255));
//	
//	ImGui::SFML::Update(m_Window, m_DeltaClock.restart());
//
//	ImGui::Begin("UmGui");
//	ImGui::Text("Hello, GUI");
//	ImGui::SliderFloat("PlayerRadius", &m_PlayerConfig.SR, 1.f, 300.f);
//	ImGui::SliderInt("Side", &m_PlayerConfig.V, 3, 64);
//	ImGui::ColorEdit4("PlayerColor", m_PlayerColor);
//	ImGui::End();
//
//	m_Player->cShape->circle.setRadius(m_PlayerConfig.SR);
//	m_Player->cShape->circle.setPointCount(m_PlayerConfig.V);
//	m_Player->cShape->circle.setFillColor(sf::Color(m_PlayerColor[0] * 255,
//													m_PlayerColor[1] * 255,
//													m_PlayerColor[2] * 255,
//													m_PlayerColor[3] * 255));
//	m_Player->cShape->circle.setOrigin(m_PlayerConfig.SR, m_PlayerConfig.SR);
//
//	m_Text.setString(std::format("Score: {}", m_Score));
//	m_Window.draw(m_Text);
//	m_Window.draw(m_GameState);
//	//m_Window.draw(m_BenchMark);
//
//	for (auto& e : m_Entities.GetEntities())
//	{
//		e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
//		e->cTransform->angle += 1.0f;
//		e->cShape->circle.setRotation(e->cTransform->angle);
//
//		m_Window.draw(e->cShape->circle);
//	}
//
//	ImGui::SFML::Render(m_Window);
//	m_Window.display();
//}
//
//void Game::sEnemySpawner()
//{
//	if (m_CurrentFrame - m_LastEnemySpawnTime == 450)
//	{
//		SpawnEnemy();
//	}
//}
//
//void Game::sCollision()
//{
//	for (auto& b : m_Entities.GetEntities("Bullet"))
//	{
//		for (auto& e : m_Entities.GetEntities("Enemy"))
//		{
//			// Check for Collision
//			int tempE = sqrt((e->cTransform->pos.x - b->cTransform->pos.x)* (e->cTransform->pos.x - b->cTransform->pos.x)
//				+ (e->cTransform->pos.y - b->cTransform->pos.y)* (e->cTransform->pos.y - b->cTransform->pos.y));
//			int tempB = e->cShape->circle.getRadius() + b->cShape->circle.getRadius();
//			if (tempE < tempB)
//			{
//				SpawnSmallEnemies(e);
//				AddScore(e);
//				e->destroy();
//				b->destroy();
//			}
//		}
//	}
//}
//
//void Game::SpawnPlayer()
//{
//	auto entity = m_Entities.AddEntity("Player");
//
//	float mx = m_WindowConfig.W / 2;
//	float my = m_WindowConfig.H / 2;
//	
//	m_PlayerRadius = m_PlayerConfig.SR;
//
//	entity->cTransform = std::make_shared<CTransform>(Vec2(mx, my), Vec2(m_PlayerConfig.S, m_PlayerConfig.S), 0.0f);
//
//	entity->cShape = std::make_shared<CShape>(m_PlayerConfig.SR, m_PlayerConfig.V,
//									sf::Color(m_PlayerConfig.FR, m_PlayerConfig.FG, m_PlayerConfig.FB, m_PlayerConfig.FA),
//									sf::Color(m_PlayerConfig.OR, m_PlayerConfig.OG, m_PlayerConfig.OB), m_PlayerConfig.OT);
//	entity->cShape->circle.setOrigin(m_PlayerConfig.SR, m_PlayerConfig.SR);
//
//	entity->cInput = std::make_shared<CInput>();
//
//	m_Player = entity;
//}
//
//void Game::sWallCollision()
//{
//	for (auto& e : m_Entities.GetEntities("Enemy"))
//	{
//		// Check for Collision
//		if (e->cTransform->pos.x > (m_WindowConfig.W - e->cShape->circle.getRadius())
//			|| e->cTransform->pos.x < (0 + e->cShape->circle.getRadius()))
//		{
//			e->cTransform->velocity.x *= -1;
//		}
//		if (e->cTransform->pos.y > (m_WindowConfig.H - e->cShape->circle.getRadius())
//			|| e->cTransform->pos.y < (0 + e->cShape->circle.getRadius()))
//		{
//			e->cTransform->velocity.y *= -1;
//		}
//	}
//}
//
//void Game::SpawnEnemy()
//{
//	auto entity = m_Entities.AddEntity("Enemy");
//
//	float sx = RandomNumberGen(0 + m_EnemyConfig.SR, m_WindowConfig.W - m_EnemyConfig.SR);
//	float sy = RandomNumberGen(0 + m_EnemyConfig.SR, m_WindowConfig.H - m_EnemyConfig.SR);
//	float sSpeedx = RandomNumberGen(-m_EnemyConfig.SMIN, m_EnemyConfig.SMAX);
//	float sSpeedy = RandomNumberGen(-m_EnemyConfig.SMIN, m_EnemyConfig.SMAX);
//	float sVertices = RandomNumberGen(m_EnemyConfig.VMIN, m_EnemyConfig.VMAX);
//	int sR = RandomNumberGen(0, 255);
//	int sG = RandomNumberGen(0, 255);
//	int sB = RandomNumberGen(0, 255);
//
//	entity->cTransform = std::make_shared<CTransform>(Vec2(sx, sy), Vec2(sSpeedx, sSpeedy), 0.0f);
//
//	entity->cShape = std::make_shared<CShape>(m_EnemyConfig.SR, sVertices,
//		sf::Color(sR, sG, sB),
//		sf::Color(m_EnemyConfig.OR, m_EnemyConfig.OG, m_EnemyConfig.OB), m_EnemyConfig.OT);
//	entity->cShape->circle.setOrigin(m_EnemyConfig.SR, m_EnemyConfig.SR);
//	entity->cLifespan = std::make_shared<CLifespan>(m_EnemyConfig.L);
//
//	// Record when the most recent enemy was spawned
//	m_LastEnemySpawnTime = m_CurrentFrame;
//}
//
//void Game::SpawnSmallEnemies(std::shared_ptr<Entity> entity)
//{
//	float sSides = entity->cShape->circle.getPointCount();
//	float sInternalAngle = 360 / sSides;
//	float sTangent = sInternalAngle;
//	for (int i = 0; i < sSides; i++)
//	{
//		auto enemyParticle = m_Entities.AddEntity("EnemyParticle");
//		enemyParticle->cTransform = std::make_shared<CTransform>(entity->cTransform->pos, Vec2(entity->cTransform->velocity), 0, sTangent);
//		sTangent += sInternalAngle;
//		enemyParticle->cShape = std::make_shared<CShape>(15, sSides,
//								entity->cShape->circle.getFillColor(), entity->cShape->circle.getOutlineColor(), 1);
//		enemyParticle->cShape->circle.setOrigin(15, 15);
//		enemyParticle->cLifespan = std::make_shared<CLifespan>(m_EnemyConfig.L);
//		//log(enemyParticle->cTransform->vectorDirection);
//	}
//}
//
//void Game::SpawnBullet(std::shared_ptr<Entity> Entity, const Vec2& MousePos)
//{
//	auto bullet = m_Entities.AddEntity("Bullet");
//	Vec2 sPos = { MousePos - m_Player->cTransform->pos };
//	float sTangent = atan2(sPos.y, sPos.x) * (180 / PI);
//	bullet->cTransform = std::make_shared<CTransform>(m_Player->cTransform->pos, Vec2(m_BulletConfig.V, m_BulletConfig.V), 0, sTangent);
//	bullet->cShape = std::make_shared<CShape>(10, 8, sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 0), 2);
//	bullet->cShape->circle.setOrigin(10, 10);
//	bullet->cLifespan = std::make_shared<CLifespan>(m_BulletConfig.L);
//}
//
//void Game::AddScore(std::shared_ptr<Entity> Entity)
//{
//	int sTempScore = Entity->cShape->circle.getPointCount() * 100;
//	m_Score += sTempScore;
//}
//
//void Game::SpawnSpecialWeapon()
//{
//	for (auto& e : m_Entities.GetEntities())
//	{
//		if(e->tag() != "Player" && e->tag() != "EnemyParticle")
//		{
//			SpawnSmallEnemies(e);
//			e->destroy();
//		}
//	}
//}
//
//void Game::SetGameOver()
//{
//	if (!m_GameOver)
//		m_GameOver = true;
//	else
//		m_GameOver = false;
//	m_GameState.setString("GameOver\nPress R to Player Again");
//}
//
//float Game::RandomNumberGen(float Min, float Max)
//{
//	std::random_device rd; // obtain a random number from hardware
//	std::mt19937 gen(rd()); // seed the generator
//	std::uniform_int_distribution<> distr(Min, Max); // define the range
//	return distr(gen);
//}
//
//Game::Game(const std::string& ConfigPath) : m_Score(0)
//{
//	m_Running = true;
//	init(ConfigPath);
//}
//
//void Game::RestartGame()
//{
//	m_Entities.Update();
//	m_GameOver = false;
//	m_Score = 0;
//	m_GameState.setString("");
//	SpawnPlayer();
//}
//
//Game::~Game()
//{
//	ImGui::SFML::Shutdown();
//}
//
//void Game::CheckGameState()
//{
//	if (m_Entities.GetEntities("Enemy").size() > 25)
//		SetGameOver();
//}
//
//void Game::run()
//{
//	//TODO: Add pause funtionality here
//	//		Some systems should function while paused (Rendering)
//	//		Some systems shouldn't (Movement / Input)
//
//	while (m_Running)
//	{
//		m_Entities.Update();
//
//		if (!m_Paused && !m_SpecialAttackPause && !m_GameOver)
//		{
//			sEnemySpawner();//1
//			sMovement();//2
//			sCollision();//3
//			sWallCollision();//4
//
//		}
//		sUserInput();//5
//		sRender();//6
//		if (!m_Paused && !m_SpecialAttackPause && !m_GameOver)
//		{
//			sLifespan();//7
//			//increment the current frame
//			//may need to be moved when pause implemented
//			m_CurrentFrame++;
//			//CheckGameState();
//		}
//		if (m_GameOver)
//		{
//			for (auto& e : m_Entities.GetEntities())
//			{
//				e->destroy();
//			}
//		}
//	}
//	
//}
//
//
