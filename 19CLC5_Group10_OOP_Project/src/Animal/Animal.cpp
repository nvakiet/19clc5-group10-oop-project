#include "Animal.h"

animal::animal(float speed, float xPos, float yPos, float length, vector<sf::Texture*> textures, int findex)
{
    fX = xPos;
    fY = yPos;
    fSpeed = speed;
    fLength = length;
    fWidth = 40;

    m_rectBox.setPosition(sf::Vector2f(fX, fY)); // set position of animal
    m_rectBox.setSize(sf::Vector2f(fLength, fWidth));	// Sets the size of the animal
    m_rectBox.setTexture(textures[findex]); // build picture animal
    if (fSpeed < 0)
    {
        m_rectBox.scale(-1, 1); // reverses the textture
    }
}

// update the animals position
void animal::update(float elapsed)
{
    fX += fSpeed * elapsed;

    m_rectBox.setPosition(sf::Vector2f(fX, fY)); // sets the animal
}

// Draws animal to the provided window
void animal::draw(sf::RenderWindow& window)
{
    window.draw(m_rectBox);
}

bool animal::checkCollision(sf::FloatRect other) 
{
    return m_rectBox.getGlobalBounds().intersects(other);
}