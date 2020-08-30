#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "Animation.h"
using namespace std;

class trafficmanager;
class AnimalManager;
class Player {
public:
	//Player(const sf::Texture&, const sf::Sound&);
	Player(const vector<sf::Texture*>&, const sf::Sound&);
	void move(const sf::Event&, const float&);
	void draw(sf::RenderWindow&);
	bool isImpact(trafficmanager*);
	bool isImpact(AnimalManager*);
	bool isDead() const;
	bool reachedGoal() const;
	void resetStatus();
	//sf::FloatRect getBound() const;
	sf::Vector2f getPosition();
private:
	float x, y;
	//sf::Sprite playerSprite;
	sf::Sound movementSound;
	Animation player_animation;
	bool state; //0 = dead, 1 = alive
	sf::Clock cooldown;
};

#endif // !PLAYER_H
