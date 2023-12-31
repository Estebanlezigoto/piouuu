#pragma once
#include"CCard.h"
class CCardUpgrade : public CCard
{
private:
	std::vector<sf::Text> Stats;
public:
	std::vector<std::string> type;
	std::vector<std::string> Upgrade;

	void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const;
	CCardUpgrade(){}
	CCardUpgrade(int levelofEntity);//Nouvelle CCardUpgrade pour quand on a complété toutes les améliorations
	CCardUpgrade( std::vector<std::string> Upgrade, std::vector<std::string> type, CAssetManager* assetParam);
	//Surcharge pour une amélioration
	CCardUpgrade(std::string Upgrade, std::string type, CAssetManager* assetParam);
	void setPosition(sf::Vector2f r);
	//resize le text pour qu'il ne dépasse pas, ne descend pas en dessous de la taille de caractère 20
	//Va falloir faire un truc pour rendre plus jolie les noms des types, surement plus dans upgradestate cela dit
	void update(float deltaTime);
	void reduceScale();
	//Fonction qui resize une liste de texte compte tenu d'une bordure en hauteur et en largeur
	void resizeTexts(std::vector<sf::Text>& texts, sf::FloatRect border);
};

