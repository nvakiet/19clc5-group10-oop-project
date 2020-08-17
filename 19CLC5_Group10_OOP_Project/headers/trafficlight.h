#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class trafficlight
{
private:
    double m_fX;
    double m_fY;
    double m_length;
    double m_width;
    double m_level;
    double m_NextStop;

    sf::Clock StopClock;

public:
    bool m_status;
    sf::RectangleShape m_rectBox;

    trafficlight(double mXpos, double mYpos, double length, double width,double level);
    void update(double fGameTime);
    void draw(sf::RenderWindow &window);
    double getNextStop();

};

#endif // TRAFFICLIGHT_H
