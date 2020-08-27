#ifndef soundLoad_h
#define soundLoad_h

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <SFML/Audio.hpp>
using namespace std;

class sound
{
public:
	vector<sf::SoundBuffer*> animal;
	sf::Music* menu;
	sf::Music* ingame;

	sound();
	~sound();
};
#endif
