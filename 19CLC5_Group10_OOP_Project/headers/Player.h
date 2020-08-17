#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
using namespace std;

class Lane;

class Player {
public:
	Player(const sf::Texture&);
	void move(const sf::Event&, const float&);
	void draw(sf::RenderWindow&) const;

private:
	sf::Sprite playerSprite;
	bool state; //0 = dead, 1 = alive
};

#endif // !PLAYER_H
