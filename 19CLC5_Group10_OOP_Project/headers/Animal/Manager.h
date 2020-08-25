#ifndef TRAFFICMANAGER_H
#define TRAFFICMANAGER_H

#include "Lane.h"
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
    vector <sf::Texture*> animal;
    vector <trafficlane> land;

public:
    trafficmanager();
    ~trafficmanager();
    void uploadtexture();
    void unloadtexture();
    void update(float elapsed, float gametime);
    void draw(sf::RenderWindow& window);
    bool checkCollosion(sf::FloatRect other);
};

#endif // TRAFFICMANAGER_H