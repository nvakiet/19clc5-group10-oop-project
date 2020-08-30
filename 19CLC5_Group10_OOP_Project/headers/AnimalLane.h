#ifndef ANIMALLANE_H
#define ANIMALLANE_H

#include "Animal.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace std;

class AnimalLane
{
private:
    float laneHeight;
    float laneXStart;
    float NextSpawn;
    float Width;
    float LaneSpeed;
    float level;
    float fTimeSinceSpawn;
    int number;

    sf::Clock spawnClock;

    vector<sf::Texture*> m_vptexTextures;
    vector<animal> AnimalsInLane;

public:
    AnimalLane(float fXpos, float fYpos, float fWidth, float landspeed, float level, vector<sf::Texture*> textures);
    void draw(sf::RenderWindow& window);
    void update(float elapsed, float fGameTime);
    float getNextSpawn();
    bool checkCollision(sf::FloatRect other);
    int getNumber();
    void update_level(int x);
};

#endif // TRAFFICROAD_H
