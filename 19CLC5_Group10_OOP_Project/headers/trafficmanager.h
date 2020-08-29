#ifndef TRAFFICMANAGER_H
#define TRAFFICMANAGER_H

#include "trafficroad.h"
#include "trafficlight.h"
#include "textureLoad.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "soundLoad.h"


class trafficmanager
{
private:
    vector <sf::Texture*> m_car;
    vector <trafficlane> m_vland;
    vector <trafficlight> m_light;
    int m_level=5;
    sound m_sound;

public:
    trafficmanager(texture &texturemanager);
    void update(double elapsed, double gametime);
    void draw(sf::RenderWindow & window);
    bool checkCollosion(sf::FloatRect other);
    bool checkCollosion(sf::FloatRect other, double fYpos);
    void UpLevel();
};

#endif // TRAFFICMANAGER_H
