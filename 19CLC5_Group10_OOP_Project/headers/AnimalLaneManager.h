#ifndef AnimalManager_H
#define AnimalManager_H

#include "AnimalLane.h"
#include "textureLoad.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


class AnimalManager
{
private:
    vector<vector <sf::Texture*>> animal;
    vector <AnimalLane> land;

public:
    AnimalManager(const texture& textureManager);
    //~AnimalManager();
    //void unloadtexture();
    void update(float elapsed, float gametime);
    void draw(sf::RenderWindow& window);
    bool checkCollosion(sf::FloatRect other);
};

#endif // AnimalManager_H
