#pragma once

#include "Component.h"

#include <tuple>
#include <string>
#include <memory>
#include <string>

typedef std::tuple<
	CTransform,
	CLifespan,
	CInput,
	CBoundingBox,
	CSprite,
	CAnimation,
	CGravity,
	CState
> ComponentTuple;

class Entity
{
	friend class EntityManager;

	bool m_alive = true;
	size_t m_id = 0;
	std::string m_tag = "DefaultName";

	// Constructor and Destructor

public:
	const size_t GetEntityID() const
	{
		return m_id;
	}
	ComponentTuple m_Component;
	// Constructor is private so we can never create
	// entities outside the EntityManager which had friend access
	Entity(const size_t id, const std::string& tag);

	////Component Pointers
	//std::shared_ptr<CAnimation> cAnimation
	//std::shared_ptr<CTransform> cTransform;
	//std::shared_ptr<CShape> cShape;
	//std::shared_ptr<CCollision> cCollision;
	//std::shared_ptr<CInput> cInput;
	//std::shared_ptr<CScore> cScore;
	//std::shared_ptr<CLifespan> cLifespan;

	// Private Member Access Functions

	template <typename T>
	bool HasComponent() const
	{
		return GetComponent<T>().Has;
	}

	template <typename T, typename... TArgs> 
	T& AddComponent(TArgs&&... mArgs)
	{
		auto& component = GetComponent<T>();
		component = T(std::forward<TArgs>(mArgs)...);
		component.Has = true;
		return component;
	}

	template <typename T>
	const T& GetComponent() const
	{
		return std::get<T>(m_Component);
	}

	template <typename T>
	T& GetComponent()
	{
		return std::get<T>(m_Component);
	}

	template <typename T>
	void RemoveComponent()
	{
		GetComponent<T>() = T();
	}

	bool isActive() const;
	const std::string& tag() const;
	const size_t id() const;
	void destroy();
};