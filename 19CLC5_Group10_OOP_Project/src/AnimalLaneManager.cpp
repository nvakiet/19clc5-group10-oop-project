#include "AnimalLaneManager.h"

AnimalManager::AnimalManager(const texture& textureManager)
{
	land.clear();
	animal = textureManager.animal;
	land.push_back(AnimalLane(0, 50, 40, 110, 3, animal,1));
	land.push_back(AnimalLane(800, 250, 40, -130, 3, animal,0));
	land.push_back(AnimalLane(0, 300, 40, 120, 3, animal,1));
	land.push_back(AnimalLane(800, 500, 40, -115, 3, animal,0));

}

//AnimalManager::~AnimalManager()
//{
//	unloadtexture();
//}

void AnimalManager::update(float elapsed, float gametime)
{
	for (int i = 0; i < land.size(); i++)
	{
		land[i].update(elapsed,gametime);
	}
}

void AnimalManager::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < land.size(); i++)
	{
		land[i].draw(window);
	}
}

bool AnimalManager::checkCollosion(sf::FloatRect other)
{
	for (int i = 0; i < land.size(); i++) {
		if (land[i].checkCollision(other))
		{
			return true;	// collision
		}
	}
	return false;	// no collision
}


//void AnimalManager::unloadtexture()
//{
//	for (int i = 0; i < animal.size(); i++)
//	{
//		delete animal[i];
//	}
//	animal.clear();
//}