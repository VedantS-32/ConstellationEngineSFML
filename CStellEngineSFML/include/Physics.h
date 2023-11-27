#pragma once
#include "Vec2.h"
#include <memory>

class Entity;

class Physics
{
public:
	Vec2 m_Overlap = { 0, 0 };
	Vec2 m_PreviousOverlap = { 0, 0 };
	Vec2 m_MouseOverlap = { 0, 0 };
	Vec2 m_Gravity = { 0.0f, 10.0f };

	Vec2 GetOverlap(const std::shared_ptr<Entity>& e, const std::shared_ptr<Entity>& f);
	Vec2 GetPreviousOverlap(const std::shared_ptr<Entity>& e, const std::shared_ptr<Entity>& f);
	void GetOverlappingEntity(const std::shared_ptr<Entity>& e, Vec2 mousePos);

	void ApplyGravity(const std::shared_ptr<Entity>& e);
	float RandomNumberGen(float Min, float Max);
	void UpdateGravity(const std::shared_ptr<Entity>& e, float dt);
	void Update(const std::shared_ptr<Entity>& e, float dt);


	//bool IsIntersect(line, line);
	//bool IsInside(Vec2& v, Line);
};
