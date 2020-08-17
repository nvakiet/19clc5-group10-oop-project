#ifndef TRAFFICMANAGER_H
#define TRAFFICMANAGER_H

#include "trafficroad.h"
#include "trafficlight.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


class trafficmanager
{
private:
    vector <sf::Texture*> m_car;
    vector <trafficlane> m_vland;
    vector <trafficlight> m_light;

public:
    trafficmanager();
    ~trafficmanager();
    void uploadtexture();
    void unloadtexture();
    void update(double elapsed, double gametime);
    void draw(sf::RenderWindow & window);
    bool checkCollosion(sf::FloatRect other);
};

#endif // TRAFFICMANAGER_H
