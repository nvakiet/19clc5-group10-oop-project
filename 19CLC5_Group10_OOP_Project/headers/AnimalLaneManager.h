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
#include "soundLoad.h"


class AnimalManager
{
private:
    vector<vector <sf::Texture*>> animal;
    vector <AnimalLane> land;
    int level = 1;
    sound m_sound;
public:
    AnimalManager(const texture& textureManager);
    //AnimalManager(const texture& textureManager, sound &s);
    //~AnimalManager();
    //void unloadtexture();
    void update(float elapsed, float gametime);
    void draw(sf::RenderWindow& window);
    bool checkCollosion(sf::FloatRect other);
    bool checkCollosion(sf::FloatRect other, double fYpos);
    void UpLevel();
};

#endif // AnimalManager_H
