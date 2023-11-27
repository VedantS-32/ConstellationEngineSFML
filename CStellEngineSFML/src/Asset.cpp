#include "Asset.h"
#include <fstream>
#include <sstream>

bool Asset::AddTexture(std::string Name, std::string Path)
{
	bool b = false;
	m_Texture[Name] = sf::Texture();
	b = m_Texture[Name].loadFromFile(Path);
	m_AssetPath[Name] = Path;
	return b;
}

void Asset::AddTexture(std::string Name, sf::Texture Texture)
{
	m_Texture[Name] = Texture;
}

void Asset::AddAnimation(std::string Name, Animation)
{
}

void Asset::AddSound(std::string Name, std::string Path)
{
}

void Asset::AddFont(std::string Name, std::string Path)
{
	m_Font[Name] = sf::Font();
	m_Font[Name].loadFromFile(Path);
	m_AssetPath[Name] = Path;
}

void Asset::LoadFromFile(std::string Attribute, std::string Name, std::string Path)
{
	if (Attribute == "Texture")
	{
		AddTexture(Name, Path);
	}
	if (Attribute == "Font")
	{
		AddFont(Name, Path);
	}
	if (Attribute == "Animation")
	{
		//AddAnimation(Name, Path);
	}
	if (Attribute == "Sound")
	{
		AddSound(Name, Path);
	}
}

const std::string& Asset::GetAssetPath(std::string Name) const
{
	return m_AssetPath.at(Name);
}

sf::Texture& Asset::GetTexture(std::string Name)
{
	return m_Texture.at(Name);
}

Animation& Asset::GetAnimation(std::string Name)
{
	return m_Animation.at(Name);
}

sf::Sound& Asset::GetSound(std::string Name)
{
	return m_Sound.at(Name);
}

sf::Font& Asset::GetFont(std::string Name)
{
	return m_Font.at(Name);
}
