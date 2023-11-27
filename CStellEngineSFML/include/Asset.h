#pragma once
#include<map>
#include"Animation.h"
#include<SFML/Audio.hpp>

class Asset
{
private:
	std::map<std::string, std::string> m_AssetPath;
	std::map<std::string, sf::Texture> m_Texture;
	std::map<std::string, Animation> m_Animation;
	std::map<std::string, sf::Sound> m_Sound;
	std::map<std::string, sf::Font> m_Font;

public:
	Asset() = default;

	bool AddTexture(std::string Name, std::string Path);
	void AddTexture(std::string Name, sf::Texture Texture);
	void AddAnimation(std::string Name, Animation);
	void AddSound(std::string Name, std::string Path);
	void AddFont(std::string Name, std::string Path);

	void LoadFromFile(std::string Attribute, std::string Name, std::string Path);

	const std::string & GetAssetPath(std::string Name) const;
	sf::Texture& GetTexture(std::string Name);
	Animation& GetAnimation(std::string Name);
	sf::Sound& GetSound(std::string Name);
	sf::Font& GetFont(std::string Name);

};