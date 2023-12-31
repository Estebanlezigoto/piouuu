#include "CEnemy.h"

/*
CEnemy::CEnemy()
{
}

CEnemy::CEnemy(CAssetManager* a)
{
	setType(Enemy);
	assets = a;
	imageName = "enemyImage";
	setTexture(imageName, ENEMYPNG_FILEPATH);
	getSprite().setScale(0.2f, 0.2f);
	initAnimation();
	initStat();
	initPositionX = (float)assets->sCREEN_WIDTH;
	setSprite();
	std::cout << "bah oui !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
}
CEnemy::CEnemy(float xcoordinate, CAssetManager* a) 
{
	assets = a;
	imageName = "enemyImage";
	setTexture(imageName, ENEMYPNG_FILEPATH);
	initPositionX = xcoordinate;
	getSprite().setScale(0.2f, 0.2f);
	initAnimation();
	initStat();
	setSprite();
}
*/
void CEnemy::initAnimation()
{
	CAssetManager &a = *assets;
	currentFrame = sf::IntRect(274 , 409, 1295, 1925);
	explosionSprite.setTexture(a.GetTexture("explosion"));
	explosionSprite.setTextureRect(currentFrame);
	explosionSprite.setScale(0.1f, 0.1f);
}

/*
CEnemy::CEnemy(CAssetManager* a, std::string nameParam, std::string imageFileParam)
{
	setType(Enemy);
	assets = a;
	a->LoadTexture(enemyName, imageFile);
	getSprite().setTexture((a->GetTexture(enemyName)));
	getSprite().setScale(0.2f, 0.2f);
	initAnimation();
	initStat();
	initPositionX = (float)assets->sCREEN_WIDTH;
	setSprite();
}
*/

void CEnemy::initEnnemy(CAssetManager* a)
{
	setType(Enemy);
	assets = a;
	imageName = "enemyImage";
	setTexture(imageName);
	getSprite().setScale(0.2f, 0.2f);
	initAnimation();
	initStat();
	setSprite();
}

void CEnemy::initEnnemy(CAssetManager* a, std::string nameParam, std::string imageFileParam)
{
	setType(Enemy);
	assets = a;
	a->LoadTexture(enemyName, imageFile);
	getSprite().setTexture((a->GetTexture(enemyName)));
	getSprite().setScale(0.2f, 0.2f);
	initAnimation();
	initStat();
	setSprite();
}



void CEnemy::setSprite()
{
	setLifeBar();
	setPositionEntity(initPositionX  - getSprite().getGlobalBounds().width, (float)initPositionY);
}



void CEnemy::updateEntity(float delta)
{
	if (isDead == true)
	{
		if (updateExplosionSprite() == true)
			needDelete = true;
	}	
		updateMovement(delta);
}

void CEnemy::updatewPlayer(float delta, CPlayer& player)
{
	if (checkCollisions(player))
	{
		//SI on est la c'est que l'ennemi est en contact avec le jouueur
		if (isDead == false)
		{
			if (isHitting == false)
			{
				player.reduceHP(damage);
				isHitting = true;
			}
		}
		else if (isHitting == true)
			isHitting = false;
	}
	//Ici on regarde le type 

	std::vector<CBulletAuto>* guns = player.getBAW()->getVector();
	size_t temp =guns->size();
	for (size_t i = 0; i < temp; i++)
	{
		if (checkCollisions((*guns)[i])&& isDead==false)
		{
			reduceHP((*guns)[i].getDamage());
			guns->erase(guns->begin() + i);
			if (i != 0)
				i--;
			temp--;
		}
	}
	if (healthPoint <= 0)
	{
		isDead = true;
		onAvance = false;
	}
	if (isDead == true)
	{
		if(gavexP==false)
		{
			player.gainXP(level);
			gavexP=true;
			player.addToScore(scoreGived);
		}
	}
}

bool CEnemy::getIsAShooter()
{
	return isAShooter;
}



void CEnemy::specialBehaviorwithPlayer(CPlayer& player)
{
	player.gainXP(level);
}

void CEnemy::updateCollision(CEntity& b)
{
	/*switch (b.getType())
	{
	case FriendlyFire:
		if (checkCollisions(b))
			reduceHP(b.getDamage());
		break;
	case Player:
		if (checkCollisions(b))
		{
			if(isHitting==false)
			{
				b.damagetaken -= getDamage();
				isHitting = true;
			}
		}
		else if (isHitting == true)
			isHitting = false;
		break;
	default:
		break;
	}*/
}

bool CEnemy::updateEntity(float leftbound, float delta)
{
	if (isDead == true)
		return updateExplosionSprite();
	if(getSprite().getGlobalBounds().left + getSprite().getGlobalBounds().width>leftbound)
	{ 

		return false;
	}
	onAvance = false;
	return true;
}

bool CEnemy::updateEntity(sf::FloatRect a,float delta)
{
	if (!getSprite().getGlobalBounds().intersects(a))
	{
		return false;
	}
	return true;
}

void CEnemy::updateAnimation()
{
	if (animationTimer.getElapsedTime().asSeconds() > 0.5f)
	{
		currentFrame.left += 1295;
	}
}
//renvoie true si l'animation d'explosion est finie
bool CEnemy::updateExplosionSprite()
{
	explosionSprite.setPosition(sf::Vector2f(getSprite().getPosition().x+(getSprite().getGlobalBounds().width/2)-(explosionSprite.getGlobalBounds().width/2),
		getSprite().getPosition().y + (getSprite().getGlobalBounds().height / 2) - (explosionSprite.getGlobalBounds().width / 2)));
	if (r < 7)
	{
		if (animationTimer.getElapsedTime().asSeconds() > 0.1f)
		{
			currentFrame.left += 1295;
			explosionSprite.setTextureRect(currentFrame);
			r++;
			animationTimer.restart();
			return false;
		}
		return false;
	}
	return true;
}


void CEnemy::renderEntity(sf::RenderTarget& target)
{
	if(isDead==false)
		renderTheEntity(target);
	else{
		//std::cout << r << std::endl;
		target.draw(explosionSprite);
	}
}
/*
void CEnemy::updateMovement(float delta)
{
		if (checkGlobalCollisions())
			needDelete = true;
		updateLifeBar();
		if(onAvance==true)
			moveEntity(sf::Vector2f(directionX * delta * 19.f, directionY));


}
*/