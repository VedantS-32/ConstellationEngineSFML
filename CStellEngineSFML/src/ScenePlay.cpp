#include "ScenePlay.h"


ScenePlay::ScenePlay(GameEngine* GEngine, std::string ResourcePath, std::string EntityPath)
	: Scene(GEngine, ResourcePath, EntityPath)
{
	InitScene();
	InitSceneKeyMap();
	SpawnPlayer();
}

void ScenePlay::InitSceneKeyMap()
{
	//Register all gameplay actions
	RegisterAction(sf::Keyboard::W, "MoveForward");
	RegisterAction(sf::Keyboard::A, "MoveLeft");
	RegisterAction(sf::Keyboard::S, "MoveFront");
	RegisterAction(sf::Keyboard::D, "MoveRight");

	RegisterAction(sf::Keyboard::Space, "Jump");

	m_GridText.setCharacterSize(12);
	m_GridText.setFont(m_Asset.GetFont("SomeTimeLater"));
}

Vec2 ScenePlay::GridToPixel(float GridX, float GridY, std::shared_ptr<Entity> entity)
{
	// This function takes in a grid (x, y) position and an entity
	// Return a Vec2 indicating where the CENTER position of the Entity should be
	// You must use the Entity's Animation size to the position it correctly
	// The size of the grid width and height is stored in m_GridSize.X and m_GridSize.Y
	// The bottom-left corner of the animation should align with the bottom left of the grid cell

	return Vec2(0, 0);
}

void ScenePlay::SpawnPlayer()
{
	auto& e = m_Player->GetComponent<CTransform>();
	e.pos = Vec2(100.0f, 600.0f);
	m_PlayerDirection = abs(e.scale.x);
}

void ScenePlay::SpawnBullet()
{
}

void ScenePlay::update()
{
	m_EntityManager.Update();
	if(!m_Game->m_EditorMode)
	{
		sMovement(1.0);
	}
	sLifespan();
	sAnimation();
	sRender();
	sSceneSystemUpdate();
}

void ScenePlay::OnEnd()
{
	// When the scene ends, change back to the Menu scene
	// Use m_Game->ChangeScene(Correct Params);
}

void ScenePlay::sAnimation()
{
	auto& playerTransform = m_Player->GetComponent<CTransform>();
	auto& playerScale = m_Player->GetComponent<CTransform>().scale;
	auto& playerAnimation = m_Player->GetComponent<CAnimation>().animation;
	auto& playerGravity = m_Player->GetComponent<CGravity>().jumpAccleration;
	auto& playerInput = m_Player->GetComponent<CInput>();

	if (playerInput.left)
	{
		playerScale.x = -m_PlayerDirection;
	}
	if (playerInput.right)
	{
		playerScale.x = m_PlayerDirection;
	}
	
	if (m_Player->GetComponent<CState>().onFloor)
	{
		if (playerInput.right || playerInput.left)
		{
			if (playerAnimation.GetName() != "PlayerRun")
			{
				playerAnimation.ChangeAnimation("PlayerRun");
			}
		}
		if (!playerInput.right && !playerInput.left)
		{
			if (playerAnimation.GetName() != "PlayerIdle")
			{
				playerAnimation.ChangeAnimation("PlayerIdle");
			}
		}
	}

	float v = playerTransform.pos.y - playerTransform.previousPos.y;
	if (!m_Player->GetComponent<CState>().onFloor)
	{
		if (v < 0)
		{
			if(playerAnimation.GetName() != "PlayerJumping")
			{
				playerAnimation.ChangeAnimation("PlayerJumping");
			}
		}
		if (v >= 0)
		{
			if (playerAnimation.GetName() != "PlayerFalling")
			{
				playerAnimation.ChangeAnimation("PlayerFalling");
			}
		}
	}

	playerAnimation.UpdateAnimation();
}

void ScenePlay::sSpawnParticle(const std::shared_ptr<Entity>& e)
{
	auto& sSpawnPos = e->GetComponent<CTransform>().pos;
	//sSpawnPos.y -= 500;
	int particles = m_Physics.RandomNumberGen(2, 5);
	for (int i = 0; i <= particles; i++)
	{
		auto p = m_EntityManager.AddEntity("Brick Particle");
		p->AddComponent<CTransform>(sSpawnPos);
		p->GetComponent<CTransform>().scale = { 0.5f, 0.5f };
		p->AddComponent<CSprite>(m_Asset.GetTexture("Brick"));
		p->GetComponent<CSprite>().sprite.setOrigin(m_Asset.GetTexture("Brick").getSize().x / 2.0f,
			m_Asset.GetTexture("Brick").getSize().y / 2.0f);
		Vec2 v = { m_Physics.RandomNumberGen(-2, 2), m_Physics.RandomNumberGen(-12, -11) };
		p->AddComponent<CGravity>(v);
	}
}

void ScenePlay::sMovement(float dt)
{
	Vec2 PlayerVelocity(0, 0);
	auto& playerInput = m_Player->GetComponent<CInput>();
	auto& playerState = m_Player->GetComponent<CState>();
	auto& playerTransform = m_Player->GetComponent<CTransform>();
	playerTransform.velocity.x = PlayerVelocity.x;

	if (playerInput.up)
	{
		PlayerVelocity.y = -speed;
	}
	if (playerInput.left)
	{
		PlayerVelocity.x = -speed;
	}
	if (playerInput.down)
	{
		PlayerVelocity.y = speed;
	}
	if (playerInput.right)
	{
		PlayerVelocity.x = speed;
	}
	if (playerInput.canJump)
	{
		if(playerState.onFloor)
		{
			playerState.onFloor = false;
			m_Player->GetComponent<CGravity>().jumpAccleration.y = -20.0f;
			playerInput.canJump = false;
		}
	}

	playerTransform.velocity = PlayerVelocity;
}

void ScenePlay::sLifespan()
{
}

void ScenePlay::sEnemySpawner()
{
}

void ScenePlay::sRender()
{
	// Color the background darker so you know that the game is paused
	if (!m_Pause) { m_Game->Window().clear(sf::Color(100, 100, 255)); }
	else { m_Game->Window().clear(sf::Color(50, 50, 150)); }


	// Set the viewport of the window to be centered on the player if it's far enough right
	Vec2 pPos = m_Player->GetComponent<CTransform>().pos;
	float windowCenterX = std::max(m_Game->Window().getSize().x / 2.0f, pPos.x);
	m_View = m_Game->Window().getView();
	m_View.setCenter(windowCenterX, m_Game->Window().getSize().y - m_View.getCenter().y);
	UpdateAttribute();
	m_Game->Window().setView(m_View);

	//Draw all Entity textures and animation
}

void ScenePlay::sDoAction(const Action& action)
{
	auto& playerInput = m_Player->GetComponent<CInput>();
	auto& playerState = m_Player->GetComponent<CState>();
	if (action.Type() == "Start")
	{
		//Game Input
		if (!m_Game->m_EditorMode)
		{
			if (action.Name() == "MoveForward")
			{
				playerInput.up = true;
				playerState.walking = true;
			}
			else if (action.Name() == "MoveLeft")
			{
				playerInput.left = true;
				playerState.walking = true;
			}
			else if (action.Name() == "MoveFront")
			{
				playerInput.down = true;
				playerState.walking = true;
			}
			else if (action.Name() == "MoveRight")
			{
				playerInput.right = true;
				playerState.walking = true;
			}
			else if (action.Name() == "Jump")
			{
				if (playerState.onFloor)
				{
					playerInput.canJump = true;
				}
			}
		}
		//Game Input End

	}
	else if (action.Type() == "End")
	{
		//Game Input
		if (!m_Game->m_EditorMode)
		{
			if (action.Name() == "MoveForward")
			{
				playerInput.up = false;
				playerState.walking = false;
			}
			else if (action.Name() == "MoveLeft")
			{
				playerInput.left = false;
				playerState.walking = false;
			}
			else if (action.Name() == "MoveFront")
			{
				playerInput.down = false;
				playerState.walking = false;
			}
			else if (action.Name() == "MoveRight")
			{
				playerInput.right = false;
				playerState.walking = false;
			}
			else if (action.Name() == "Jump")
			{
				playerInput.canJump = false;
			}
		}
		//Game Input End
	}
}

void ScenePlay::sDebug()
{
	for (auto& e : m_EntityManager.GetEntities())
	{
		console_log(e->tag());
	}
}
