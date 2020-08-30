#include "Animation.h"


Animation::Animation(){}

Animation::Animation(double fx,double fy,double width,double length,double trend,vector<sf::Texture*> textures)
{
    m_fX = fx;
    m_fY = fy;
    m_fWidth = width;
    m_fLength = length;
    Animation_texture = textures;
    if (trend > 0) m_trend = 1;
    else m_trend = -1;
    SpawnClock.restart();
}

sf::RectangleShape Animation::picture_animation(int mode)
{
    double time = SpawnClock.getElapsedTime().asMilliseconds();
    float switchTime = 8 * 50 / Animation_texture.size();
    if (time > switchTime && (mode==1))
    {
        //time -= 100;
        index_pic = (index_pic+mode) % Animation_texture.size();
        SpawnClock.restart();
    }
    sf::RectangleShape m_rectBox;
    m_rectBox.setTexture(Animation_texture[index_pic]); // build picture animal

    m_rectBox.setSize(sf::Vector2f(m_fLength, m_fWidth));	// Sets the size of the animal
    if(m_fWidth==50 && m_fLength==30)
        m_rectBox.setOrigin(m_rectBox.getGlobalBounds().width / 2, m_rectBox.getGlobalBounds().height / 2); // nay la luoi bieng!
    m_rectBox.setPosition(sf::Vector2f(m_fX, m_fY)); // set position of animal

    if (m_trend < 0)
        m_rectBox.scale(-1, 1); // reverses the textture
    return m_rectBox;
}

void Animation::animation_update_fX(double fx)
{
    m_fX = fx;
}

void Animation::animation_update_fY(double fy)
{
    m_fY = fy;
}

void Animation::update_trend(double trend)
{
    m_trend = trend;
}

double Animation::get_fX()
{
    return m_fX;
}

double Animation::get_fY()
{
    return m_fY;
}

