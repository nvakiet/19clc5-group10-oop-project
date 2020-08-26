#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace std;

class Animation
{
private:
    double m_fX;
    double m_fY;
    double m_fWidth;
    double m_fLength;
    double m_trend;
    vector<sf::Texture*> Animation_texture;
    int index_pic = 0;

    sf::Clock SpawnClock;

public:
    Animation();
    Animation(double fx,double fy,double width,double length,double fspeed,vector<sf::Texture*> textures);
    sf::RectangleShape picture_animation(int mode);
    void animation_update_fX(double fX);
};

#endif // ANIMATION_H
