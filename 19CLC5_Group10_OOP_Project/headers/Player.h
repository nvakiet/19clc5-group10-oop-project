#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

using namespace std;

class trafficmanager;
class AnimalManager;
class Player {
public:
	Player(const sf::Texture&);
	void move(const sf::Event&, const float&);
	void draw(sf::RenderWindow&) const;
	bool isImpact(trafficmanager*);
	bool isImpact(AnimalManager*);
	bool isDead() const;
	bool reachedGoal() const;
	void resetStatus();
	//sf::FloatRect getBound() const;
	//sf::Vector2f getPosition() const;
private:
	float x, y;
	sf::Sprite playerSprite;
	bool state; //0 = dead, 1 = alive
	sf::Clock cooldown;
};

#endif // !PLAYER_H
