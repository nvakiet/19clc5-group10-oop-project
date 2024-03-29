#include "trafficmanager.h"

trafficmanager::trafficmanager(texture &textureManager, const sf::Sound& sound)
{
    m_vland.clear();
    m_car = textureManager.vehicle;
    int magic[] = {100,200,350,450};
    for (int i=0; i<4; i++)
    {
        if (rand()%2==0)
        {
            m_vland.push_back(trafficlane(-100,magic[i],100,1,m_level,m_car));
            m_light.push_back(trafficlight(750,magic[i],40,40,m_level,textureManager, sound));
        }
        else
        {
            m_vland.push_back(trafficlane(900,magic[i],100,-1,m_level,m_car));
            m_light.push_back(trafficlight(0,magic[i],40,40,m_level,textureManager, sound));
        }

    }
 //   m_vland.push_back(trafficlane(-100,300,100,1,3,m_car));
}

void trafficmanager::update(double elapsed, double gametime)
{
    for (int i=0; i<m_vland.size(); i++)
    {
        if (!m_light[i].m_status || !m_vland[i].check_position_light())
            m_light[i].update(gametime);

        if (m_light[i].m_status || !m_vland[i].check_position_light())       // true that mean can run
            m_vland[i].update(elapsed,gametime);
        else m_vland[i].update_nextspawn(elapsed);
    }



    //m_vland[2].update(elapsed,gametime);
}

void trafficmanager::draw(sf::RenderWindow &window)
{
    for (int i=0; i<m_vland.size(); i++)
    {
        if (!m_light[i].m_status) {
            m_light[i].draw(window);
        }
        m_vland[i].draw(window);
    }
//    m_vland[2].draw(window);
}

bool trafficmanager::checkCollosion(sf::FloatRect other)
{
    for (int i = 0; i < m_vland.size(); i++){
		if (m_vland[i].checkCollision(other))
		{
			return true;	// collision
		}
	}
	return false;	// no collision
}

bool trafficmanager::checkCollosion(sf::FloatRect other, double fYpos)
{
    double magic[] = {100,200,350,450}; //position
    for (int i = 0; i < m_vland.size(); i++){
		if (magic[i]-60.0 <= fYpos && fYpos <= magic[i]+60.0 && m_vland[i].checkCollision(other))
		{
			return true;	// collision
		}
	}
	return false;	// no collision
}

void trafficmanager::setLevel(int newLevel)
{
    m_level += 10 * (newLevel - 1);
    for (int i=0; i<m_vland.size(); i++)
        m_vland[i].update_level(m_level);
    //cout <<m_level << '\n';
}

