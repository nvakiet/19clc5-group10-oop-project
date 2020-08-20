#ifndef TRAFFICROAD_H
#define TRAFFICROAD_H

#include "vehicle.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace std;

class trafficlane
{
private:
    double m_laneHeight;
    double m_laneXStart;
    double m_NextSpawn;
    double m_Width;
    double m_LaneSpeed;
    double hack_speed; //hack speed follow level
    double m_level;

    sf::Clock spawnClock;

    vector<sf::Texture*> m_vptexTextures;
    vector<vehicle> CarsInLane;

public:
    trafficlane();
    trafficlane(double fXpos, double fYpos, double fWidth,double landspeed,double level, vector<sf::Texture*> textures);
    void draw(sf::RenderWindow &window);
    void update(double elapsed,double fGameTime);
    void update_nextspawn(double timeplus);
    double getNextSpawn();
    bool checkCollision(sf::FloatRect other);
    bool check_position_light(); // check have car in position light or not
};

#endif // TRAFFICROAD_H
