#include "AnimalLaneManager.h"

AnimalManager::AnimalManager(const texture& textureManager)
{
	land.clear();

	land.push_back(AnimalLane(0, 50, 40, 110, level, textureManager.DinoAnimation));
	land.push_back(AnimalLane(800, 250, 40, -130, level, textureManager.DogAnimation));
	land.push_back(AnimalLane(0, 300, 40, 120, level, textureManager.CatAnimation));
	land.push_back(AnimalLane(800, 500, 40, -115, level, textureManager.DinoAnimation));

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

bool AnimalManager::checkCollosion(sf::FloatRect other, double fYpos)
{
    double magic[] = {50,250,300,500}; //position
	for (int i = 0; i < land.size(); i++) {
        if (magic[i]-60.0 <= fYpos && fYpos <= magic[i]+60.0 && land[i].checkCollision(other))
		{
            if (i==0 || i==3) m_sound.dinosaurSound.play();
		    else if (i==1) m_sound.dogSound.play();
		    else if (i==2) m_sound.catSound.play();
			return true;	// collision
		}
	}
	return false;	// no collision
}

void AnimalManager::UpLevel()
{
    level+=4;
}


//void AnimalManager::unloadtexture()
//{
//	for (int i = 0; i < animal.size(); i++)
//	{
//		delete animal[i];
//	}
//	animal.clear();
//}
