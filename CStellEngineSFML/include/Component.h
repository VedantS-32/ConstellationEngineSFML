#pragma once

#include "Vec2.h"
#include <SFML/Graphics.hpp>

#include "Animation.h"

class Component
{
public:
	bool Has = false;
};

class CTransform : public Component
{
public:
	Vec2 pos = { 0.0, 0.0 };
	Vec2 previousPos = { 0.0, 0.0 };
	Vec2 velocity = { 0.0, 0.0 };
	Vec2 scale = { 1.0, 1.0 };
	Vec2 vectorVelocity = { 0.0, 0.0 };
	Vec2 acceleration = { 0.0, 0.0 };
	float vectorDirection = 0;
	double angle = 0;

	CTransform() {}
	CTransform(const Vec2& p)
		: pos(p) {}
	//CTransform(const Vec2& p, const Vec2& v, float a, float tangent = 0)
	//	: pos(p), velocity(v), angle(a), vectorDirection(tangent) {}
	CTransform(const Vec2& p, const Vec2& s, float a)
		: pos(p), scale(s), angle(a) {}
};

class CShape : public Component
{
public:
	sf::CircleShape circle;

	CShape(float radius, int points, const sf::Color& fill, const sf::Color& outline, float thickness)
		: circle(radius, points)
	{
		circle.setFillColor(fill);
		circle.setOutlineColor(outline);
		circle.setOutlineThickness(thickness);
		circle.setOrigin(radius, radius);
	}
};

class CCircleCollision : public Component
{
public:
	float radius = 0;
	CCircleCollision(float r)
		: radius(r) {}
};

class CScore : public Component
{
public:
	int score = 0;
	CScore(int s)
		: score(s) {}
};

class CLifespan : public Component
{
public:
	int remaining = 0;		//Legacy
	int total = 0;			//Legacy

	int lifespan = 0;
	int frameCreated = 0;

	CLifespan() {}
	CLifespan(int total)						//Legacy
		: remaining(total), total(total) {}

	CLifespan(int Duration, int Frame)
		: lifespan(Duration), frameCreated(Frame) {}
};

class CInput : public Component
{
public:
	bool up = false;
	bool left = false;
	bool right = false;
	bool down = false;
	bool shoot = false;
	bool canShoot = true;
	bool canJump = false;

	CInput() {}
};

class CBoundingBox : public Component
{
public:
	Vec2 size = { 64.0f, 64.0f };
	Vec2 halfSize = { 32.0f, 32.0f };
	bool dynamic = false;
	
	CBoundingBox() {}
	CBoundingBox(const Vec2& v)
		: size(v), halfSize(v.x / 2.0f, v.y / 2.0f) {}
	CBoundingBox(const Vec2& v, bool Dynamic)
		: size(v), halfSize(v.x / 2.0f, v.y / 2.0f), dynamic(Dynamic) {}
};

class CAnimation : public Component
{
public:
	Animation animation;
	bool repeat = false;
	CAnimation() {}
	CAnimation(const Animation& anim, bool r = false)
		: animation(anim), repeat(r) {}
};

class CSprite : public Component
{
public:
	std::string textureName;
	sf::Texture spriteTexture;
	sf::Sprite sprite;
	Vec2 origin = { 0.0, 0.0 };

	CSprite() {}

	CSprite(const sf::Texture& spriteTexture, std::string textureName = "DefaultName")
		: textureName(textureName), spriteTexture(spriteTexture)
	{
		sprite.setTexture(spriteTexture);
	}
};

class CGravity : public Component
{
public:
	float gravity = 0;
	Vec2 jumpAccleration = { 0, 0 };
	CGravity() {}
	CGravity(float g) : gravity(g) {}
	CGravity(Vec2 v) : jumpAccleration(v) {}
};

class CState : public Component
{
public:
	bool walking = false;
	bool idle = true;
	bool onFloor = false;
	bool selected = false;
	bool mouseHover = false;
	std::string state = "CanJump";
	CState() {}
	CState(const std::string& s) : state(s) {}
};