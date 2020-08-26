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

    if (time > 100 && mode==1)
    {
        index_pic = (index_pic+mode)%8;
        SpawnClock.restart();
    }
    sf::RectangleShape m_rectBox;
    m_rectBox.setPosition(sf::Vector2f(m_fX, m_fY)); // set position of animal
    m_rectBox.setSize(sf::Vector2f(m_fLength, m_fWidth));	// Sets the size of the animal
    m_rectBox.setTexture(Animation_texture[index_pic]); // build picture animal


    if (m_trend < 0)
        m_rectBox.scale(-1, 1); // reverses the textture
    return m_rectBox;
}

void Animation::animation_update_fX(double fx)
{
    m_fX = fx;
}
