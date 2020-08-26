#ifndef ANIMAL_H
#define ANIMAL_H

#include "Animation.h"
#include <iostream>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace std;

class animal
{
public:
    float fX;
    float fY;
    float fSpeed;
    float fLength;
    float fWidth;

    Animation animal_animation;
    sf::Texture* animalTextures;

    //constructor
    animal(float speed, float xPos, float yPos, float length, vector<sf::Texture*> textures);
    void update(float elapsed);
    void draw(sf::RenderWindow& window);
    bool checkCollision(sf::FloatRect other);
};

#endif
