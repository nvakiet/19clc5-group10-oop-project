#include "trafficlight.h"

trafficlight::trafficlight(double mXpos, double mYpos, double length, double width,double level)
{
    m_status = true;
    m_fX = mXpos;
    m_fY = mYpos;
    m_length = length;
    m_width = width;
    m_level = level;

    sf::Texture* text;
    text = new sf::Texture;
    text->loadFromFile("D:/c++ source/codeblock/crossy road project oop/assets/stop.png");

    m_rectBox.setPosition(sf::Vector2f(mXpos,mYpos));
    m_rectBox.setSize(sf::Vector2f(m_length,m_width));
    m_rectBox.setTexture(text);
}

void trafficlight::draw(sf::RenderWindow &window)
{
    window.draw(m_rectBox);
}

double trafficlight::getNextStop()
{
    float fMinTime; 	// Minimum time for a car to spawn
	float fMaxTime;		// Maximum time for a car to spawn
	if (m_status)
    {
        fMinTime = 9;		// Distance of a vehicle plus size of the player
        fMaxTime = 15+(6-m_level);	// Distance of 3 vehicles plus the size of the player
    }
    else
    {
        fMinTime = 3;		// Distance of a vehicle plus size of the player
        fMaxTime = 5+(6-m_level);	// Distance of 3 vehicles plus the size of the player
    }
	double magic = (fMinTime + (float) (rand()) / ( (float) (RAND_MAX / (fMaxTime - fMinTime)))); //Return a float between the min and max times
	return magic;
}

void trafficlight::update(double fGameTime)
{
    double m_fTimeSinceStop;
    if (fGameTime < 0.1)
		m_fTimeSinceStop = StopClock.getElapsedTime().asSeconds() * 60;
	else
		m_fTimeSinceStop = StopClock.getElapsedTime().asSeconds();

    if (m_fTimeSinceStop > m_NextStop)
    {
        bool tmp = !m_status;
        m_status = tmp;
        StopClock.restart();
        m_NextStop = getNextStop();
    }
}
