#include "Animation.h"
#include <cmath>

Animation::Animation()
{
}

Animation::Animation(const std::string& Name, const sf::Texture& texture)
	: m_Name(Name), m_EntityTag(Name)
{
	m_Sprite.setTexture(texture);
	m_Size = Vec2((float)texture.getSize().x, (float)texture.getSize().y);
	m_Sprite.setOrigin(m_Size.x / 2.0f, m_Size.y / 2.0f);
	m_Sprite.setTextureRect(sf::IntRect(0, 0, m_Size.x, m_Size.y));
}

Animation::Animation(const std::string& Name, const sf::Texture& t, size_t FrameCount, size_t Speed)
	: m_Name(Name), m_EntityTag(Name), m_Sprite(t), m_FrameCount(FrameCount), m_CurrentFrame(0), m_Speed(Speed)
{
	m_Size = Vec2((float)t.getSize().x / FrameCount, (float)t.getSize().y);
	m_Sprite.setOrigin(m_Size.x / 2.0f, m_Size.y / 2.0f);
	m_Sprite.setTextureRect(sf::IntRect(std::floor(m_CurrentFrame) * m_Size.x, 0, m_Size.x, m_Size.y));
}

// Update the animation to show next frame
// Animation loops when it reaches the next

void Animation::AddAnimation(std::string AnimName, sf::Texture Texture, int FrameCount = 1)
{
	m_AnimationMap[AnimName] = Texture;
	m_AnimFrameCountMap[AnimName] = FrameCount;
	m_AnimationList.push_back(AnimName);
	console_log(AnimName << "->AnimationAdded");
}

void Animation::ChangeAnimation(std::string AnimName)
{
	m_CurrentAnimation = AnimName;
	m_FrameCount = m_AnimFrameCountMap[AnimName];
	m_Sprite.setTexture(m_AnimationMap[AnimName]);
	m_Size = Vec2((float)m_Sprite.getTexture()->getSize().x / m_FrameCount, (float)m_Sprite.getTexture()->getSize().y);
	m_Sprite.setTextureRect(sf::IntRect(m_Size.x, 0, m_Size.x, m_Size.y));

	/*log("FrameCount: " << m_FrameCount);
	log(AnimName << "->CurrentAnimation");*/
}

void Animation::UpdateAnimation()
{
	if(m_AnimFrameCountMap[m_CurrentAnimation] > 1)
	{
		// Add the speed variable to the current frame
		if (m_FrameElapsed++ > m_Speed)
		{
			if (m_CurrentFrame >= m_AnimFrameCountMap[m_CurrentAnimation] - 1)
			{
				m_CurrentFrame = 0;
			}
			m_CurrentFrame++;
			m_Sprite.setTextureRect(sf::IntRect(std::floor(m_CurrentFrame) * m_Size.x, 0, m_Size.x, m_Size.y));
			m_FrameElapsed = 0;
		}

		// 1) Calculate the correct frame of the animation to play based on CurrentFrame and Speed
		// 2) Set the texture rectangle properly (see constructor for sample)
	}
}

bool Animation::HasEnded()
{
	// Detect when animation has ended (last frame was played) and return true
	return false;
}

void Animation::SetSprite(std::string AnimName, sf::Texture& t)
{
	m_FrameCount = 1;
	m_CurrentAnimation = AnimName;
	m_Sprite.setTexture(t);
}

const std::vector<std::string> Animation::GetAnimationList() const
{
	return m_AnimationList;
}

const std::map<std::string, int> Animation::GetAnimationFrameCount() const
{
	return m_AnimFrameCountMap;
}

const std::string& Animation::GetName() const
{
	return m_CurrentAnimation;
}

const size_t& Animation::GetSize() const
{
	return m_FrameCount;
}

sf::Sprite& Animation::GetSprite()
{
	return m_Sprite;
}
