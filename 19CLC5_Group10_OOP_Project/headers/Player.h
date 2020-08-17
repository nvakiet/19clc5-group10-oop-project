#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
using namespace std;

class Player {
public:
	Player(const sf::Texture&);
	void move(const sf::Event&, const float&);
	void draw(sf::RenderWindow&) const;
	bool isDead() const;
	bool reachedGoal() const;

private:
	float x, y;
	sf::Sprite playerSprite;
	bool state; //0 = dead, 1 = alive
};

#endif // !PLAYER_H
