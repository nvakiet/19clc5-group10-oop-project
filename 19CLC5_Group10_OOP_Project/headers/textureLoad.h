#ifndef load_h
#define load_h

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;

class texture
{
public:
	vector<sf::Texture*> player;
	vector<sf::Texture*> animal;
	vector<sf::Texture*> vehicle;
	vector<sf::Texture*> CatAnimation;
	vector<sf::Texture*> DogAnimation;
	vector<sf::Texture*> DinoAnimation;
	vector<sf::Texture*> button;
	sf::Texture* background;
	sf::Texture* igBackground;
	sf::Texture* title;
	sf::Texture* selected;
	//sf::Texture* traffic;
	sf::Texture* trafficlight;

	texture();
	~texture();
};
#endif
