#include "trafficmanager.h"

trafficmanager::trafficmanager()
{
    m_vland.clear();
    uploadtexture();

    for (int i=0; i<8; i++)
    {
        if (rand()%2==0)
        {
            m_vland.push_back(trafficlane(-100,(i+1)*50,100,1,3,m_car));
            m_light.push_back(trafficlight(750,(i+1)*50,50,50,3));
        }
        else
        {
            m_vland.push_back(trafficlane(900,(i+1)*50,100,-1,3,m_car));
            m_light.push_back(trafficlight(0,(i+1)*50,50,50,3));
        }

    }

 //   m_vland.push_back(trafficlane(-100,300,100,1,3,m_car));

}

trafficmanager::~trafficmanager()
{
    unloadtexture();
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
        if (!m_light[i].m_status)
            m_light[i].draw(window);
        m_vland[i].draw(window);
    }
//    m_vland[2].draw(window);
}

bool trafficmanager::checkCollosion(sf::FloatRect other)
{
    for (int i = 0; i <= m_vland.size(); i++){
		if (m_vland[i].checkCollision(other))
		{
			return true;	// collision
		}
	}
	return false;	// no collision
}

void trafficmanager::uploadtexture()
{
int numcar = 22;
    string Car[numcar] =
	{
		"assets/textures/vehicles/fast/AudiBlue.png",
		"assets/textures/vehicles/fast/AudiGreen.png",
		"assets/textures/vehicles/fast/AudiPurple.png",
		"assets/textures/vehicles/fast/AudiRed.png",
		"assets/textures/vehicles/fast/AudiYellow.png",
		"assets/textures/vehicles/fast/ViperBlackOrange.png",
		"assets/textures/vehicles/fast/ViperBlackRed.png",
		"assets/textures/vehicles/fast/ViperBlackWhite.png",
		"assets/textures/vehicles/fast/ViperWhiteBlack.png",
		"assets/textures/vehicles/fast/Police.png",
		"assets/textures/vehicles/medium/CarBlue.png",
		"assets/textures/vehicles/medium/CarGreen.png",
		"assets/textures/vehicles/medium/CarOrange.png",
		"assets/textures/vehicles/medium/CarRed.png",
		"assets/textures/vehicles/medium/CarYellow.png",
		"assets/textures//vehicles/medium/PickupBlue.png",
		"assets/textures/vehicles/medium/PickupGreen.png",
		"assets/textures/vehicles/medium/PickupRed.png",
		"assets/textures/vehicles/medium/Taxi.png",
		"assets/textures/vehicles/slow/Ambulance.png",
		"assets/textures/vehicles/slow/Truck.png",
		"assets/textures/vehicles/slow/Van.png"
	};

	for (int i = 0; i < numcar; i++)
	{
		m_car.push_back(new sf::Texture);
		m_car[i]->loadFromFile(Car[i]);
	}
}

void trafficmanager::unloadtexture()
{
    for (int i = 0; i < m_car.size(); i++)
	{
		delete m_car[i];
	}
	m_car.clear();
}
