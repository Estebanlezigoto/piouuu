#include "CAssetManager.h"


void CAssetManager::LoadTexture(std::string name, std::string fileName)
{
	sf::Texture tex;
	if (tex.loadFromFile(fileName)) {
		Textures[name] = tex;
	}
}

void CAssetManager::LoadTexture(std::string name, sf::Texture tex)
{
	Textures[name] = tex;
}

sf::Texture& CAssetManager::GetTexture(std::string name)
{
	return Textures.at(name);
}

void CAssetManager::LoadFont(std::string name, std::string fileName)
{
	sf::Font font;
	if (font.loadFromFile(fileName)) {
		Fonts[name] = font;
	}
}

sf::Font& CAssetManager::GetFont(std::string name)
{
	return Fonts.at(name);
}

void CAssetManager::InitialiserMusiques()
{
	musiqueManager.ajouterMusique("MenuPrincipal", "res\\sfx\\musique_menu_test.mp3");
	musiqueManager.ajouterMusique("PartieJour", "res\\sfx\\Partie_de_jour.mp3");
}

void CAssetManager::changeScreenType(sf::RenderWindow& window, bool& isFullScreen)
{
	if (!isFullScreen)
	{
		isFullScreen = true;
		sCREEN_WIDTH = 1920;
		sCREEN_HEIGHT = 1080;
		window.create(sf::VideoMode(sCREEN_WIDTH, sCREEN_HEIGHT), "PIOU PIOU", sf::Style::Fullscreen);
	}
	else
	{
		isFullScreen = false;
		sCREEN_WIDTH = 1280;
		sCREEN_HEIGHT = 720;
		window.create(sf::VideoMode(sCREEN_WIDTH, sCREEN_HEIGHT),"PIOU PIOU", sf::Style::Close | sf::Style::Titlebar);
	}
	window.setFramerateLimit(60);
}


