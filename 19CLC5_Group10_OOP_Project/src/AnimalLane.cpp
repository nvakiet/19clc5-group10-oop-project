#include "AnimalLane.h"

AnimalLane::AnimalLane(float fXpos, float fYpos, float fWidth, float landspeed, float level, vector<sf::Texture*> textures)
{
    AnimalsInLane.clear();
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

    if (fTimeSinceSpawn > NextSpawn)
    {
        AnimalsInLane.push_back(animal(LaneSpeed, laneXStart, laneHeight, Width, m_vptexTextures));
        spawnClock.restart();
        NextSpawn = getNextSpawn();
    }


    // if ther is more than 30 animals in the lane then remove the earliest animal to have spawned
    if (AnimalsInLane.size() > 30)
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
        double mg[] = {0.3,0.15,0.13,0.1,0.07};
        fMinTime = mg[(int) level/4-1];
        fMaxTime = mg[(int) level/4-1];
        time = (fMinTime + (float)(rand()) / ((float)(RAND_MAX / (fMaxTime - fMinTime)))); //Return a float between the min and max times
        number--;
    }
    else
    {
        double mgf[] = {2,1.5,1.5,1,1};
        double mgs[] = {3,2,1.7,1.7,1.5};
        /*double mgf[5] = { 1.5, 0.9 , 0.7 , 0.5 , 0.3 };
        double mgs[5] = { 2.5, 1.5 , 1 , 0.9 , 0.5 };*/
        fMinTime = mgf[(int) level/4-1];
        fMaxTime = mgs[(int) level/4-1];
        time = (fMinTime + (float)(rand()) / ((float)(RAND_MAX / (fMaxTime - fMinTime)))); //Return a float between the min and max times
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

void AnimalLane::update_level(int x)
{
    double mg[] = {90,120,130,150,170};
    level = x;
    LaneSpeed = (LaneSpeed/abs(LaneSpeed)) * mg[(int) level/4-1];
  //  cout << LaneSpeed << '\n';
}
