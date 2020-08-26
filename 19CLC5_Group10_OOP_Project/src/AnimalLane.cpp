#include "AnimalLane.h"

AnimalLane::AnimalLane(float fXpos, float fYpos, float fWidth, float landspeed, float level, vector<sf::Texture*> textures)
{
    laneHeight = fYpos;
    laneXStart = fXpos;
    Width = fWidth;
    m_vptexTextures = textures;

    LaneSpeed = landspeed;
    this->level = level;
    number = getNumber();
}
void AnimalLane::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < AnimalsInLane.size(); i++)
        AnimalsInLane[i].draw(window);
}

void AnimalLane::update(float elapsed, float fGameTime)
{
    for (int i = 0; i < AnimalsInLane.size(); i++)
        AnimalsInLane[i].update(elapsed);
    //unknown Checks the game time if it is less the 0.1 seconds the game is speed up by 60x for spawning
    if (fGameTime < 0.1)
        fTimeSinceSpawn = spawnClock.getElapsedTime().asSeconds() * 60;
    else
        fTimeSinceSpawn = spawnClock.getElapsedTime().asSeconds();
    ;
    if (fTimeSinceSpawn > NextSpawn)
    {
        AnimalsInLane.push_back(animal((level*1.0/2) * LaneSpeed, laneXStart, laneHeight, Width, m_vptexTextures));
        spawnClock.restart();
        NextSpawn = getNextSpawn();
    }


    // if ther is more than 10 animals in the lane then remove the earliest animal to have spawned
    if (AnimalsInLane.size() > 10)
    {
        AnimalsInLane.erase(AnimalsInLane.begin());
    }
}

float AnimalLane::getNextSpawn()
{
    float fTempLaneSpeed;
    // turning speed to always be positve
    if (LaneSpeed < 0)
    {
        fTempLaneSpeed = -LaneSpeed;
    }
    else
    {
        fTempLaneSpeed = LaneSpeed;
    }
    float fMinTime; 	// Minimum time for a car to spawn
    float fMaxTime;		// Maximum time for a car to spawn
    float time;

    if (number > 0)
    {
        fMinTime = 0.2;
        fMaxTime = 0.2;
        time = (fMinTime + (float)(rand()) / ((float)(RAND_MAX / (fMaxTime - fMinTime)))); //Return a float between the min and max times
        number--;
    }
    else
    {
        time = 2.5;
        number = getNumber();
    }
    return time;
}

bool AnimalLane::checkCollision(sf::FloatRect other)
{
    // Call checkCollision for each animal in the lane
    for (unsigned int i = 0; i < AnimalsInLane.size(); i++) {
        if (AnimalsInLane[i].checkCollision(other))
        {
            return true;	// collision
        }
    }
    return false;	// no collision
}

int AnimalLane::getNumber()
{
    int n = rand() % 3 + 3;
    return n;
}
