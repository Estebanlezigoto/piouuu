#pragma once
#include "DEFINITIONS.h"
#include <SFML/Graphics.hpp>
#include<iostream>
#include <string>
#include"CAssetManager.h"
class CEntity1
{
private :
	sf::Sprite ENTsprite;
	int type = undefined;
	int damage;
	int level = 0;
public:
	int damagetaken = 0;
	bool isHitting = false;
	bool isDead = false;
	bool needDelete = false;
	typedef enum
	{
		undefined = -1,
		Player,
		Enemy,
		FriendlyFire,
		EnemyFire,
		PowerUp,
		Gunslinger
	} typeInt;
	CAssetManager* assets = NULL;
	 //void specialPlayerInteraction(CPlayer&a){}
	virtual void setSprite() = 0;
	virtual void updateEntity(float dt) = 0;
	virtual void renderEntity(sf::RenderTarget& target) = 0;
	virtual void updateCollision(CEntity1& b) = 0;
	void setTexture(std::string name, std::string filename) {
		CAssetManager& a = *assets;
		a.LoadTexture(name, filename);
		ENTsprite.setTexture(a.GetTexture(name));
	}
	sf::Sprite& getSprite() { return ENTsprite; }
	sf::FloatRect getGlobalBounds() {
		return ENTsprite.getGlobalBounds();
	}
	void setPositionEntity(const float x, const float y) {
		ENTsprite.setPosition(x, y);
	}
	void setPositionEntity(sf::Vector2f i) {
		ENTsprite.setPosition(i);
	}
	int getType() { return type; }
	void setType(int Type) { type = Type; }
	bool checkCollisions(CEntity1& b)
	{
		if (b.ENTsprite.getGlobalBounds().intersects(ENTsprite.getGlobalBounds()))
			return true;
		return false;
	}
	bool checkGlobalCollisions() {
		if(type!=Gunslinger)
		{ 
			if (ENTsprite.getGlobalBounds().left + ENTsprite.getGlobalBounds().width<0 || ENTsprite.getGlobalBounds().left>SCREEN_WIDTH)
				return true;
			return false;
		}
		return false;
	}
	int getDamage()
	{
		return damage;
	}
	void setDamage(int d) { damage = d; }
	void setLevel(int l) { level = l; }
	int getLevel() { return level; }
};

