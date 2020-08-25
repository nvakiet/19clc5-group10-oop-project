#include "AnimalLaneManager.h"

trafficmanager::trafficmanager()
{
	land.clear();
	uploadtexture();
	land.push_back(trafficlane(0, 100, 40, 110, 3, animal,1));
	land.push_back(trafficlane(800, 300, 40, -130, 3, animal,0));
	land.push_back(trafficlane(0, 350, 40, 120, 3, animal,1));
	land.push_back(trafficlane(800, 550, 40, -115, 3, animal,0));

}

trafficmanager::~trafficmanager()
{
	unloadtexture();
}

void trafficmanager::update(float elapsed, float gametime)
{
	for (int i = 0; i < land.size(); i++)
	{
		land[i].update(elapsed,gametime);
	}
}

void trafficmanager::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < land.size(); i++)
	{
		land[i].draw(window);
	}
}

bool trafficmanager::checkCollosion(sf::FloatRect other)
{
	for (int i = 0; i <= land.size(); i++) {
		if (land[i].checkCollision(other))
		{
			return true;	// collision
		}
	}
	return false;	// no collision
}

void trafficmanager::uploadtexture()
{
	string dinosaur[2] = {
		"images/textures/animals/dog.png",
		"images/textures/animals/dino.png"
	};

	for (int i = 0; i < 2; i++)
	{
		animal.push_back(new sf::Texture);
		animal[i]->loadFromFile(dinosaur[i]);
	}
}

void trafficmanager::unloadtexture()
{
	for (int i = 0; i < animal.size(); i++)
	{
		delete animal[i];
	}
	animal.clear();
}