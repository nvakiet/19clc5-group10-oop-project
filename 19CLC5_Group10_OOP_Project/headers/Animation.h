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
    double m_trend;// 1 huong chinh, -1 huong phu
    vector<sf::Texture*> Animation_texture;
    int index_pic = 0;

    sf::Clock SpawnClock;

public:
    Animation();
    Animation(double fx,double fy,double width,double length,double trend,vector<sf::Texture*> textures);
    sf::RectangleShape picture_animation(int mode);
    void animation_update_fX(double fX);
    void animation_update_fY(double fY);
    void update_trend(double trend);
    double get_fX();
    double get_fY();
};

#endif // ANIMATION_H
