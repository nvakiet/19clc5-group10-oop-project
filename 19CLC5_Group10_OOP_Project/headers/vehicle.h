#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace std;

class vehicle
{
public:
    double m_fX;
    double m_fY;
    double m_fSpeed;
    double m_fLength;
    double m_fWidth;

    sf::RectangleShape m_rectBox;
    sf::Texture *carTextures;

    //constructor
    vehicle(float speed, float xPos, float yPos, float length, vector<sf::Texture*> textures);

	void setSpeed(float speed);
	void update(double elapsed);
	void draw(sf::RenderWindow& window);
	bool checkCollision(sf::FloatRect other);
	bool crash(double v); // check with the last car v = van toc xe trc
};

#endif // vehiclelib
