#include "vehicle.h"

vehicle::vehicle(float speed, float xPos, float yPos, float length, vector<sf::Texture*> textures)
{
    m_fX = xPos;
	m_fY = yPos;
	m_fSpeed = speed;
	m_fLength = length;
	m_fWidth = 46;

    m_rectBox.setPosition(sf::Vector2f(m_fX,m_fY)); // set position of vehicle
    m_rectBox.setSize(sf::Vector2f(m_fLength, m_fWidth));	// Sets the size of the vehicle

    int randindex = rand() % (textures.size());
    m_rectBox.setTexture(textures[randindex]); // build picture vehicle

    if (m_fSpeed < 0)
    {
        m_timeend = (xPos)/speed;
        m_rectBox.scale(-1 , 1); // reverses the textture
    }
}

//sets a new speed for the vehicle
void vehicle::setSpeed(float speed)
{
    m_fSpeed = speed;
}

// update the vehicles position
void vehicle::update(double elapsed)
{
    m_fX += m_fSpeed * elapsed;

    m_rectBox.setPosition(sf::Vector2f(m_fX,m_fY)); // sets the vehicle
}

// Draws vehicle to the provided window
void vehicle::draw(sf::RenderWindow& window)
{
	window.draw(m_rectBox);
}

bool vehicle::checkCollision(sf::FloatRect other) {
	return m_rectBox.getGlobalBounds().intersects(other);
}

bool vehicle::crash(double v)
{
    if (m_fSpeed > 0) if (((double)800.0 - m_fX)/m_fSpeed < (double)800.0/v) return true;
    if (m_fSpeed < 0) if (((double)m_fX)/abs(m_fSpeed) < (double)800.0/abs(v)) return true;
    return false;
}
