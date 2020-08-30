#include "trafficroad.h"

trafficlane::trafficlane(double fXpos, double fYpos, double fWidth, double landspeed,double level,vector<sf::Texture*> textures)
{
    m_laneHeight = fYpos;
    m_laneXStart = fXpos;
    m_Width = fWidth;
    m_vptexTextures = textures;
    m_LaneSpeed = landspeed/abs(landspeed);
    m_level = level;
    hack_speed = (rand()%3+1)*6*(abs(m_level)+1); //hack speed
}

void trafficlane::draw(sf::RenderWindow &window)
{
    for (int i=0; i<CarsInLane.size(); i++)
        CarsInLane[i].draw(window);
}

void trafficlane::update(double elapsed, double fGameTime)
{
    for (int i=0; i<CarsInLane.size(); i++)
        CarsInLane[i].update(elapsed);

    int k =0;
    //unknown Checks the game time if it is less the 0.1 seconds the game is speed up by 60x for spawning
    double m_fTimeSinceSpawn;
    if (fGameTime < 0.1)
		m_fTimeSinceSpawn = spawnClock.getElapsedTime().asSeconds() * 60;
	else
		m_fTimeSinceSpawn = spawnClock.getElapsedTime().asSeconds();
    k = CarsInLane.size();
    if (m_fTimeSinceSpawn > m_NextSpawn)
    {
        //set speed to cars
        double speed = 0;
        double mg[]={90,100,100,100,170,200,170,220};
        int countt=0;
//        for (int i=0; i<k; i++)
//        {
//            cout <<i << "::::" << CarsInLane[i].m_fX << " " << CarsInLane[i].m_fSpeed << '\n';
//        }
        for (int i=0; i<8; i++)
            mg[i]+=20.0;

        while (speed <= 70)
        {
            countt++;
            speed = mg[rand()%8] + hack_speed;
            if (CarsInLane.size()==0) break;
            if (!CarsInLane[CarsInLane.size()-1].crash(speed)) speed =0;
            if (countt > 2) goto jump;
        }
        CarsInLane.push_back(vehicle(speed * m_LaneSpeed, m_laneXStart, m_laneHeight, m_Width, m_vptexTextures));
        //cout << speed << '\n';
        spawnClock.restart();
		m_NextSpawn = getNextSpawn();
    }
    jump:
    while (CarsInLane.size() > 0 && ((m_LaneSpeed > 0 && CarsInLane[0].m_fX > 800) || (m_LaneSpeed < 0 && CarsInLane[0].m_fX < 0)))
    {
		CarsInLane.erase(CarsInLane.begin());
	}
}

double trafficlane::getNextSpawn()
{
    double magicmin[5] = {1, 0.8 , 0.6 , 0.4 , 0.2};
    double magicmax[5] = {2.5, 2 , 1.5 , 1 , 0.5};
	double fMinTime; 	// Minimum time for a car to spawn
	double fMaxTime;		// Maximum time for a car to spawn
	int tmp = min(m_level/10  , 4.0);
    fMinTime = magicmin[tmp] ;
    fMaxTime = magicmax[tmp] ;
  //  cout << (int) m_level / 10<< " " << tmp << " " << fMinTime << ' '  << fMaxTime << '\n';
	return (fMinTime + (float) (rand()) / ( (float) (RAND_MAX / (fMaxTime - fMinTime)))); //Return a float between the min and max times

}

bool trafficlane::checkCollision(sf::FloatRect other)
{
	// Call checkCollision for each vechicle in the lane
	for (unsigned int i = 0; i < CarsInLane.size(); i++){
		if (CarsInLane[i].checkCollision(other))
		{
			return true;	// collision
		}
	}
	return false;	// no collision
}

void trafficlane::update_nextspawn(double timeplus)
{
    m_NextSpawn +=timeplus;
}

bool trafficlane::check_position_light() //have car in end true.
{
    for (int i=0; i<CarsInLane.size(); i++)
        if (m_LaneSpeed > 0 && CarsInLane[i].m_fX > 630) return true;
        else if (m_LaneSpeed < 0 && 170 > CarsInLane[i].m_fX) return true;
    return false;
}

void trafficlane::update_level(int x)
{
    m_level = x;
    hack_speed = (rand()%3+1)*6*(m_level+1); //hack speed
}
