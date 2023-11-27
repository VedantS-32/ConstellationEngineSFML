#pragma once

#include<SFML/Graphics.hpp>
#include"Vec2.h"
#include<map>

class Animation
{
	friend class Serializer;

private:
	sf::Sprite m_Sprite;
	std::map<std::string, sf::Texture> m_AnimationMap;
	std::map<std::string, int> m_AnimFrameCountMap;
	std::vector<std::string> m_AnimationList;
	std::map<std::string, std::string> m_AnimationPath;
	std::string m_CurrentAnimation;
	std::string m_EntityTag;
	size_t m_FrameCount;
	size_t m_CurrentFrame = 1;
	size_t m_FrameElapsed = 0;
	Vec2 m_Size;
	std::string m_Name = "Default Name";

public:
	size_t m_Speed = 10;

	Animation();
	Animation(const std::string& Name, const sf::Texture& texture);
	Animation(const std::string& Name, const sf::Texture& texture, size_t FrameCount, size_t Speed);

	void AddAnimation(std::string AnimName, sf::Texture Texture, int FrameCount);
	void ChangeAnimation(std::string AnimName);
	void UpdateAnimation();
	bool HasEnded();
	void SetSprite(std::string AnimName, sf::Texture& t);
	const std::vector<std::string> GetAnimationList() const;
	const std::map<std::string, int> GetAnimationFrameCount() const;
	const std::string& GetName() const;
	const size_t& GetSize() const;
	sf::Sprite& GetSprite();
};
